// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <rtf/FixtureManager.h>
#include <rtf/Arguments.h>

#include <string.h>

using namespace RTF;
using namespace std;

FixtureManager::FixtureManager(std::string param)
    : dispatcher(nullptr), param(param) {
}


FixtureManager::FixtureManager(RTF::FixtureEvents* dispatcher,
                               string param)
    : dispatcher(dispatcher), param(param) {
}

FixtureManager::~FixtureManager() { }

bool FixtureManager::setup() {
    char* szenv = new char[param.size()+1];
    strcpy(szenv, param.c_str());
    int argc = 0;
    char** argv = new char*[128]; // maximum 128
    Arguments::parse(szenv, &argc, argv);
    argv[argc]=0;
    bool ret = setup(argc, argv);
    delete [] szenv;
    delete [] argv;
    return ret;
}

bool FixtureManager::setup(int argc, char**argv) {
    return true;
}


void FixtureManager::tearDown() { }


bool FixtureManager::check() {
    return true;
}


void FixtureManager::setDispatcher(RTF::FixtureEvents* dispatcher) {
    this->dispatcher = dispatcher;
}


RTF::FixtureEvents* FixtureManager::getDispatcher() {
    return dispatcher;
}


void FixtureManager::setParam(const std::string param) {
    this->param = param;
}

const std::string FixtureManager::getParam() {
    return param;
}
