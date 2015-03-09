// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TEST_H
#define _RTF_TEST_H

#include <string>

namespace RTF {
    class Test;
    class TestResult;
}


/**
 * class Test
 */

class RTF::Test {
public:

    /**
     * Test constructor
     * @param  name The test name
     */
    Test(std::string name)
        : strName(name) {
    }

    /**
     *  Test destructor
     */
    virtual ~Test() { }

    /**
     * the main caller of a test.
     * @param result an instance of a TestResult
     * to collect the result of the test
     */
    virtual void run(RTF::TestResult &result) = 0;

    /**
     * @brief succeeded
     * @return true or false representing whether the test
     * was successful or not.
     */
    virtual bool succeeded() = 0;

private:
    std::string strName;    
};
#endif // _RTF_TEST_H
