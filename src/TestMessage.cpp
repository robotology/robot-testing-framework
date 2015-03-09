// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <TestMessage.h>

using namespace RTF;

TestMessage::TestMessage(const TestMessage& other) {
    *this = other;
}

TestMessage::TestMessage(std::string msg,
                         std::string filename,
                         unsigned int line) {
    strMessage = msg;
    strFileName = filename;
    lineNumber = line;
}

TestMessage::TestMessage(std::string msg,
                         std::string detail,
                         std::string filename,
                         unsigned int line) {
    strMessage = msg;
    strDetail = detail;
    strFileName = filename;
    lineNumber = line;
}

TestMessage::~TestMessage() {

}

const std::string TestMessage::getMessage() {
    return strMessage;
}

const std::string TestMessage::getDetail() {
    return strDetail;
}


void TestMessage::setSourceLineNumber(unsigned int line) {
    lineNumber = line;
}


unsigned int TestMessage::getSourceLineNumber() {
    return lineNumber;
}


void TestMessage::setSourceFileName(std::string filename) {
    strFileName = filename;
}

const std::string TestMessage::getSourceFileName() {
    return strFileName;
}
