// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdio.h>
#include <TestCase.h>
#include <TestResult.h>
#include <TestRunner.h>
#include <ConsoleListener.h>
#include <TestResultCollector.h>
#include <TextOutputter.h>

#include <cmdline.h>
#include <PluginRunner.h>
#include <SuitRunner.h>
#include <ErrorLogger.h>
#include <Version.h>

using namespace RTF;
using namespace std;

void reportErrors(void) {
    ErrorLogger& logger  = ErrorLogger::Instance();
    for(int i=0; i<logger.errorCount(); i++)
        cout<<"[testrunner] "<<logger.getLastError()<<endl;
}

void addOptions(cmdline::parser &cmd) {
    cmd.add<string>("test", 't',
                    "Runs a single test from the given plugin file.",
                    false);

    cmd.add<string>("tests", '\0',
                    "Runs multiple tests from the given folder which contains plugins.",
                    false);

    cmd.add<string>("suit", 's',
                    "Runs a single test suit from the given XMl file.",
                    false);

    cmd.add<string>("suits", '\0',
                    "Runs multiple tests from the given folder which contains XML files.",
                    false);

    cmd.add<string>("output", 'o',
                    "The output file to save the result",
                    false, "result.txt");
    cmd.add("recursive", 'r',
            "Search into subfolders for plugins or XML files. (Can be used with --tests or --suits options.)");
    cmd.add("detail", '\0',
            "Enables verbose mode of test assertions.");
    cmd.add("verbose", '\0',
            "Enables verbose mode.");
    cmd.add("version", '\0',
            "Shows version information.");
}

int main(int argc, char *argv[]) {

    cmdline::parser cmd;
    addOptions(cmd);
    cmd.parse_check(argc, argv);

    // print version info
    if(cmd.exist("version")) {
        cout<<"testrunner version "<<TESTRUNNER_VERSION<<endl;
        return 0;
    }

    // exit if no test or suit is given
    if(!cmd.get<string>("test").size() &&
            !cmd.get<string>("tests").size() &&
            !cmd.get<string>("suit").size() &&
            !cmd.get<string>("suits").size()) {
        cout<<cmd.usage();
        return 0;
    }

    // create a test runner
    PluginRunner runner(cmd.exist("verbose"));

    // load a single plugin
    if(cmd.get<string>("test").size())
        if(!runner.loadPlugin(cmd.get<string>("test"))) {
            reportErrors();
            return 0;
        }

    // load multiple plugins
    if(cmd.get<string>("tests").size())
        if(!runner.loadMultiplePlugins(cmd.get<string>("tests"),
                                       cmd.exist("recursive"))) {
            reportErrors();
            return 0;
        }

    // report any warning or errors
    reportErrors();

    // create a test result collector to collect the result
    TestResultCollector collector;

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&collector);

    // create a test listener to collect the result
    ConsoleListener listener(cmd.exist("detail"));
    if(cmd.exist("verbose"))
        result.addListener(&listener);

    // create a test runner and run the test case
    runner.run(result);

    // store the results in a text file
    TextOutputter outputter(collector);
    outputter.write(cmd.get<string>("output"));

    return 0;
}
