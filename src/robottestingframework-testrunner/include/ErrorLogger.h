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


#ifndef ROBOTTESTINGFRAMEWORK_ERRORLOGGER_H
#define ROBOTTESTINGFRAMEWORK_ERRORLOGGER_H

#include <string>
#include <vector>

/**
 * class ErrorLogger (singleton)
 */
class ErrorLogger
{

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
    ErrorLogger()
    {
    }
    ErrorLogger(ErrorLogger const&)
    {
    }

    static ErrorLogger* pInstance;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

#endif // ROBOTTESTINGFRAMEWORK_ERRORLOGGER_H
