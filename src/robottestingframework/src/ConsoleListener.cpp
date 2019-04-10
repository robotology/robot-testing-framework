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

#include <iostream>

using namespace std;
using namespace robottestingframework;

#if defined(_WIN32) || defined(NO_COLORED_CONSOLE)
#    define BLUE ""
#    define GREEN ""
#    define ORANGE ""
#    define GRAY ""
#    define RED ""
#    define ENDC ""
#else
#    define BLUE "\033[94m"
#    define GREEN "\033[92m"
#    define ORANGE "\033[93m"
#    define RED "\033[91m"
#    define GRAY "\033[30m"
#    define ENDC "\033[0m"
#endif

#define MSG_ERROR RED "[ERROR] " ENDC
#define MSG_FAIL RED "[FAIL]  " ENDC
#define MSG_REPORT GREEN "[INFO]  " ENDC

ConsoleListener::ConsoleListener(bool verbose)
{
    this->verbose = verbose;
    hideUncritical = false;
}

ConsoleListener::~ConsoleListener() = default;

void ConsoleListener::hideUncriticalMessages()
{
    hideUncritical = true;
}

void ConsoleListener::addReport(const Test* test,
                                TestMessage msg)
{
    if (hideUncritical) {
        return;
    }

    cout << MSG_REPORT << "(" << test->getName() << ") "
         << msg.getMessage() << ": " << msg.getDetail() << endl;
    if (verbose && msg.getSourceLineNumber() != 0) {
        cout << GRAY << msg.getSourceFileName() << " at " << msg.getSourceLineNumber() << "." << ENDC << endl
             << endl;
    }
}

void ConsoleListener::addError(const Test* test,
                               TestMessage msg)
{
    cout << MSG_ERROR << "(" << test->getName() << ") "
         << msg.getMessage() << ": " << msg.getDetail() << endl;
    if (verbose && msg.getSourceLineNumber() != 0) {
        cout << GRAY << msg.getSourceFileName() << " at " << msg.getSourceLineNumber() << "." << ENDC << endl
             << endl;
    }
}

void ConsoleListener::addFailure(const Test* test,
                                 TestMessage msg)
{
    cout << MSG_FAIL << "(" << test->getName() << ") "
         << msg.getMessage() << ": " << msg.getDetail() << endl;
    if (verbose && msg.getSourceLineNumber() != 0) {
        cout << GRAY << msg.getSourceFileName() << " at " << msg.getSourceLineNumber() << "." << ENDC << endl
             << endl;
    }
}

void ConsoleListener::startTest(const Test* test)
{
    if (hideUncritical) {
        return;
    }

    cout << BLUE << "Test case " << test->getName() << " started..." << ENDC << endl;
}

void ConsoleListener::endTest(const Test* test)
{
    if (hideUncritical) {
        return;
    }

    cout << BLUE << "Test case " << test->getName();
    if (test->succeeded()) {
        cout << " passed!" << ENDC << endl;
    } else {
        cout << " failed!" << ENDC << endl;
    }
}

void ConsoleListener::startTestSuite(const Test* test)
{
    if (hideUncritical) {
        return;
    }

    cout << BLUE << "Test suite " << test->getName() << " started..." << ENDC << endl;
}

void ConsoleListener::endTestSuite(const Test* test)
{
    if (hideUncritical) {
        return;
    }

    cout << BLUE << "Test suite " << test->getName();
    if (test->succeeded()) {
        cout << " passed!" << ENDC << endl;
    } else {
        cout << " failed!" << ENDC << endl;
    }
}

void ConsoleListener::startTestRunner()
{
    if (hideUncritical) {
        return;
    }

    cout << BLUE << "Starting test runner." << ENDC << endl;
}

void ConsoleListener::endTestRunner()
{
    if (hideUncritical) {
        return;
    }

    cout << BLUE << "Ending test runner." << ENDC << endl;
}
