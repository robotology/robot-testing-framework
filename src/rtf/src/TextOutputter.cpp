// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <string.h>
#include <errno.h>
#include <fstream>

#include <rtf/TextOutputter.h>
#include <rtf/ResultEvent.h>

using namespace RTF;
using namespace std;

#define MSG_ERROR   "[ERROR] "
#define MSG_FAIL    "[FAIL]  "
#define MSG_REPORT  "[INFO]  "

TextOutputter::TextOutputter(RTF::TestResultCollector& collector, bool verbose)
    :collector(collector), verbose(verbose) { }

TextOutputter::~TextOutputter() { }

bool TextOutputter::write(std::string filename, bool summary,
                          RTF::TestMessage* errorMsg) {
    if(filename.empty()) {
        if(errorMsg != NULL) {
            errorMsg->setMessage("Cannot open the file.");
            errorMsg->setDetail("Empty file name.");
        }
        return false;
    }

    ofstream outputter;
    outputter.open(filename.c_str());
    if (!outputter.is_open() || !outputter.good()) {
        if(errorMsg != NULL) {
            errorMsg->setMessage("Cannot open the file.");
            const char* errorStr = strerror(errno);
            errorMsg->setDetail(errorStr);
        }
        return false;
    }

    TestResultCollector::EventResultIterator itr;
    TestResultCollector::EventResultContainer events = collector.getResults();

    for(itr=events.begin(); itr!=events.end(); ++itr) {
       ResultEvent* e = *itr;

       // start suit
       if(dynamic_cast<ResultEventStartSuit*>(e))
           outputter<<"Test suit "<<e->getTest()->getName()<<" started..."<<endl;
       // end suit
       else if(dynamic_cast<ResultEventEndSuit*>(e)) {
           outputter<<"Test suit "<<e->getTest()->getName();
           if(e->getTest()->succeeded())
               outputter<<" passed!"<<endl;
           else
               outputter<<" failed!"<<endl;
       }

       // start test case
       else if(dynamic_cast<ResultEventStartTest*>(e))
           outputter<<"Test case "<<e->getTest()->getName()<<" started..."<<endl;

       // end test case
       else if(dynamic_cast<ResultEventEndTest*>(e)) {
           outputter<<"Test case "<<e->getTest()->getName();
           if(e->getTest()->succeeded())
               outputter<<" passed!"<<endl;
           else
               outputter<<" failed!"<<endl;
       }

       // report event
       else if(dynamic_cast<ResultEventReport*>(e)) {
           outputter<<MSG_REPORT<<"("<<e->getTest()->getName()<<") "
               <<e->getMessage().getMessage()<<": "<<e->getMessage().getDetail()<<endl;
           if(verbose && e->getMessage().getSourceLineNumber() != 0) {
               outputter<<e->getMessage().getSourceFileName()
                       <<" at "<<e->getMessage().getSourceLineNumber()<<"."<<endl<<endl;
           }
       }

       // failure event
       else if(dynamic_cast<ResultEventFailure*>(e)) {
           outputter<<MSG_FAIL<<"("<<e->getTest()->getName()<<") "
               <<e->getMessage().getMessage()<<": "<<e->getMessage().getDetail()<<endl;
           if(verbose && e->getMessage().getSourceLineNumber() != 0) {
               outputter<<e->getMessage().getSourceFileName()
                       <<" at "<<e->getMessage().getSourceLineNumber()<<"."<<endl<<endl;
           }
       }

       // error event
       else if(dynamic_cast<ResultEventError*>(e)) {
           outputter<<MSG_ERROR<<"("<<e->getTest()->getName()<<") "
               <<e->getMessage().getMessage()<<": "<<e->getMessage().getDetail()<<endl;
           if(verbose && e->getMessage().getSourceLineNumber() != 0) {
               outputter<<e->getMessage().getSourceFileName()
                       <<" at "<<e->getMessage().getSourceLineNumber()<<"."<<endl<<endl;
           }
       }
    } // end for

    if(summary) {
        // write some simple statistics
        outputter<<endl<<"---------- summary -----------"<<endl;
        if(collector.suitCount()) {
            outputter<<"Total number of test suites  : "<<collector.suitCount()<<endl;
            outputter<<"Number of passed test suites : "<<collector.passedSuitCount()<<endl;
            outputter<<"Number of failed test suites : "<<collector.failedSuitCount()<<endl;
        }
        outputter<<"Total number of test cases   : "<<collector.testCount()<<endl;
        outputter<<"Number of passed test cases  : "<<collector.passedCount()<<endl;
        outputter<<"Number of failed test cases  : "<<collector.failedCount()<<endl;
    }

    outputter.close();
    return true;
}
