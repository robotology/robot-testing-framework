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
    // call setup/run/tearDown
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
        parseArguments(szcmd, &nargs, szarg);
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
        tearDown();        
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

void TestCase::split(char *line, char **args)
{
     char *pTmp = strchr(line, ' ');

    if (pTmp) {
        *pTmp = '\0';
        pTmp++;
        while ((*pTmp) && (*pTmp == ' ')) {
            pTmp++;
        }
        if (*pTmp == '\0') {
            pTmp = NULL;
        }
    }
    *args = pTmp;
}

void TestCase::parseArguments(char *azParam , int *argc, char **argv)
{
    char *pNext = azParam;
    size_t i;
    int j;
    int quoted = 0;
    size_t len = strlen(azParam);

    // Protect spaces inside quotes, but lose the quotes
    for(i = 0; i < len; i++) {
        if ((!quoted) && ('"' == azParam [i])) {
            quoted = 1;
            azParam [i] = ' ';
        } else if ((quoted) && ('"' == azParam [i])) {
            quoted = 0;
            azParam [i] = ' ';
        } else if ((quoted) && (' ' == azParam [i])) {
            azParam [i] = '\1';
        }
    }

    // init
    memset(argv, 0x00, sizeof(char*) * C_MAXARGS);
    *argc = 1;
    argv[0] = azParam ;

    while ((NULL != pNext) && (*argc < C_MAXARGS)) {
        split(pNext, &(argv[*argc]));
        pNext = argv[*argc];

        if (NULL != argv[*argc]) {
            *argc += 1;
        }
    }

    for(j = 0; j < *argc; j++) {
        len = strlen(argv[j]);
        for(i = 0; i < len; i++) {
            if('\1' == argv[j][i]) {
                argv[j][i] = ' ';
            }
        }
    }
}
