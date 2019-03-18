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


#include <ErrorLogger.h>

using namespace std;

// Global static pointer used to ensure a single instance of the class.
ErrorLogger* ErrorLogger::pInstance = nullptr;


ErrorLogger& ErrorLogger::Instance()
{
    if (!pInstance)
        pInstance = new ErrorLogger;
    return *pInstance;
}


void ErrorLogger::addWarning(const std::string message)
{
    warnings.push_back(message);
}

void ErrorLogger::addError(const std::string message)
{
    errors.push_back(message);
}


std::string ErrorLogger::getLastError()
{
    if (errors.empty())
        return "";
    static string msg;
    msg = errors.back();
    errors.pop_back();
    return msg;
}

std::string ErrorLogger::getLastWarning()
{
    if (warnings.empty())
        return "";
    static string msg;
    msg = warnings.back();
    warnings.pop_back();
    return msg;
}

void ErrorLogger::reset()
{
    errors.clear();
    warnings.clear();
}

unsigned int ErrorLogger::errorCount()
{
    return errors.size();
}

unsigned int ErrorLogger::warningCount()
{

    return warnings.size();
}
