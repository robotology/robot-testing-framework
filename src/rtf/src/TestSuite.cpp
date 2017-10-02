// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/TestMessage.h>
#include <rtf/TestSuite.h>
#include <rtf/Exception.h>

using namespace RTF;

TestSuite::TestSuite(std::string name)
    : RTF::Test(name),
    successful(true),
    fixtureOK(true),
    fixtureMesssage(""),
    result(NULL),
    current(NULL) { }

TestSuite::~TestSuite() {

}

void TestSuite::addTest(RTF::Test* test) {
    tests.push_back(test);
}


void TestSuite::removeTest(RTF::Test* test) {
    for (int i = 0; i < tests.size(); i++)
    {
        if(tests[i] == test) tests.erase(tests.begin()+i);
    }
}

void TestSuite::reset() {
    tests.clear();
    successful = fixtureOK =  true;
    fixtureMesssage.clear();
    result = NULL;
}


bool TestSuite::succeeded() const {
    return successful;
}

TestResult* TestSuite::getResult() {
    return result;
}

bool TestSuite::setup() {
    bool ret = true;
    FixtureIterator itr;
    for(itr=fixtureManagers.begin(); (itr!=fixtureManagers.end()) && ret; itr++)
        ret &= (*itr)->setup();
    return ret;
}


void TestSuite::tearDown() {
    FixtureRIterator itr;
    for(itr=fixtureManagers.rbegin(); itr!=fixtureManagers.rend(); itr++)
        (*itr)->tearDown();
}


void TestSuite::run(TestResult &rsl) {
    this->result = &rsl;
    successful = fixtureOK = true;
    interrupted = false;
    fixtureMesssage.clear();
    try {
        result->startTestSuite(this);
        // calling test suite setup
        if (!setup()) {
            result->addError(this, RTF::TestMessage("setup() failed!"));
            successful = false;
            result->endTestSuite(this);
            return;
        }

        // calling all test's run
        for (TestIterator it=tests.begin(); it!=tests.end(); ++it) {
            current = *it;
            // interrupted?
            if(interrupted)
                throw TestFailureException(RTF::TestMessage("interrupted!"));

            if(!fixtureOK)
                result->addError(this, fixtureMesssage);

            bool checkOk = true;
            FixtureIterator itr;
            for(itr=fixtureManagers.begin(); (itr!=fixtureManagers.end()) && checkOk; itr++)
                checkOk &= (*itr)->check();
            if(!checkOk) {
                result->addError(this, TestMessage("Fixture collapsed",
                                                   "check() failed",
                                                   RTF_SOURCEFILE(),
                                                   RTF_SOURCELINE()));
                fixtureOK = false;
            }

            // restart the fixture if it has been collapsed
            if(!fixtureOK) {
                successful = false;
                result->addReport(this, TestMessage("reports",
                                                    "restaring fixture setup",
                                                    RTF_SOURCEFILE(),
                                                    RTF_SOURCELINE()));
                tearDown();
                if(!setup())
                    throw FixtureException(RTF::TestMessage("setup() failed!"));

                bool checkOk = true;
                FixtureIterator itr;
                for(itr=fixtureManagers.begin(); (itr!=fixtureManagers.end()) && checkOk; itr++)
                    checkOk &= (*itr)->check();
                if(!checkOk)
                    throw FixtureException(TestMessage("Fixture collapsed",
                                                       "check() failed",
                                                       RTF_SOURCEFILE(),
                                                       RTF_SOURCELINE()));
                fixtureOK = true;
            }
            (*it)->run(*result);
            successful &= (*it)->succeeded();
        }
    }
    catch(RTF::TestFailureException& e) {
        successful = false;
        result->addFailure(this, e.message());
    }
    catch(RTF::TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    }
    catch(RTF::FixtureException& e) {
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

    result->endTestSuite(this);
    current = NULL;
}


void TestSuite::addFixtureManager(RTF::FixtureManager* manager) {
    manager->setDispatcher(this);
    fixtureManagers.push_back(manager);
}

void TestSuite::fixtureCollapsed(RTF::TestMessage reason) {

    // we do not want to throw any exception here.
    // The reason is that if fixtureCollapsed is called
    // within other threads, the exception cannot be caught
    // by the TestSuite.
    fixtureOK = false;
    fixtureMesssage = reason;
}

void TestSuite::interrupt() {
    if(current)
        current->interrupt();
    interrupted = true;
}
