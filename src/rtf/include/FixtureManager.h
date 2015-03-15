// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_FixtureManager_H
#define _RTF_FixtureManager_H

#include <string>
#include <TestResult.h>
#include <TestMessage.h>

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
 * class FixtureManager
 */
/**
 * class TestSuit
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
     * @param dispatcher an instance of FixtureEvents
     */
    FixtureManager(RTF::FixtureEvents* dispatcher) {
        this->dispatcher = dispatcher;
    }

    /**
     *  FixtureManager destructor
     */
    virtual ~FixtureManager() { }

    /**
     * @brief setup is called before to start the fixture manger
     * @return true or false depending of the test initialization
     */
    virtual bool setup() { }

    /**
     * @brief tearDown is called after to stop the fixture manager
     */
    virtual void tearDown() { }


    /**
     * @brief getResult returns an instance of TestResult
     * @return an instance of TestResult
     */
    RTF::FixtureEvents* getDispatcher() {
        return dispatcher;
    }


private:
    RTF::FixtureEvents* dispatcher;
};

#endif // _RTF_FixtureManager_H
