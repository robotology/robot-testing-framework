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


#include <robottestingframework/Arguments.h>
#include <robottestingframework/Exception.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestMessage.h>

#include <csignal>
#include <cstring>
#include <utility>

#define C_MAXARGS 128 // max number of the command parametes

using namespace robottestingframework;
using namespace std;


/**
 * In case of any abnormal behaviour of the test case
 * catch the abortion signal and add the proper messege
 * to the result collector.
 */
static TestCase* _currentTestCase = nullptr;
static void run_signal_handler(int)
{
    if (_currentTestCase) {
        _currentTestCase->getResult()->addError(_currentTestCase,
                                                TestMessage("asserts error with exception",
                                                            "Terminated due to segmentation violation/abortion within the test case!",
                                                            ROBOTTESTINGFRAMEWORK_SOURCEFILE(),
                                                            ROBOTTESTINGFRAMEWORK_SOURCELINE()));
        _currentTestCase->getResult()->endTest(_currentTestCase);
    }
    std::signal(SIGSEGV, SIG_DFL);
    std::signal(SIGABRT, SIG_DFL);
    throw TestErrorException(TestMessage("Terminated due to segmentation violation or abort signal!"));
}


TestCase::TestCase(std::string name, std::string param) :
        Test(name),
        param(std::move(param)),
        successful(true),
        result(nullptr),
        repetition(0)
{
    _currentTestCase = this;
}

TestCase::~TestCase() = default;

void TestCase::failed()
{
    successful = false;
}

bool TestCase::succeeded() const
{
    return successful;
}

TestResult* TestCase::getResult()
{
    return result;
}

void TestCase::setParam(const std::string param)
{
    this->param = param;
}

std::string TestCase::getParam()
{
    return param;
}


void TestCase::setEnvironment(const std::string environment)
{
    this->environment = environment;
}

std::string TestCase::getEnvironment()
{
    return environment;
}

void TestCase::setRepetition(unsigned int rep)
{
    repetition = rep;
}

unsigned int TestCase::getRepetition()
{
    return repetition;
}


bool TestCase::setup(int argc, char** argv)
{
    return true;
}


void TestCase::tearDown()
{
}


void TestCase::run(TestResult& rsl)
{
    this->result = &rsl;
    successful = true;
    interrupted = false;

    // call setup and run
    char* szcmd;
    char** szarg;

    std::signal(SIGSEGV, run_signal_handler);
    std::signal(SIGABRT, run_signal_handler);
    try {
        result->startTest(this);

        // parsing the argument to pass to the setup
        string strCmd = getName() + string(" ") + param;
        szcmd = new char[strCmd.size() + 1];
        strcpy(szcmd, strCmd.c_str());
        int nargs = 0;
        szarg = new char*[C_MAXARGS + 1];
        Arguments::parse(szcmd, &nargs, szarg);
        szarg[nargs] = nullptr;
        // call the setup
        if (!setup(nargs, szarg)) {
            result->addError(this, TestMessage("setup() failed!"));
            successful = false;
            result->endTest(this);
            // clear allocated memory for arguments
            if (szcmd) {
                delete[] szcmd;
                szcmd = nullptr;
            }
            if (szarg) {
                delete[] szarg;
                szarg = nullptr;
            }
            return;
        }

        for (unsigned int rep = 0; rep <= repetition && successful && !interrupted; rep++) {
            run();
        }
    } catch (TestFailureException& e) {
        successful = false;
        result->addFailure(this, e.message());
    } catch (TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    } catch (std::exception& e) {
        successful = false;
        result->addError(this, TestMessage(e.what()));
    }

    // call tearDown and catch the error exception
    try {
        tearDown();
    } catch (TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    } catch (std::exception& e) {
        successful = false;
        result->addError(this, TestMessage(e.what()));
    }

    std::signal(SIGSEGV, SIG_DFL);
    std::signal(SIGABRT, SIG_DFL);

    result->endTest(this);

    // clear allocated memory for arguments if it is not cleared
    if (szcmd) {
        delete[] szcmd;
        szcmd = nullptr;
    }
    if (szarg) {
        delete[] szarg;
        szarg = nullptr;
    }
}

void TestCase::interrupt()
{
    interrupted = true;
    result->addReport(this, TestMessage("TestCase interrupted", "An interrupt signal received", ROBOTTESTINGFRAMEWORK_SOURCEFILE(), ROBOTTESTINGFRAMEWORK_SOURCELINE()));
}
