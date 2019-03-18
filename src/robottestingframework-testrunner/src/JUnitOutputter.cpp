/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <robottestingframework/Asserter.h>
#include <robottestingframework/ResultEvent.h>

#include <JUnitOutputter.h>
#include <cerrno>
#include <cstring>
#include <tinyxml.h>

using namespace robottestingframework;
using namespace std;

#define MSG_ERROR "[ERROR] ("
#define MSG_FAIL "[FAIL]  ("
#define MSG_REPORT "[INFO]  ("

JUnitOutputter::JUnitOutputter(TestResultCollector& collector, bool verbose) :
        collector(collector), verbose(verbose)
{
}

JUnitOutputter::~JUnitOutputter() = default;

bool JUnitOutputter::write(std::string filename,
                           TestMessage* errorMsg)
{
    if (filename.empty()) {
        if (errorMsg != nullptr) {
            errorMsg->setMessage("Cannot open the file.");
            errorMsg->setDetail("Empty file name.");
        }
        return false;
    }

    TiXmlDocument doc;
    auto* root = new TiXmlElement("testsuites");
    root->SetAttribute("suites", collector.suiteCount());
    root->SetAttribute("tests", collector.testCount());
    root->SetAttribute("failures", collector.failedCount());
    doc.LinkEndChild(root);

    TiXmlElement* testsuite = nullptr;
    TiXmlElement* testcase = nullptr;
    string classname;

    // If there is not any test suite, add one!
    if (collector.suiteCount() == 0) {
        classname = "default";
        testsuite = new TiXmlElement("testsuite");
        testsuite->SetAttribute("name", classname.c_str());
        root->LinkEndChild(testsuite);
    }

    TestResultCollector::EventResultIterator itr;
    TestResultCollector::EventResultContainer events = collector.getResults();

    string errorMessages;
    string failureMessages;
    string reportsMessages;
    for (itr = events.begin(); itr != events.end(); ++itr) {
        ResultEvent* e = *itr;

        // start suite
        if (dynamic_cast<ResultEventStartSuite*>(e) != nullptr) {
            classname = e->getTest()->getName();
            testsuite = new TiXmlElement("testsuite");
            testsuite->SetAttribute("name", classname.c_str());
            root->LinkEndChild(testsuite);
        }
        // end suite
        //else if(dynamic_cast<ResultEventEndSuite*>(e)) { }

        // start test case
        else if (dynamic_cast<ResultEventStartTest*>(e) != nullptr) {
            if (testsuite == nullptr) {
                continue;
            }
            testcase = new TiXmlElement("testcase");
            testcase->SetAttribute("name", e->getTest()->getName());
            testcase->SetAttribute("classname", classname + "." + e->getTest()->getName());
            testsuite->LinkEndChild(testcase);
            errorMessages.clear();
            failureMessages.clear();
            reportsMessages.clear();
        }

        // end test case
        else if (dynamic_cast<ResultEventEndTest*>(e) != nullptr) {
            if (testcase == nullptr) {
                continue;
            }
            // adding falures
            if (failureMessages.size()) {
                auto* failure = new TiXmlElement("failure");
                failure->SetAttribute("message", "Something went wrong. See Stacktrace for detail.");
                failure->LinkEndChild(new TiXmlText(failureMessages.c_str()));
                testcase->LinkEndChild(failure);
            }

            // adding errors
            if (errorMessages.size()) {
                auto* error = new TiXmlElement("error");
                error->SetAttribute("message", "Something went wrong. See Stacktrace for detail.");
                error->LinkEndChild(new TiXmlText(errorMessages.c_str()));
                testcase->LinkEndChild(error);
            }

            // adding reports
            if (reportsMessages.size()) {
                auto* report = new TiXmlElement("system-out");
                report->SetAttribute("message", "See Standard Output for detail.");
                report->LinkEndChild(new TiXmlText(reportsMessages.c_str()));
                testcase->LinkEndChild(report);
            }
        }

        // failure event
        else if (dynamic_cast<ResultEventFailure*>(e) != nullptr) {
            string msg;
            if (verbose) {
                msg = Asserter::format("%s : %s (%s at %d) <br>",
                                       e->getMessage().getMessage().c_str(),
                                       e->getMessage().getDetail().c_str(),
                                       e->getMessage().getSourceFileName().c_str(),
                                       e->getMessage().getSourceLineNumber());
            } else {
                msg = e->getMessage().getMessage() + ": " + e->getMessage().getDetail() + "\n";
            }
            failureMessages += msg;
            reportsMessages += MSG_FAIL + e->getTest()->getName() + ") " + msg;
        }

        // error event
        else if (dynamic_cast<ResultEventError*>(e) != nullptr) {
            string msg;
            if (verbose) {
                msg = Asserter::format("%s : %s (%s at %d) <br>",
                                       e->getMessage().getMessage().c_str(),
                                       e->getMessage().getDetail().c_str(),
                                       e->getMessage().getSourceFileName().c_str(),
                                       e->getMessage().getSourceLineNumber());
            } else {
                msg = e->getMessage().getMessage() + ": " + e->getMessage().getDetail() + "\n";
            }
            errorMessages += msg;
            reportsMessages += MSG_ERROR + e->getTest()->getName() + ") " + msg;
        }

        // report event
        else if (dynamic_cast<ResultEventReport*>(e) != nullptr) {
            string msg;
            if (verbose) {
                msg = Asserter::format("%s : %s (%s at %d) <br>",
                                       e->getMessage().getMessage().c_str(),
                                       e->getMessage().getDetail().c_str(),
                                       e->getMessage().getSourceFileName().c_str(),
                                       e->getMessage().getSourceLineNumber());
            } else {
                msg = e->getMessage().getMessage() + ": " + e->getMessage().getDetail() + "\n";
            }
            reportsMessages += MSG_REPORT + e->getTest()->getName() + ") " + msg;
        }

    } // end for

    if (!doc.SaveFile(filename.c_str())) {
        if (errorMsg != nullptr) {
            errorMsg->setMessage("Cannot write to the " + filename);
            if (doc.Error()) {
                errorMsg->setDetail(Asserter::format("%s (line: %d, column %d)", doc.ErrorDesc(), doc.ErrorRow(), doc.ErrorCol()));
            }
        }
        return false;
    }
    return true;
}
