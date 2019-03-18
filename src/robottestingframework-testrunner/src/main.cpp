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


#include <robottestingframework/ConsoleListener.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestResultCollector.h>
#include <robottestingframework/TextOutputter.h>

#include <ErrorLogger.h>
#include <JUnitOutputter.h>
#include <SuiteRunner.h>
#include <Version.h>
#include <cmdline.h>
#include <cstdio>
#include <cstdlib>

#if defined(ENABLE_WEB_LISTENER)
#    include <robottestingframework/WebProgressListener.h>
#endif

#if defined(_WIN32)
#    include <windows.h>
#else
#    include <cerrno>
#    include <csignal>
#    include <sys/types.h>
#    include <sys/wait.h>
#    include <unistd.h>
#endif


using namespace robottestingframework;
using namespace std;

void reportErrors()
{
    ErrorLogger& logger = ErrorLogger::Instance();
    for (unsigned int i = 0; i < logger.errorCount(); i++)
        cout << "[robottestingframework-testrunner] " << logger.getLastError() << endl;
    for (unsigned int i = 0; i < logger.warningCount(); i++)
        cout << "[robottestingframework-testrunner] " << logger.getLastWarning() << endl;
}

void addOptions(cmdline::parser& cmd)
{
    cmd.add<string>("test", 't', "Runs a single test from the given plugin file.", false);

    cmd.add<string>("tests", '\0', "Runs multiple tests from the given folder which contains plugins.", false);

    cmd.add<string>("suite", 's', "Runs a single test suite from the given XML file.", false);

    cmd.add<string>("suites", '\0', "Runs multiple test suites from the given folder which contains XML files.", false);

    cmd.add<string>("suit", '\0', "Runs a single test suite from the given XML file (legacy option that will be removed in RTF 1.5, do not use).", false);

    cmd.add<string>("suits", '\0', "Runs multiple test suites from the given folder which contains XML files (legacy option that will be removed in RTF 1.5, do not use).", false);

    cmd.add("no-output", '\0', "Avoids generating any output file");

    cmd.add("no-summary", '\0', "Avoids reporting test summary");

    cmd.add<string>("output", 'o', "The output file to save the result. Default is result.txt", false, "");
    cmd.add<string>("output-type", '\0', "The output file type (text, junit)", false, "text");

    cmd.add<string>("param", 'p', "Sets the test case parameters. (Can be used only with --test option.)", false);
    cmd.add<string>("environment", 'e', "Sets the test case environment. (Can be used only with --test option.)", false);
    cmd.add<int>("repetition", '\0', "Sets the test run repetition. (Can be used only with --test option.)", false, 0);
    cmd.add("web-reporter", 'w', "Enables web reporter");
    cmd.add<int>("web-port", '\0', "Sets the web reporter server port. (The default port number is 8080.)", false, 8080);
    cmd.add("recursive", 'r', "Searches into subfolders for plugins or XML files. (Can be used with --tests or --suites options.)");
    cmd.add("detail", 'd', "Enables verbose mode of test assertions.");
    cmd.add("verbose", 'v', "Enables verbose mode.");
    cmd.add("version", '\0', "Shows version information.");
}


static TestRunner* currentRunner = nullptr;
void signalHandler(int signum)
{
    static int interuptCount = 1;
    cout << endl
         << "[robottestingframework-testrunner] (" << interuptCount << ") interrupted..." << endl
         << endl;
    if (interuptCount++ > 3) {
        cout << endl
             << "[robottestingframework-testrunner] killing the tests (interrupted for more than 3 times)!" << endl
             << endl;
        exit(EXIT_FAILURE);
    }

    if (currentRunner)
        currentRunner->interrupt();
}

#if defined(_WIN32)
BOOL CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType) {
    // Handle the CTRL-C signal.
    case CTRL_C_EVENT:
        signalHandler(0);
        return (TRUE);
    case CTRL_BREAK_EVENT:
        signalHandler(0);
        return TRUE;
    default:
        return FALSE;
    }
}
#endif

