// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_FixtureManager_H
#define _RTF_FixtureManager_H

#include <rtf/rtf_config.h>
#include <string>
#include <rtf/TestResult.h>
#include <rtf/TestMessage.h>

namespace RTF {
    class FixtureManager;
    class FixtureEvents;
}


/**
 * class FixtureEvents
 */
class RTF::FixtureEvents {
public:
    /**
     * @brief fixtureCollapsed is called by a fixture manager
     *        to inform the test suit that the corresponding
     *        fixture has been collapsed.
     * @param reason An error message indicates the reason for
     *        collapsing the fixture.
     */
    virtual void fixtureCollapsed(RTF::TestMessage reason) = 0;
};


/**
 * \ingroup key_class
 *
 * \brief The FixtureManager can be used to to setup any fixture which
 * is required for the tests before executing the tests by a TestSuit.
 *
 * The \c fixtureCollapsed method of the FixtureEvents class is used by a
 * fixture manager to inform any class  which inherited from FixtureEvents
 * that the corresponding fixture has been collapsed.
 *
 * Here's an example of using a FixtureManager:
 * \include examples/simple_fixture.cpp
 */

class RTF::FixtureManager {
public:

    /**
     * @brief FixtureManager constructor
     * The parameter string is parsed into (argc/argv) format
     * and will be passed to the fixture manager using setup(int argc, char** argv).
     * @param param fixture manager optional parameters
     */
    FixtureManager(std::string param="");

    /**
     * @brief FixtureManager constructor
     * The parameter string is parsed into (argc/argv) format
     * and will be passed to the fixture manager using setup(int argc, char** argv).
     * @param dispatcher an instance of FixtureEvents
     * @param param fixture manager optional parameters
     */
    FixtureManager(RTF::FixtureEvents* dispatcher,
                   std::string param="");

    /**
     *  FixtureManager destructor
     */
    virtual ~FixtureManager();

    /**
     * @brief setup is called by a test suit.
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
   virtual bool setup(int argc, char**argv);


    /**
     * @brief tearDown is called after to stop the fixture manager
     */
    virtual void tearDown();


    /**
     * @brief setDispatcher Sets the FixtureEvents dispatcher
     * @param dispatcher an instance of FixtureEvents dispatcher
     */
    void setDispatcher(RTF::FixtureEvents* dispatcher);

    /**
     * @brief getResult returns an instance of FixtureEvents dispatcher
     * @return an instance of TestResult
     */
    RTF::FixtureEvents* getDispatcher();

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
    const std::string getParam();

private:
    std::string param;
    RTF::FixtureEvents* dispatcher;
};

#endif // _RTF_FixtureManager_H
