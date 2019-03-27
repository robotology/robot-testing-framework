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


#ifndef ROBOTTESTINGFRAMEWORK_RESULTEVENT_H
#define ROBOTTESTINGFRAMEWORK_RESULTEVENT_H

#include <robottestingframework/Test.h>
#include <robottestingframework/TestMessage.h>

namespace robottestingframework {

/**
 * @brief The ResultEvent class is used by a test collector
 * to collect the result of the tests and the corresponding messages
 * issued during the test run.
 */
class ResultEvent
{
public:
    /**
     * @brief ResultEvent constructor
     */
    ResultEvent() :
            test(nullptr)
    {
    }

    /**
     * @brief ~ResultEvent Destructor
     */
    virtual ~ResultEvent() = default;

    /**
     * @brief ResultEvent constructor
     * @param test pointer to a Test
     * @param msg  the corresponding message issued by the test
     */
    ResultEvent(const Test* test, TestMessage msg)
    {
        ResultEvent::test = test;
        ResultEvent::message = msg;
    }

    /**
     * @brief getTest get the test
     * @return a pointer to a Test
     */
    const Test* getTest()
    {
        return test;
    }

    /**
     * @brief getMessage get the corresponding message
     * @return a TestMessage
     */
    TestMessage& getMessage()
    {
        return message;
    }

private:
    const Test* test;
    TestMessage message;
};


/**
 * @brief The ResultEventReport class keeps a test report event
 */
class ResultEventReport : public ResultEvent
{
public:
    ResultEventReport(const Test* test, TestMessage msg) :
            ResultEvent(test, msg)
    {
    }
};


/**
 * @brief The ResultEventError class keeps a test error event
 */
class ResultEventError : public ResultEvent
{
public:
    ResultEventError(const Test* test, TestMessage msg) :
            ResultEvent(test, msg)
    {
    }
};

/**
 * @brief The ResultEventFailure class keeps a failure event
 */
class ResultEventFailure : public ResultEvent
{
public:
    ResultEventFailure(const Test* test, TestMessage msg) :
            ResultEvent(test, msg)
    {
    }
};

/**
 * @brief The ResultEventStartTest class keeps a test starting event
 */
class ResultEventStartTest : public ResultEvent
{
public:
    ResultEventStartTest(const Test* test, TestMessage msg) :
            ResultEvent(test, msg)
    {
    }
};

/**
 * @brief The ResultEventEndTest class keeps a test ending event
 */
class ResultEventEndTest : public ResultEvent
{
public:
    ResultEventEndTest(const Test* test, TestMessage msg) :
            ResultEvent(test, msg)
    {
    }
};

/**
 * @brief The ResultEventStartSuite class keeps a test suite starting event
 */
class ResultEventStartSuite : public ResultEvent
{
public:
    ResultEventStartSuite(const Test* test, TestMessage msg) :
            ResultEvent(test, msg)
    {
    }
};


/**
 * @brief The ResultEventEndSuite class keeps a test suite ending event
 */
class ResultEventEndSuite : public ResultEvent
{
public:
    ResultEventEndSuite(const Test* test, TestMessage msg) :
            ResultEvent(test, msg)
    {
    }
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_TESTRESUTEVENT_H
