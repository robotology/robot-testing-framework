// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <string.h>
#include <errno.h>
#include <tinyxml.h>

#include <JUnitOutputter.h>
#include <rtf/ResultEvent.h>
#include <rtf/Asserter.h>

using namespace RTF;
using namespace std;

#define MSG_ERROR   "[ERROR] ("
#define MSG_FAIL    "[FAIL]  ("
#define MSG_REPORT  "[INFO]  ("

JUnitOutputter::JUnitOutputter(RTF::TestResultCollector& collector, bool verbose)
    :collector(collector), verbose(verbose) { }

JUnitOutputter::~JUnitOutputter() { }

bool JUnitOutputter::write(std::string filename,
                          RTF::TestMessage* errorMsg) {
    if(filename.empty()) {
        if(errorMsg != NULL) {
            errorMsg->setMessage("Cannot open the file.");
            errorMsg->setDetail("Empty file name.");
        }
        return false;
    }

    TiXmlDocument doc;
    TiXmlElement* root = new TiXmlElement("testsuites");
    root->SetAttribute("suites", collector.suiteCount());
    root->SetAttribute("tests", collector.testCount());
    root->SetAttribute("failures", collector.failedCount());
    doc.LinkEndChild(root);

    TiXmlElement* testsuite = NULL;
    TiXmlElement* testcase = NULL;
    string classname;

    // If there is not any test suite, add one!
    if(collector.suiteCount() == 0) {
        classname = "default";
        testsuite = new TiXmlElement("testsuite");
        testsuite->SetAttribute("name", classname.c_str());
        root->LinkEndChild(testsuite);
    }

    TestResultCollector::EventResultIterator itr;
    TestResultCollector::EventResultContainer events = collector.getResults();

    string errorMessages, failureMessages, reportsMessages;
    for(itr=events.begin(); itr!=events.end(); ++itr) {
       ResultEvent* e = *itr;

       // start suit
       if(dynamic_cast<ResultEventStartSuite*>(e)) {
           classname = e->getTest()->getName();
           testsuite = new TiXmlElement("testsuite");
           testsuite->SetAttribute("name", classname.c_str());
           root->LinkEndChild(testsuite);
       }
       // end suit
       //else if(dynamic_cast<ResultEventEndSuite*>(e)) { }

       // start test case
       else if(dynamic_cast<ResultEventStartTest*>(e)) {
           if(testsuite == NULL) continue;
           testcase = new TiXmlElement("testcase");
           testcase->SetAttribute("name", e->getTest()->getName());
           testcase->SetAttribute("classname", classname+"."+e->getTest()->getName());
           testsuite->LinkEndChild(testcase);
           errorMessages.clear();
           failureMessages.clear();
           reportsMessages.clear();
       }

       // end test case
       else if(dynamic_cast<ResultEventEndTest*>(e)) {
           if(testcase == NULL) continue;
           // adding falures
           if(failureMessages.size()) {
               TiXmlElement * failure = new TiXmlElement("failure");
               failure->SetAttribute("message", "Something went wrong. See Stacktrace for detail.");
               failure->LinkEndChild(new TiXmlText(failureMessages.c_str()));
               testcase->LinkEndChild(failure);
            }

           // adding errors
           if(errorMessages.size()){
               TiXmlElement * error = new TiXmlElement("error");
               error->SetAttribute("message", "Something went wrong. See Stacktrace for detail.");
               error->LinkEndChild(new TiXmlText(errorMessages.c_str()));
               testcase->LinkEndChild(error);
            }

           // adding reports
           if(reportsMessages.size()) {
               TiXmlElement * report = new TiXmlElement("system-out");
               report->SetAttribute("message", "See Standard Output for detail.");
               report->LinkEndChild(new TiXmlText(reportsMessages.c_str()));
               testcase->LinkEndChild(report);
            }
       }

       // failure event
       else if(dynamic_cast<ResultEventFailure*>(e)) {
           string msg;
           if(verbose) {
                msg = Asserter::format("%s : %s (%s at %d) <br>",
                                         e->getMessage().getMessage().c_str(),
                                         e->getMessage().getDetail().c_str(),
                                         e->getMessage().getSourceFileName().c_str(),
                                         e->getMessage().getSourceLineNumber());
           }
           else
               msg = e->getMessage().getMessage() + ": " + e->getMessage().getDetail() + "\n";
            failureMessages += msg;
            reportsMessages += MSG_FAIL + e->getTest()->getName()+ ") " + msg;
       }

       // error event
       else if(dynamic_cast<ResultEventError*>(e)) {
           string msg;
           if(verbose) {
                msg = Asserter::format("%s : %s (%s at %d) <br>",
                                         e->getMessage().getMessage().c_str(),
                                         e->getMessage().getDetail().c_str(),
                                         e->getMessage().getSourceFileName().c_str(),
                                         e->getMessage().getSourceLineNumber());
           }
           else
               msg = e->getMessage().getMessage() + ": " + e->getMessage().getDetail() + "\n";
            errorMessages += msg;
            reportsMessages += MSG_ERROR + e->getTest()->getName()+ ") " + msg;
       }

       // report event
       else if(dynamic_cast<ResultEventReport*>(e)) {
           string msg;
           if(verbose) {
                msg = Asserter::format("%s : %s (%s at %d) <br>",
                                         e->getMessage().getMessage().c_str(),
                                         e->getMessage().getDetail().c_str(),
                                         e->getMessage().getSourceFileName().c_str(),
                                         e->getMessage().getSourceLineNumber());
           }
           else
               msg = e->getMessage().getMessage() + ": " + e->getMessage().getDetail() + "\n";
            reportsMessages += MSG_REPORT + e->getTest()->getName()+ ") " + msg;
       }

    } // end for

    if(!doc.SaveFile(filename.c_str())) {
        if(errorMsg != NULL) {
            errorMsg->setMessage("Cannot write to the " + filename);
            if (doc.Error())
                errorMsg->setDetail(Asserter::format("%s (line: %d, column %d)", doc.ErrorDesc(), doc.ErrorRow(), doc.ErrorCol()));
        }
        return false;
    }
    return true;
}
