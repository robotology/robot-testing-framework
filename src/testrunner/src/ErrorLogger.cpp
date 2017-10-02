// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <ErrorLogger.h>

using namespace std;

// Global static pointer used to ensure a single instance of the class.
ErrorLogger* ErrorLogger::pInstance = nullptr;


ErrorLogger& ErrorLogger::Instance() {
    if (!pInstance)
      pInstance = new ErrorLogger;
    return *pInstance;
}


void ErrorLogger::addWarning(const std::string message) {
    warnings.push_back(message);
}

void ErrorLogger::addError(const std::string message) {
    errors.push_back(message);
}


std::string ErrorLogger::getLastError() {
    if(errors.empty())
        return "";
    static string msg;
    msg = errors.back();
    errors.pop_back();
    return msg;
}

std::string ErrorLogger::getLastWarning() {
    if(warnings.empty())
        return "";
    static string msg;
    msg = warnings.back();
    warnings.pop_back();
    return msg;
}

void ErrorLogger::reset() {
    errors.clear();
    warnings.clear();
}

unsigned int ErrorLogger::errorCount() {
    return errors.size();
}

unsigned int ErrorLogger::warningCount() {

    return warnings.size();
}

