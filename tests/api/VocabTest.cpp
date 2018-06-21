// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */
#include <rtf/TestCase.h>
#include <rtf/TestResult.h>
#include <rtf/TestResultCollector.h>
#include <rtf/TestAssert.h>
#include <rtf/ConsoleListener.h>
#include <rtf/dll/Vocab.h>

using namespace RTF;
using namespace shlibpp;

class MyTest : public TestCase {
public:
    MyTest() : TestCase("VocabTest") { }

    virtual void run() {        
        RTF_TEST_CHECK(Vocab::encode("RTF") == (int)4609106, "checking Vocab::encode()");
        RTF_TEST_CHECK(Vocab::decode( Vocab::encode("RRTF")) == "RRTF", "checking Vocab::decode()");
        RTF_TEST_CHECK(Vocab::decode( VOCAB('R','T')) == "RT", "checking VOCAB");
        RTF_TEST_CHECK(Vocab::decode( VOCAB('R','T', 'F')) == "RTF", "checking VOCAB");
        RTF_TEST_CHECK(Vocab::decode( VOCAB('R','T', 'F', 'R')) == "RTFR", "checking VOCAB");
    }
};


int main(int argc, char** argv)
{
    ConsoleListener listener;
    TestResultCollector collector;
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);

    MyTest test;
    test.TestCase::run(result);
    return collector.failedCount();
}
