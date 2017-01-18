// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <rtf/TestAssert.h>
#include <rtf/TestRunner.h>
#include <rtf/dll/Plugin.h>
#include <rtf/python/PythonPluginLoader.h>
#include <rtf/TestResultCollector.h>

using namespace RTF;
using namespace RTF::plugin;

class PythonPlugin : public RTF::TestCase {
private:
    PythonPluginLoader loader;
    TestCase* test;

public:
    PythonPlugin() : TestCase("PythonPlugin") {}

    virtual bool setup(int argc, char**argv) {
        RTF_ASSERT_ERROR_IF(argc>=2, "Missing lua test file as argument");
        RTF_TEST_REPORT(Asserter::format("Loading lua file %s", argv[1]));
        test = loader.open(argv[1]);
        RTF_ASSERT_ERROR_IF(test!=NULL, Asserter::format("Cannot load %s", argv[1]));
        return true;
    }

    virtual void run() {

        TestResultCollector collector;

        // create a test result and add the listeners
        TestResult result;
        result.addListener(&collector);

        // calling a test case
        test->run(result);

        //RTF_TEST_REPORT(Asserter::format("count: %d", collector.failedCount()));
        RTF_TEST_CHECK(collector.passedCount() == 1, "Checking passed count");
        RTF_TEST_CHECK(collector.failedCount() == 0, "Checking failed count");
    }
};

PREPARE_PLUGIN(PythonPlugin)
