// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_EXCEPTION_H
#define _RTF_EXCEPTION_H

#include <exception>
#include <rtf/TestMessage.h>

namespace RTF {
    class Exception;
    class TestFailureException;
    class TestErrorException;
    class FixtureException;
}

/**
 * @brief The RTF::Exception is a generic exception.
 */
class RTF::Exception : public std::exception {

public:

    Exception(const Exception& other)
        : std::exception(other) ,
        expMessage(other.expMessage),
        strMessage(other.strMessage)
    {
    }

    Exception(const RTF::TestMessage& msg)
        : expMessage(msg)
    {
        strMessage = expMessage.getMessage();
        if(expMessage.getDetail().size())
            strMessage +=  "(" + expMessage.getDetail() + ")";
    }

    virtual ~Exception() throw() { }

    /**
     * @brief what
     * @return the exception message string
     */
    virtual const char* what() const throw() {
        return strMessage.c_str();
    }

    /**
     * @brief message
     * @return the current exception message
     * as TestMessage
     */
    const RTF::TestMessage& message() {
        return expMessage;
    }

private:
    RTF::TestMessage expMessage;
    std::string strMessage;
};


/**
 * @brief The RTF::FailureException class
 * Failure exception is used when a test or subtests fail.
 */
class RTF::TestFailureException : public RTF::Exception {
public:
    TestFailureException(const RTF::TestMessage& msg)
        : Exception(msg) { }

    TestFailureException(const TestFailureException& other)
        : Exception(other) { }
};

/**
 * @brief The RTF::TestErrorException class
 * Error exception is used when test breakdown
 * due to an error in setup, teardown or any configuration.
 */
class RTF::TestErrorException : public RTF::Exception {
public:
    TestErrorException(const RTF::TestMessage& msg)
        : Exception(msg) { }

    TestErrorException(const TestErrorException& other)
        : Exception(other) { }
};


/**
 * @brief The RTF::FixtureException class
 * Ficture exception is used when a there is a
 * probleme during fixture setup.
 */
class RTF::FixtureException : public RTF::Exception {
public:
    FixtureException(const RTF::TestMessage& msg)
        : Exception(msg) { }

    FixtureException(const FixtureException& other)
        : Exception(other) { }
};

#endif // _RTF_EXCEPTION_H
