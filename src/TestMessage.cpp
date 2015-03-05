// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <TestMessage.h>

using namespace RTF;

TestMessage::TestMessage(std::string msg) {
    strMessage  = msg;
}

TestMessage::TestMessage(std::string msg, std::string detail) {
}


TestMessage::~TestMessage() {

}

std::string TestMessage::getMessage() {

}

std::string TestMessage::getDetail() {

}


void TestMessage::setSourceLineNumber(int line) {

}


int TestMessage::getSourceLineNumber() {

}


std::string TestMessage::getSourceFileName() {

}
