// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/TestMessage.h>

using namespace RTF;


TestMessage::TestMessage()
    : strFileName(""), lineNumber(0) {
}


TestMessage::TestMessage(const TestMessage& other) {
    *this = other;
}

TestMessage::TestMessage(const std::string msg,
                         const std::string filename,
                         unsigned int line) {
    strMessage = msg;
    strFileName = filename;
    lineNumber = line;
}

TestMessage::TestMessage(const std::string msg,
                         const std::string detail,
                         const std::string filename,
                         unsigned int line) {
    strMessage = msg;
    strDetail = detail;
    strFileName = filename;
    lineNumber = line;
}

TestMessage::~TestMessage() {

}


void TestMessage::setMessage(const std::string message) {
    strMessage = message;
}


void TestMessage::setDetail(const std::string detail) {
    strDetail = detail;
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


void TestMessage::setSourceFileName(const std::string filename) {
    strFileName = filename;
}

const std::string TestMessage::getSourceFileName() {
    return strFileName;
}

void TestMessage::clear() {
    lineNumber = 0;
    strFileName.clear();
    strMessage.clear();
    strDetail.clear();
}
