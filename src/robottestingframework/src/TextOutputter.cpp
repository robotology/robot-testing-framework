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


#include <robottestingframework/ResultEvent.h>
#include <robottestingframework/TextOutputter.h>

#include <cerrno>
#include <cstring>
#include <fstream>

using namespace robottestingframework;
using namespace std;

#define MSG_ERROR "[ERROR] "
#define MSG_FAIL "[FAIL]  "
#define MSG_REPORT "[INFO]  "

TextOutputter::TextOutputter(TestResultCollector& collector, bool verbose) :
        collector(collector), verbose(verbose)
{
}

TextOutputter::~TextOutputter() = default;

bool TextOutputter::write(std::string filename, bool summary, TestMessage* errorMsg)
{
    if (filename.empty()) {
        if (errorMsg != nullptr) {
            errorMsg->setMessage("Cannot open the file.");
            errorMsg->setDetail("Empty file name.");
        }
        return false;
    }

    ofstream outputter;
    outputter.open(filename.c_str());
    if (!outputter.is_open() || !outputter.good()) {
        if (errorMsg != nullptr) {
            errorMsg->setMessage("Cannot open the file.");
            const char* errorStr = strerror(errno);
            errorMsg->setDetail(errorStr);
        }
        return false;
    }

    TestResultCollector::EventResultIterator itr;
    TestResultCollector::EventResultContainer events = collector.getResults();

    for (itr = events.begin(); itr != events.end(); ++itr) {
        ResultEvent* e = *itr;

        // start suit
        if (dynamic_cast<ResultEventStartSuite*>(e))
            outputter << "Test suite " << e->getTest()->getName() << " started..." << endl;
        // end suit
        else if (dynamic_cast<ResultEventEndSuite*>(e)) {
            outputter << "Test suite " << e->getTest()->getName();
            if (e->getTest()->succeeded())
                outputter << " passed!" << endl;
            else
                outputter << " failed!" << endl;
        }

        // start test case
        else if (dynamic_cast<ResultEventStartTest*>(e))
            outputter << "Test case " << e->getTest()->getName() << " started..." << endl;

        // end test case
        else if (dynamic_cast<ResultEventEndTest*>(e)) {
            outputter << "Test case " << e->getTest()->getName();
            if (e->getTest()->succeeded())
                outputter << " passed!" << endl;
            else
                outputter << " failed!" << endl;
        }

        // report event
        else if (dynamic_cast<ResultEventReport*>(e)) {
            outputter << MSG_REPORT << "(" << e->getTest()->getName() << ") "
                      << e->getMessage().getMessage() << ": " << e->getMessage().getDetail() << endl;
            if (verbose && e->getMessage().getSourceLineNumber() != 0) {
                outputter << e->getMessage().getSourceFileName()
                          << " at " << e->getMessage().getSourceLineNumber() << "." << endl
                          << endl;
            }
        }

        // failure event
        else if (dynamic_cast<ResultEventFailure*>(e)) {
            outputter << MSG_FAIL << "(" << e->getTest()->getName() << ") "
                      << e->getMessage().getMessage() << ": " << e->getMessage().getDetail() << endl;
            if (verbose && e->getMessage().getSourceLineNumber() != 0) {
                outputter << e->getMessage().getSourceFileName()
                          << " at " << e->getMessage().getSourceLineNumber() << "." << endl
                          << endl;
            }
        }

        // error event
        else if (dynamic_cast<ResultEventError*>(e)) {
            outputter << MSG_ERROR << "(" << e->getTest()->getName() << ") "
                      << e->getMessage().getMessage() << ": " << e->getMessage().getDetail() << endl;
            if (verbose && e->getMessage().getSourceLineNumber() != 0) {
                outputter << e->getMessage().getSourceFileName()
                          << " at " << e->getMessage().getSourceLineNumber() << "." << endl
                          << endl;
            }
        }
    } // end for

    if (summary) {
        // write some simple statistics
        outputter << endl
                  << "---------- summary -----------" << endl;
        if (collector.suiteCount()) {
            outputter << "Total number of test suites  : " << collector.suiteCount() << endl;
            outputter << "Number of passed test suites : " << collector.passedSuiteCount() << endl;
            outputter << "Number of failed test suites : " << collector.failedSuiteCount() << endl;
        }
        outputter << "Total number of test cases   : " << collector.testCount() << endl;
        outputter << "Number of passed test cases  : " << collector.passedCount() << endl;
        outputter << "Number of failed test cases  : " << collector.failedCount() << endl;
    }

    outputter.close();
    return true;
}
