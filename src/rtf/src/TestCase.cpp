// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/TestMessage.h>
#include <rtf/TestCase.h>
#include <rtf/Exception.h>
#include <rtf/Arguments.h>

#include <string.h>
#include <csignal>

#define C_MAXARGS           128         // max number of the command parametes

using namespace RTF;
using namespace std;


/**
 * In case of any abnormal behaviour of the test case
 * catch the abortion signal and add the proper messege
 * to the result collector.
 */
static RTF::TestCase* _currentTestCase = NULL;
static void run_signal_handler(int) {
    if(_currentTestCase) {
        _currentTestCase->getResult()->addError(_currentTestCase,
                                                RTF::TestMessage("asserts error with exception",
                                                                 "Terminated due to segmentation violation/abortion within the test case!",
                                                                 RTF_SOURCEFILE(), RTF_SOURCELINE()));
        _currentTestCase->getResult()->endTest(_currentTestCase);
    }
    std::signal(SIGSEGV, SIG_DFL);
    std::signal(SIGABRT, SIG_DFL);
    throw TestErrorException(RTF::TestMessage("Terminated due to segmentation violation or abort signal!"));
}


TestCase::TestCase(std::string name, std::string param)
    : RTF::Test(name),
      param(param),
      successful(true),
      result(NULL),
      repetition(0)
{
    _currentTestCase = this;
}

TestCase::~TestCase() {

}

void TestCase::failed() {
    successful = false;
}

bool TestCase::succeeded() const {
    return successful;
}

TestResult* TestCase::getResult() {
    return result;
}

void TestCase::setParam(const std::string param) {
    this->param = param;
}

const std::string TestCase::getParam() {
    return param;
}


void TestCase::setEnvironment(const std::string environment) {
    this->environment = environment;
}

const std::string TestCase::getEnvironment() {
    return environment;
}

void TestCase::setRepetition(unsigned int rep) {
    repetition = rep;
}

unsigned int TestCase::getRepetition() {
    return repetition;
}



bool TestCase::setup(int argc, char**argv) {
    return true;
}


void TestCase::tearDown() { }


void TestCase::run(TestResult &rsl) {
    this->result = &rsl;
    successful = true;
    // call setup and run
    char *szcmd;
    char **szarg;

    std::signal(SIGSEGV, run_signal_handler);
    std::signal(SIGABRT, run_signal_handler);
    try {
        result->startTest(this);

        // parsing the argument to pass to the setup
        string strCmd = getName() + string(" ") + param;
        szcmd = new char[strCmd.size()+1];
        strcpy(szcmd, strCmd.c_str());
        int nargs = 0;
        szarg = new char*[C_MAXARGS + 1];
        Arguments::parse(szcmd, &nargs, szarg);
        szarg[nargs]=0;
        // call the setup
        if (!setup(nargs, szarg)) {
            result->addError(this, RTF::TestMessage("setup() failed!"));
            successful = false;
            result->endTest(this);
            // clear allocated memory for arguments
            if(szcmd) {
                delete [] szcmd;
                szcmd = NULL;
            }
            if(szarg) {
                delete [] szarg;
                szarg = NULL;
            }
            return;
        }

        for(unsigned int rep=0; rep<=repetition && successful; rep++)
            run();
    }
    catch(RTF::TestFailureException& e) {
        successful = false;
        result->addFailure(this, e.message());
    }
    catch(RTF::TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    }
    catch(std::exception& e) {
        successful = false;
        result->addError(this, RTF::TestMessage(e.what()));
    }

    // call tearDown and catch the error exception
    try {
        tearDown();
    }
    catch(RTF::TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    }
    catch(std::exception& e) {
        successful = false;
        result->addError(this, RTF::TestMessage(e.what()));
    }

    std::signal(SIGSEGV, SIG_DFL);
    std::signal(SIGABRT, SIG_DFL);

    result->endTest(this);

    // clear allocated memory for arguments if it is not cleared
    if(szcmd) {
        delete [] szcmd;
        szcmd = NULL;
    }
    if(szarg) {
        delete [] szarg;
        szarg = NULL;
    }
}