int main(int argc, char* argv[])
{

// setup signal handler to cathc ctrl+c
#if defined(_WIN32)
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);
#else
    struct sigaction new_action, old_action;
    new_action.sa_handler = signalHandler;
    sigemptyset(&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction(SIGINT, nullptr, &old_action);
    if (old_action.sa_handler != SIG_IGN)
        sigaction(SIGINT, &new_action, nullptr);
    sigaction(SIGHUP, nullptr, &old_action);
    if (old_action.sa_handler != SIG_IGN)
        sigaction(SIGHUP, &new_action, nullptr);
    sigaction(SIGTERM, nullptr, &old_action);
    if (old_action.sa_handler != SIG_IGN)
        sigaction(SIGTERM, &new_action, nullptr);
#endif

    cmdline::parser cmd;
    addOptions(cmd);
    cmd.parse_check(argc, argv);

    // print version info
    if (cmd.exist("version")) {
        cout << "robottestingframework-testrunner version " << TESTRUNNER_VERSION << endl;
        return 0;
    }

    // exit if no test or suite is given
    if (!cmd.get<string>("test").size() && !cmd.get<string>("tests").size() && !cmd.get<string>("suite").size() && !cmd.get<string>("suites").size() && !cmd.get<string>("suit").size() && !cmd.get<string>("suits").size()) {
        cout << cmd.usage();
        return EXIT_FAILURE;
    }

    // create a test runner
    SuiteRunner runner(cmd.exist("verbose"));
    currentRunner = &runner;

    // load a single plugin
    if (cmd.get<string>("test").size()) {
        if (!runner.loadPlugin(cmd.get<string>("test"),
                               (cmd.get<int>("repetition") < 0) ? 0 : cmd.get<int>("repetition"),
                               cmd.get<string>("param"),
                               cmd.get<string>("environment"))) {
            reportErrors();
            return EXIT_FAILURE;
        }
    }

    // load multiple plugins
    if (cmd.get<string>("tests").size()) {
        if (!runner.loadMultiplePlugins(cmd.get<string>("tests"),
                                        cmd.exist("recursive"))) {
            reportErrors();
            return EXIT_FAILURE;
        }
    }

    // load a single suite
    string suiteFileName = cmd.get<string>("suite");
    if (suiteFileName.empty()) {
        suiteFileName = cmd.get<string>("suit");
    }

    if (suiteFileName.size()) {
        if (!runner.loadSuite(suiteFileName)) {
            reportErrors();
            return EXIT_FAILURE;
        }
    }

    // load multiple suites
    string suitesDirectoryName = cmd.get<string>("suites");
    if (suitesDirectoryName.empty()) {
        suitesDirectoryName = cmd.get<string>("suits");
    }

    if (suitesDirectoryName.size()) {
        if (!runner.loadMultipleSuites(suitesDirectoryName,
                                       cmd.exist("recursive"))) {
            reportErrors();
            return EXIT_FAILURE;
        }
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
    if (!cmd.exist("verbose"))
        listener.hideUncriticalMessages();

        // create web listener if enabled
#if defined(ENABLE_WEB_LISTENER)
    WebProgressListener* webListener = nullptr;
#endif

    if (cmd.exist("web-reporter")) {
#if defined(ENABLE_WEB_LISTENER)
        webListener = new WebProgressListener(cmd.get<int>("web-port"),
                                              cmd.exist("detail"));
        result.addListener(webListener);
#else
        cout << "Web reporter is not enabled! (please build Robot Testing Version with ENABLE_WEB_LISTENER.)" << endl;
#endif
    }

    // create a test runner and run the test case
    runner.run(result);

    // store the results
    if (!cmd.exist("no-output")) {
        string outptType = cmd.get<string>("output-type");
        if (outptType == "text") {
            TextOutputter outputter(collector, cmd.exist("detail"));
            string output = (cmd.get<string>("output").empty()) ? "result.txt" : cmd.get<string>("output");
            TestMessage msg;
            if (!outputter.write(output, true, &msg)) {
                cout << endl
                     << msg.getMessage() << ". " << msg.getDetail() << endl;
            }
        } else if (outptType == "junit") {
            JUnitOutputter outputter(collector, cmd.exist("detail"));
            string output = (cmd.get<string>("output").empty()) ? "result.xml" : cmd.get<string>("output");
            TestMessage msg;
            if (!outputter.write(output, &msg)) {
                cout << endl
                     << msg.getMessage() << ". " << msg.getDetail() << endl;
            }
        } else {
            cout << endl
                 << "Results are not saved! Unknown output type " << outptType << "." << endl;
        }
    }

    if (!cmd.exist("no-summary")) {
        // print out some simple statistics
        cout << endl
             << "---------- results -----------" << endl;
        if (collector.suiteCount()) {
            cout << "Total number of test suites  : " << collector.suiteCount() << endl;
            cout << "Number of passed test suites : " << collector.passedSuiteCount() << endl;
            cout << "Number of failed test suites : " << collector.failedSuiteCount() << endl;
        }
        cout << "Total number of test cases   : " << collector.testCount() << endl;
        cout << "Number of passed test cases  : " << collector.passedCount() << endl;
        cout << "Number of failed test cases  : " << collector.failedCount() << endl;
    }

    currentRunner = nullptr;

    int exitCode;
    if ((collector.failedCount() == 0) && (collector.failedSuiteCount() == 0))
        exitCode = EXIT_SUCCESS;
    else
        exitCode = EXIT_FAILURE;

#if defined(ENABLE_WEB_LISTENER)
    if (webListener)
        delete webListener;
#endif

    return exitCode;
}
