// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <iostream>
#include <rtf/ConsoleListener.h>

using namespace std;
using namespace RTF;

#if defined(WIN32) || defined(NO_COLORED_CONSOLE)
#define BLUE    ""
#define GREEN   ""
#define ORANGE  ""
#define GRAY    ""
#define RED     ""
#define ENDC    ""
#else
    #define BLUE    "\033[94m"
    #define GREEN   "\033[92m"
    #define ORANGE  "\033[93m"
    #define RED     "\033[91m"
    #define GRAY    "\033[30m"
    #define ENDC    "\033[0m"
#endif

#define MSG_ERROR   RED   "[ERROR] " ENDC
#define MSG_FAIL    RED   "[FAIL]  " ENDC
#define MSG_REPORT  GREEN "[INFO]  " ENDC

ConsoleListener::ConsoleListener(bool verbose) {
    this->verbose = verbose;
}

ConsoleListener::~ConsoleListener() {
}

void ConsoleListener::addReport(const RTF::Test* test,
                                RTF::TestMessage msg) {
    cout<<MSG_REPORT<<"("<<test->getName()<<") "
        <<msg.getMessage()<<": "<<msg.getDetail()<<endl;
    if(verbose && msg.getSourceLineNumber() != 0)
        cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void ConsoleListener::addError(const RTF::Test* test,
                               RTF::TestMessage msg) {
    cout<<MSG_ERROR<<"("<<test->getName()<<") "
        <<msg.getMessage()<<": "<<msg.getDetail()<<endl;
    if(verbose && msg.getSourceLineNumber() != 0)
        cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void ConsoleListener::addFailure(const RTF::Test* test,
                                 RTF::TestMessage msg) {
    cout<<MSG_FAIL<<"("<<test->getName()<<") "
        <<msg.getMessage()<<": "<<msg.getDetail()<<endl;
    if(verbose && msg.getSourceLineNumber() != 0)
        cout<<GRAY<<msg.getSourceFileName()<<" at "<<msg.getSourceLineNumber()<<"."<<ENDC<<endl<<endl;
}

void ConsoleListener::startTest(const RTF::Test* test) {
    cout<<BLUE<<"Test case "<<test->getName()<<" started..."<<ENDC<<endl;
}

void ConsoleListener::endTest(const RTF::Test* test) {
    cout<<BLUE<<"Test case "<<test->getName();
    if(test->succeeded())
        cout<<" passed!"<<ENDC<<endl;
    else
        cout<<" failed!"<<ENDC<<endl;
}

void ConsoleListener::startTestSuit(const RTF::Test* test) {
    cout<<BLUE<<"Test suit "<<test->getName()<<" started..."<<ENDC<<endl;
}

void ConsoleListener::endTestSuit(const RTF::Test* test) {
    cout<<BLUE<<"Test suit "<<test->getName();
    if(test->succeeded())
        cout<<" passed!"<<ENDC<<endl;
    else
        cout<<" failed!"<<ENDC<<endl;
}

void ConsoleListener::startTestRunner() {
    cout<<BLUE<<"Staring test runner."<<ENDC<<endl;
}

void ConsoleListener::endTestRunner() {
    cout<<BLUE<<"Ending test runner."<<ENDC<<endl;
}

