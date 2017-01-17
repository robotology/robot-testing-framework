// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <cstdlib>
#include <stdio.h>

#include <rtf/TestResult.h>
#include <rtf/ConsoleListener.h>
#include <rtf/TestResultCollector.h>
#include <rtf/TextOutputter.h>
#include <JUnitOutputter.h>

#include <cmdline.h>
#include <SuitRunner.h>
#include <ErrorLogger.h>
#include <Version.h>

#if defined(ENABLE_WEB_LISTENER)
    #include <rtf/WebProgressListener.h>
#endif

#if defined(WIN32)
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <errno.h>
    #include <sys/types.h>
    #include <signal.h>
#endif


using namespace RTF;
using namespace std;

void reportErrors(void) {
    ErrorLogger& logger  = ErrorLogger::Instance();
    for(unsigned int i=0; i<logger.errorCount(); i++)
        cout<<"[testrunner] "<<logger.getLastError()<<endl;
    for(unsigned int i=0; i<logger.warningCount(); i++)
        cout<<"[testrunner] "<<logger.getLastWarning()<<endl;
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
                    "Runs multiple test suits from the given folder which contains XML files.",
                    false);

    cmd.add("no-output", '\0',
            "Avoids generating any output file");

    cmd.add<string>("output", 'o',
                    "The output file to save the result. Default is result.txt",
                    false, "");
    cmd.add<string>("output-type", '\0',
                    "The output file type (text, junit)",
                    false, "text");

    cmd.add<string>("param", 'p',
                    "Sets the test case parameters. (Can be used only with --test option.)",
                    false);
    cmd.add<string>("environment", 'e',
                    "Sets the test case environment. (Can be used only with --test option.)",
                    false);
    cmd.add<int>("repetition", '\0',
                    "Sets the test run repetition. (Can be used only with --test option.)",
                    false, 0);
    cmd.add("web-reporter", 'w',
            "Enables web reporter");
    cmd.add<int>("web-port", '\0',
                    "Sets the web reporter server port. (The default port number is 8080.)",
                    false, 8080);
    cmd.add("recursive", 'r',
            "Searches into subfolders for plugins or XML files. (Can be used with --tests or --suits options.)");
    cmd.add("detail", 'd',
            "Enables verbose mode of test assertions.");
    cmd.add("verbose", 'v',
            "Enables verbose mode.");
    cmd.add("version", '\0',
            "Shows version information.");
}


static TestRunner* currentRunner = NULL;
void signalHandler(int signum) {
    static int interuptCount = 1;
    cout<<endl<<"[testrunner] ("<<interuptCount<<") interrupted..."<<endl<<endl;
    if(interuptCount++ > 3) {
        cout<<endl<<"[testrunner] killing the tests (interrupted for more than 3 times)!"<<endl<<endl;
        exit(EXIT_FAILURE);
    }

    if(currentRunner)
        currentRunner->interrupt();
}

#if defined(WIN32)
BOOL CtrlHandler( DWORD fdwCtrlType ) {
  switch( fdwCtrlType ) {
    // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        signalHandler(0);
        return(TRUE);
    case CTRL_BREAK_EVENT:
        signalHandler(0);
      return TRUE;
    default:
      return FALSE;
  }
}
#endif

int main(int argc, char *argv[]) {

// setup signal handler to cathc ctrl+c
#if defined(WIN32)
     SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandler, TRUE);
#else
    struct sigaction new_action, old_action;
    new_action.sa_handler = signalHandler;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction (SIGINT, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
        sigaction (SIGINT, &new_action, NULL);
    sigaction (SIGHUP, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
        sigaction (SIGHUP, &new_action, NULL);
    sigaction (SIGTERM, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN)
        sigaction (SIGTERM, &new_action, NULL);
#endif

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
    SuitRunner runner(cmd.exist("verbose"));
    currentRunner = &runner;

    // load a single plugin
    if(cmd.get<string>("test").size())
        if(!runner.loadPlugin(cmd.get<string>("test"),
                              (cmd.get<int>("repetition")<0) ? 0 : cmd.get<int>("repetition"),
                              cmd.get<string>("param"),
                              cmd.get<string>("environment"))) {
            reportErrors();
            return EXIT_FAILURE;
        }

    // load multiple plugins
    if(cmd.get<string>("tests").size())
        if(!runner.loadMultiplePlugins(cmd.get<string>("tests"),
                                       cmd.exist("recursive"))) {
            reportErrors();
            return EXIT_FAILURE;
        }

    // load a single suit
    if(cmd.get<string>("suit").size())
        if(!runner.loadSuit(cmd.get<string>("suit"))) {
            reportErrors();
            return EXIT_FAILURE;
        }

    // load multiple suits
    if(cmd.get<string>("suits").size())
        if(!runner.loadMultipleSuits(cmd.get<string>("suits"),
                                       cmd.exist("recursive"))) {
            reportErrors();
            return EXIT_FAILURE;
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
    result.addListener(&listener);
    if(!cmd.exist("verbose"))
        listener.hideUncriticalMessages();

    // create web listener if enabled
#if defined(ENABLE_WEB_LISTENER)
    WebProgressListener* webListener = NULL;
#endif

    if(cmd.exist("web-reporter")) {
#if defined(ENABLE_WEB_LISTENER)
        webListener = new WebProgressListener(cmd.get<int>("web-port"),
                                              cmd.exist("detail"));
        result.addListener(webListener);
#else
        cout<<"Web reporter is not enabled! (please build RTF with ENABLE_WEB_LISTENER.)"<<endl;
#endif
    }

    // create a test runner and run the test case
    runner.run(result);

    // store the results
    if(!cmd.exist("no-output")) {
        string outptType = cmd.get<string>("output-type");
        if (outptType == "text") {
            TextOutputter outputter(collector, cmd.exist("detail"));
            string output = (cmd.get<string>("output").size() == 0) ? "result.txt" : cmd.get<string>("output");
            RTF::TestMessage msg;
            if(!outputter.write(output, true, &msg))
                cout<<endl<<msg.getMessage()<<". "<<msg.getDetail()<<endl;
        } else if (outptType == "junit") {
            JUnitOutputter outputter(collector, cmd.exist("detail"));
            string output = (cmd.get<string>("output").size() == 0) ? "result.xml" : cmd.get<string>("output");
            RTF::TestMessage msg;
            if(!outputter.write(output, &msg)) {
                cout<<endl<<msg.getMessage()<<". "<<msg.getDetail()<<endl;
            }
        }else
            cout<<endl<<"Results are not saved! Unknown output type "<<outptType<<"."<<endl;
    }

    // print out some simple statistics
    cout<<endl<<"---------- results -----------"<<endl;
    if(collector.suitCount()) {
    cout<<"Total number of test suites  : "<<collector.suitCount()<<endl;
    cout<<"Number of passed test suites : "<<collector.passedSuitCount()<<endl;
    cout<<"Number of failed test suites : "<<collector.failedSuitCount()<<endl;
    }
    cout<<"Total number of test cases   : "<<collector.testCount()<<endl;
    cout<<"Number of passed test cases  : "<<collector.passedCount()<<endl;
    cout<<"Number of failed test cases  : "<<collector.failedCount()<<endl;

    currentRunner = NULL;

    int exitCode;
    if( (collector.failedCount() == 0)  &&
        (collector.failedSuitCount() == 0))
        exitCode = EXIT_SUCCESS;
    else
        exitCode = EXIT_FAILURE;

#if defined(ENABLE_WEB_LISTENER)
    if(webListener)
        delete webListener;
#endif

    return exitCode;
}
