// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <TestMessage.h>
#include <TestCase.h>
#include <Exception.h>
#include <Arguments.h>

#include <string.h>

#define C_MAXARGS           128         // max number of the command parametes

using namespace RTF;
using namespace std;

TestCase::TestCase(std::string name, std::string param)
    : RTF::Test(name),
      param(param),
      successful(true),
      result(NULL)
{
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
