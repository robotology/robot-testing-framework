// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TEST_H
#define _RTF_TEST_H

#include <rtf/rtf_config.h>
#include <string>

namespace RTF {
    class Test;
    class TestResult;
}


/**
 * @brief The simplest form of a test unit
 */
class RTF_API RTF::Test {
public:

    /**
     * Test constructor
     * @param name The test name
     * @param description An optional string which describes
     * the test
     */
    Test(std::string name,
         std::string description="")
        : strName(name), strDescription(description) {
    }

    /**
     *  Test destructor
     */
    virtual ~Test() { }

    /**
     * @brief getName Getting test name.
     * @return The name of the test.
     */
    const std::string getName() const {
        return strName;
    }

    /**
     * @brief getDescription Getting test description
     * @return The description of the test
     */
    const std::string getDescription() const {
        return strDescription;
    }

    /**
     * @brief setDescription Sets an optional string which
     * describes the test.
     * @param description The description string
     */
    void setDescription(const std::string description) {
        strDescription = description;
    }

    /**
     * the main caller of a test.
     * @param result an instance of a TestResult
     * to collect the result of the test
     */
    virtual void run(RTF::TestResult &result) = 0;

    /**
     * @brief interrupt interrupts the current test run
     */
    virtual void interrupt() { }

    /**
     * @brief succeeded
     * @return true or false representing whether the test
     * was successful or not.
     */
    virtual bool succeeded() const = 0;

protected:
    /**
     * @brief setName setting the test name
     * @param name the test name
     */
    void setName(std::string name) {
        strName = name;
    }

private:
    std::string strName;
    std::string strDescription;
};
#endif // _RTF_TEST_H
