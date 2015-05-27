// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/TestCase.h>
#include <rtf/TestAssert.h>
#include <rtf/dll/Plugin.h>

extern "C" void rtf_test_create(void);
extern "C" bool rtf_test_setup(const char* param);
extern "C" void rtf_test_teardown(void);
extern "C" void rtf_test_run(void);

static RTF::TestCase* testInstance = NULL; 

class AdaTest : public RTF::TestCase {
public:
    AdaTest() : TestCase("AdaTest") { 
        testInstance = this; 
        rtf_test_create();
    }

    virtual ~AdaTest() { }
    
    virtual bool setup(int argc, char** argv) {
        std::string param;
        for(int i=0; i<argc; i++)
            param = param + std::string(argv[i]) + std::string(" ");        
        return rtf_test_setup(param.c_str());
    }

    virtual void tearDown() {
        rtf_test_teardown();
    }

    virtual void run() {
        rtf_test_run();
    }

    void setTestName(std::string name) {
        setName(name);
    }
};

PREPARE_PLUGIN(AdaTest);

extern "C" void rtf_test_setname(char* name) {
    RTF_ASSERT_ERROR_IF(testInstance, "testInstance is surprisingly NULL!");
    ((AdaTest*)testInstance)->setTestName(name);
}

extern "C" void rtf_test_report(char* message) {
    RTF_ASSERT_ERROR_IF(testInstance, "testInstance is surprisingly NULL!");
    RTF::Asserter::report(RTF::TestMessage("reports",
                                            message,
                                            RTF_SOURCEFILE(),
                                            RTF_SOURCELINE()), testInstance);   
}


extern "C" void rtf_test_check(unsigned int condtion, char* message) {
    RTF_ASSERT_ERROR_IF(testInstance, "testInstance is surprisingly NULL!");
    RTF::Asserter::check(condtion != 0, RTF::TestMessage("reports",
                                            message,
                                            RTF_SOURCEFILE(),
                                            RTF_SOURCELINE()), testInstance);   
}


extern "C" void rtf_assert_fail(char* message) {
    RTF::Asserter::fail(RTF::TestMessage("asserts failure with exception",
                                          message,
                                          RTF_SOURCEFILE(),
                                          RTF_SOURCELINE()));
}

extern "C" void rtf_assert_error(char* message) {
    RTF::Asserter::error(RTF::TestMessage("asserts error with exception",
                                           message,
                                           RTF_SOURCEFILE(),
                                           RTF_SOURCELINE()));
}                                            

