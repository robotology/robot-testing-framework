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


#ifndef ROBOTTESTINGFRAMEWORK_EXCEPTION_H
#define ROBOTTESTINGFRAMEWORK_EXCEPTION_H

#include <robottestingframework/TestMessage.h>

#include <exception>

namespace robottestingframework {

/**
 * @brief The Exception is a generic exception.
 */
class Exception : public std::exception
{

public:
    Exception(const Exception& other) :
            std::exception(other),
            expMessage(other.expMessage),
            strMessage(other.strMessage)
    {
    }

    Exception(const TestMessage& msg) :
            expMessage(msg)
    {
        strMessage = expMessage.getMessage();
        if (expMessage.getDetail().size())
            strMessage += "(" + expMessage.getDetail() + ")";
    }

    virtual ~Exception() throw()
    {
    }

    /**
     * @brief what
     * @return the exception message string
     */
    const char* what() const throw() override
    {
        return strMessage.c_str();
    }

    /**
     * @brief message
     * @return the current exception message
     * as TestMessage
     */
    const TestMessage& message()
    {
        return expMessage;
    }

private:
    TestMessage expMessage;
    std::string strMessage;
};


/**
 * @brief The FailureException class
 * Failure exception is used when a test or subtests fail.
 */
class TestFailureException : public Exception
{
public:
    TestFailureException(const TestMessage& msg) :
            Exception(msg)
    {
    }

    TestFailureException(const TestFailureException& other) :
            Exception(other)
    {
    }
};


/**
 * @brief The TestErrorException class
 * Error exception is used when test breakdown
 * due to an error in setup, teardown or any configuration.
 */
class TestErrorException : public Exception
{
public:
    TestErrorException(const TestMessage& msg) :
            Exception(msg)
    {
    }

    TestErrorException(const TestErrorException& other) :
            Exception(other)
    {
    }
};


/**
 * @brief The FixtureException class
 * Ficture exception is used when a there is a
 * probleme during fixture setup.
 */
class FixtureException : public Exception
{
public:
    FixtureException(const TestMessage& msg) :
            Exception(msg)
    {
    }

    FixtureException(const FixtureException& other) :
            Exception(other)
    {
    }
};

} // namespace robottestingframework

#endif // ROBOTTESTINGFRAMEWORK_EXCEPTION_H
