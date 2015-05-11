// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_RESULTEVENT_H
#define _RTF_RESULTEVENT_H

#include <rtf/rtf_config.h>
#include <rtf/Test.h>
#include <rtf/TestMessage.h>

namespace RTF {
    class ResultEvent;
    class ResultEventReport;
    class ResultEventFailure;
    class ResultEventError;
    class ResultEventStartTest;
    class ResultEventEndTest;
    class ResultEventStartSuit;
    class ResultEventEndSuit;
}


/**
 * @brief The ResultEvent class is used by a test collector
 * to collect the result of the tests and the corresponding messages
 * issued during the test run.
 */
class RTF_API RTF::ResultEvent {
public:
    /**
     * @brief ResultEvent constructor
     */
    ResultEvent() : test(NULL) {
    }

    /**
     * @brief ~ResultEvent Destructor
     */
    virtual ~ResultEvent() { }

    /**
     * @brief ResultEvent constructor
     * @param test pointer to a Test
     * @param msg  the corresponding message issued by the test
     */
    ResultEvent(const RTF::Test* test, RTF::TestMessage msg) {
        ResultEvent::test = test;
        ResultEvent::message = msg;
    }

    /**
     * @brief getTest get the test
     * @return a pointer to a Test
     */
    const RTF::Test* getTest() {
        return test;
    }

    /**
     * @brief getMessage get the corresponding message
     * @return a TestMessage
     */
    RTF::TestMessage& getMessage() {
        return message;
    }

private:
    const RTF::Test* test;
    RTF::TestMessage message;
};


/**
 * @brief The ResultEventReport class keeps a test report event
 */
class RTF_API RTF::ResultEventReport : public RTF::ResultEvent {
public:
    ResultEventReport(const RTF::Test* test, RTF::TestMessage msg)
        : ResultEvent(test, msg) {}
};


/**
 * @brief The ResultEventError class keeps a test error event
 */
class RTF_API RTF::ResultEventError : public RTF::ResultEvent {
public:
    ResultEventError(const RTF::Test* test, RTF::TestMessage msg)
        : ResultEvent(test, msg) {}
};

/**
 * @brief The ResultEventFailure class keeps a failure event
 */
class RTF_API RTF::ResultEventFailure : public ResultEvent {
public:
   ResultEventFailure(const RTF::Test* test, RTF::TestMessage msg)
        : ResultEvent(test, msg) {}
};

/**
 * @brief The ResultEventStartTest class keeps a test starting event
 */
class RTF_API RTF::ResultEventStartTest : public RTF::ResultEvent {
public:
    ResultEventStartTest(const RTF::Test* test, RTF::TestMessage msg)
        : ResultEvent(test, msg) {}
};

/**
 * @brief The ResultEventEndTest class keeps a test ending event
 */
class RTF_API RTF::ResultEventEndTest : public RTF::ResultEvent {
public:
    ResultEventEndTest(const RTF::Test* test, RTF::TestMessage msg)
        : ResultEvent(test, msg) {}
};

/**
 * @brief The ResultEventStartSuit class keeps a test suit starting event
 */
class RTF_API RTF::ResultEventStartSuit : public RTF::ResultEvent {
public:
    ResultEventStartSuit(const RTF::Test* test, RTF::TestMessage msg)
        : ResultEvent(test, msg) {}
};


/**
 * @brief The ResultEventEndSuit class keeps a test suit ending event
 */
class RTF_API RTF::ResultEventEndSuit : public RTF::ResultEvent {
public:
    ResultEventEndSuit(const RTF::Test* test, RTF::TestMessage msg)
        : ResultEvent(test, msg) {}
};


#endif // _RTF_TESTRESUTEVENT_H
