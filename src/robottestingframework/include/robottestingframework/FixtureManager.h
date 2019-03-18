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


#ifndef ROBOTTESTINGFRAMEWORK_FIXTUREMANAGER_H
#define ROBOTTESTINGFRAMEWORK_FIXTUREMANAGER_H

#include <robottestingframework/TestMessage.h>
#include <robottestingframework/TestResult.h>

#include <string>

namespace robottestingframework {

/**
 * class FixtureEvents
 */
class FixtureEvents
{
public:
    /**
     * @brief fixtureCollapsed is called by a fixture manager
     *        to inform the test suite that the corresponding
     *        fixture has been collapsed.
     * @param reason An error message indicates the reason for
     *        collapsing the fixture.
     */
    virtual void fixtureCollapsed(TestMessage reason) = 0;
};


/**
 * \ingroup key_class
 *
 * \brief The FixtureManager can be used to to setup any fixture which
 * is required for the tests before executing the tests by a TestSuite.
 *
 * The \c fixtureCollapsed method of the FixtureEvents class is used by a
 * fixture manager to inform any class  which inherited from FixtureEvents
 * that the corresponding fixture has been collapsed.
 *
 * Here's an example of using a FixtureManager:
 * \include examples/simple_fixture.cpp
 */

class FixtureManager
{
public:
    /**
     * @brief FixtureManager constructor
     * The parameter string is parsed into (argc/argv) format
     * and will be passed to the fixture manager using setup(int argc, char** argv).
     * @param param fixture manager optional parameters
     */
    FixtureManager(std::string param = "");

    /**
     * @brief FixtureManager constructor
     * The parameter string is parsed into (argc/argv) format
     * and will be passed to the fixture manager using setup(int argc, char** argv).
     * @param dispatcher an instance of FixtureEvents
     * @param param fixture manager optional parameters
     */
    FixtureManager(FixtureEvents* dispatcher,
                   std::string param = "");

    /**
     *  FixtureManager destructor
     */
    virtual ~FixtureManager();

    /**
     * @brief setup is called by a test suite.
     * The setup() function parses the fixture paramteres
     * and call the setup(int argc, char**argv) which can be
     * ovveriden by the user customized fixture manager.
     * @return true or false depending of the test initialization
     */
    bool setup();

    /**
    * @brief setup is called to start the fixture manager
    * @param argc The number of the pasred argument from string parameter
    * @param argv The arguments which is parsed using string parameter
    * @return true or false depending of the fixture initialization
    */
    virtual bool setup(int argc, char** argv);

    /**
     * @brief tearDown is called after to stop the fixture manager
     */
    virtual void tearDown();

    /**
     * @brief check if the fixture is okay. This is called
     * automatically from the corresponding test suite to ensure
     * the correctness of the fixture before running each test case.
     * @return true or false depending of correctness of the fixture
     */
    virtual bool check();

    /**
     * @brief setDispatcher Sets the FixtureEvents dispatcher
     * @param dispatcher an instance of FixtureEvents dispatcher
     */
    void setDispatcher(FixtureEvents* dispatcher);

    /**
     * @brief getResult returns an instance of FixtureEvents dispatcher
     * @return an instance of TestResult
     */
    FixtureEvents* getDispatcher();

    /**
     * @brief setParam Sets the optional paramters of the fixture manager.
     * The parameter string is parsed into (argc/argv) format
     * and will be passed to the fixture manager using setup(int argc, char** argv).
     * @param param the parameter string
     */
    void setParam(const std::string param);

    /**
     * @brief getParam gets the original parameter string which is set
     * for the fixture manager
     * @return a string parameter
     */
    std::string getParam();

private:
    std::string param;
    FixtureEvents* dispatcher;
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_FIXTUREMANAGER_H
