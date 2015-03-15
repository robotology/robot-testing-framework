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

#include <tinyxml.h>
#include <cmdline.h>
#include <PluginRunner.h>
#include <ErrorLogger.h>

using namespace RTF;
using namespace std;

void reportErrors(void) {
    ErrorLogger& logger  = ErrorLogger::Instance();
    for(int i=0; i<logger.errorCount(); i++)
        cout<<"[testrunner] "<<logger.getLastError()<<endl;
}

void addOptions(cmdline::parser &cmd) {
    cmd.add<string>("plugin", 'p',
                    "plugin file name",
                    false);

    cmd.add<string>("all", 'a',
                    "path to the plugins folder",
                    false);

    cmd.add<string>("output", 'o',
                    "the output file to save the result",
                    false, "result.txt");
    cmd.add("recursive", 'r', "search subfolders for plug-ins");
    cmd.add("detail", '\0', "enable verbose mode of test assertions");
    cmd.add("verbose", '\0', "enable verbose mode");
}

int main(int argc, char *argv[]) {

    cmdline::parser cmd;
    addOptions(cmd);
    cmd.parse_check(argc, argv);
    if(!cmd.get<string>("plugin").size() &&
            !cmd.get<string>("all").size()) {
        cout<<cmd.usage();
        return 0;
    }

    // create a test runner
    PluginRunner runner(cmd.exist("verbose"));

    // load a single plugin
    if(cmd.get<string>("plugin").size())
        if(!runner.loadPlugin(cmd.get<string>("plugin"))) {
            reportErrors();
            return 0;
        }

    // load multiple plugins
    if(cmd.get<string>("all").size())
        if(!runner.loadMultiplePlugins(cmd.get<string>("all"),
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
