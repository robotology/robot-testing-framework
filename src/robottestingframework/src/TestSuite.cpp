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


#include <robottestingframework/Exception.h>
#include <robottestingframework/TestMessage.h>
#include <robottestingframework/TestSuite.h>

#include <algorithm>

using namespace robottestingframework;

TestSuite::TestSuite(std::string name) :
        Test(name),
        successful(true),
        fixtureOK(true),
        result(nullptr),
        fixtureMessage(""),
        current(nullptr)
{
}


TestSuite::~TestSuite()
{
}

void TestSuite::addTest(Test* test)
{
    if (std::find(tests.begin(), tests.end(), test) == tests.end()) {
        tests.push_back(test);
    }
}


void TestSuite::removeTest(Test* test)
{
    for (int i = 0; i < tests.size(); i++) {
        if (tests[i] == test)
            tests.erase(tests.begin() + i);
    }
}

void TestSuite::reset()
{
    tests.clear();
    successful = fixtureOK = true;
    result = nullptr;
    fixtureMessage.clear();
}


bool TestSuite::succeeded() const
{
    return successful;
}

TestResult* TestSuite::getResult()
{
    return result;
}

std::size_t TestSuite::size() const
{
    return tests.size();
}

bool TestSuite::setup()
{
    bool ret = true;
    FixtureIterator itr;
    for (itr = fixtureManagers.begin(); (itr != fixtureManagers.end()) && ret; itr++)
        ret &= (*itr)->setup();
    return ret;
}


void TestSuite::tearDown()
{
    FixtureRIterator itr;
    for (itr = fixtureManagers.rbegin(); itr != fixtureManagers.rend(); itr++)
        (*itr)->tearDown();
}


void TestSuite::run(TestResult& rsl)
{
    this->result = &rsl;
    successful = fixtureOK = true;
    interrupted = false;
    fixtureMessage.clear();
    try {
        result->startTestSuite(this);
        // calling test suite setup
        if (!setup()) {
            result->addError(this, TestMessage("setup() failed!"));
            successful = false;
            result->endTestSuite(this);
            return;
        }

        // calling all test's run
        for (TestIterator it = tests.begin(); it != tests.end(); ++it) {
            current = *it;
            // interrupted?
            if (interrupted)
                throw TestFailureException(TestMessage("interrupted!"));

            if (!fixtureOK)
                result->addError(this, fixtureMessage);

            bool checkOk = true;
            FixtureIterator itr;
            for (itr = fixtureManagers.begin(); (itr != fixtureManagers.end()) && checkOk; itr++)
                checkOk &= (*itr)->check();
            if (!checkOk) {
                result->addError(this, TestMessage("Fixture collapsed", "check() failed", ROBOTTESTINGFRAMEWORK_SOURCEFILE(), ROBOTTESTINGFRAMEWORK_SOURCELINE()));
                fixtureOK = false;
            }

            // restart the fixture if it has been collapsed
            if (!fixtureOK) {
                successful = false;
                result->addReport(this, TestMessage("reports", "restarting fixture setup", ROBOTTESTINGFRAMEWORK_SOURCEFILE(), ROBOTTESTINGFRAMEWORK_SOURCELINE()));
                tearDown();
                if (!setup())
                    throw FixtureException(TestMessage("setup() failed!"));

                bool checkOk = true;
                FixtureIterator itr;
                for (itr = fixtureManagers.begin(); (itr != fixtureManagers.end()) && checkOk; itr++)
                    checkOk &= (*itr)->check();
                if (!checkOk)
                    throw FixtureException(TestMessage("Fixture collapsed",
                                                       "check() failed",
                                                       ROBOTTESTINGFRAMEWORK_SOURCEFILE(),
                                                       ROBOTTESTINGFRAMEWORK_SOURCELINE()));
                fixtureOK = true;
            }
            (*it)->run(*result);
            successful &= (*it)->succeeded();
        }
    } catch (TestFailureException& e) {
        successful = false;
        result->addFailure(this, e.message());
    } catch (TestErrorException& e) {
        successful = false;
        result->addError(this, e.message());
    } catch (FixtureException& e) {
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

    result->endTestSuite(this);
    current = nullptr;
}


void TestSuite::addFixtureManager(FixtureManager* manager)
{
    manager->setDispatcher(this);
    fixtureManagers.push_back(manager);
}

void TestSuite::fixtureCollapsed(TestMessage reason)
{

    // we do not want to throw any exception here.
    // The reason is that if fixtureCollapsed is called
    // within other threads, the exception cannot be caught
    // by the TestSuite.
    fixtureOK = false;
    fixtureMessage = reason;
}

void TestSuite::interrupt()
{
    if (current)
        current->interrupt();
    interrupted = true;
}
