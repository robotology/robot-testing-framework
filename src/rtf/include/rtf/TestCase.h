// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTCASE_H
#define _RTF_TESTCASE_H

#include <rtf/rtf_config.h>
#include <rtf/Test.h>
#include <rtf/TestResult.h>

namespace RTF {
    class TestCase;
}


/**
 * \ingroup key_class
 *
 * \brief The base class to implememnt a test case. The user defined test
 * cases should be inherited from TestCase class and the \c run() method
 * must be overriden. The \c 'setup(int argc, char** argv)' and \c tearDown() can be also inherited
 * to implement any initialization or finalization of the test case.
 *
 * Here's an example of using a TestCase:
 * \include examples/simple.cpp
 */
class RTF_API RTF::TestCase : public RTF::Test {
public:

    /**
     * TestCase constructor
     * @param name The TestCase name
     * @param param The optional paramters for the test case
     */
    TestCase(std::string name, std::string param="");

    /**
     *  TestCase destructor
     */
    virtual ~TestCase();

    /**
     * @brief setup is called before the test run.
     * @note the first value in argv is the name of the current testcases
     * @param argc The number of the pasred argument from string paramter
     * @param argv The arguments which is parsed using string paramter
     * @return true or false depending of the test initialization
     */
    virtual bool setup(int argc, char**argv);

    /**
     * @brief tearDown is called after the test run
     */
    virtual void tearDown();

    /**
     * @brief run is called by the TestCase class
     * if setup is successfull;
     */
    virtual void run() = 0;

    /**
     * @brief interrupt interrupts the current test run
     */
    virtual void interrupt();

    /**
     * the main caller of a TestCase inherited from Test Class.
     * @param result an instance of a TestResult
     * to collect the result of the test.
     */
    void run(TestResult &result);

    /**
     * @brief succeeded
     * @return true or false representing whether the test
     * was successful or not.
     */
    bool succeeded() const;

    /**
     * @brief failed Sets the test successful flag to \c false
     *         which indicates that the test was not successful.
     */
    void failed();

    /**
     * @brief getResult Returns an instance of TestResult
     * if run(TestResult &result) has been already called
     * by a TestRunner
     * @return an instance of TestResult
     */
    RTF::TestResult* getResult();

    /**
     * @brief setParam Sets the optional paramters of the test.
     * The parameter string is parsed into (argc/argv) format
     * and will be passed to the test case using setup(int argc, char** argv).
     * @param param the paramter string
     */
    void setParam(const std::string param);

    /**
     * @brief getParam gets the original paramter string which is set
     * for the test case
     * @return a string paramter
     */
    const std::string getParam();


    /**
     * @brief setEnvironment Optioanlly specifies the environment in which
     * the test case is executed. The TestCase class does not
     * make any use of it. The environment can be used in the implementation
     * of the test cases to know in which setup (e.g., simulation,
     * real world environment) the test case is employed.
     * @param environment The optional environment string
     */
    void setEnvironment(const std::string environment);

    /**
     * @brief getParam gets the environment string which is set
     * for the test case
     * @return A environment string
     */
    const std::string getEnvironment();

    /**
     * @brief setRepetition sets the run repetition
     * by default the run() method is called only once; The number of test runs
     * (e.g., for stress testing) can be set using this function.
     * @param rep number of repetitions
     */
    void setRepetition(unsigned int rep);

    /**
     * @brief getRepetition gets the tun repetition
     * @return the number of repetitions
     */
    unsigned int getRepetition();

private:
    std::string param;
    std::string environment;
    RTF::TestResult* result;
    bool successful;
    bool interrupted;
    unsigned int repetition;
};
#endif // _RTF_TESTCASE_H
