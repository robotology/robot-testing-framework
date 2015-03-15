// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_ERRORLOGGER_H
#define _RTF_ERRORLOGGER_H

#include <string>
#include <vector>

/**
 * class ErrorLogger (singleton)
 */
class ErrorLogger {

public:

    /**
     * @brief Instance get an instance of the
     * ErrorLogger singleton class
     * @return
     */
    static ErrorLogger& Instance();

    /**
     * @brief addWarning adds warining to the logger
     * @param message warning message
     */
    void addWarning(const std::string message);

    /**
     * @brief addError adds error to the logger
     * @param message error message
     */
    void addError(const std::string message);

    /**
     * @brief getLastError gets the last error
     * from the logger
     * @return error message
     */
    std::string getLastError();

    /**
     * @brief getLastWarning gets the last warning
     * from the logger
     * @return
     */
    std::string getLastWarning();

    /**
     * @brief reset clears logger
     */
    void reset();

    /**
     * @brief errorCount
     * @return number of errors
     */
    unsigned int errorCount(void);

    /**
     * @brief warningCount
     * @return number of warnings
     */
    unsigned int warningCount(void);

private:

    // make private constructor
    ErrorLogger() { }
    ErrorLogger(ErrorLogger const&) { }

    static ErrorLogger* pInstance;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

#endif // _RTF_ERRORLOGGER_H
