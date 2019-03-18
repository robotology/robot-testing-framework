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


#include <robottestingframework/TestMessage.h>

using namespace robottestingframework;


TestMessage::TestMessage() :
        strFileName(""), lineNumber(0)
{
}


TestMessage::TestMessage(const TestMessage& other)
{
    *this = other;
}

TestMessage::TestMessage(const std::string msg,
                         const std::string filename,
                         unsigned int line)
{
    strMessage = msg;
    strFileName = filename;
    lineNumber = line;
}

TestMessage::TestMessage(const std::string msg,
                         const std::string detail,
                         const std::string filename,
                         unsigned int line)
{
    strMessage = msg;
    strDetail = detail;
    strFileName = filename;
    lineNumber = line;
}

TestMessage::~TestMessage() = default;


void TestMessage::setMessage(const std::string message)
{
    strMessage = message;
}


void TestMessage::setDetail(const std::string detail)
{
    strDetail = detail;
}

const std::string TestMessage::getMessage()
{
    return strMessage;
}

const std::string TestMessage::getDetail()
{
    return strDetail;
}


void TestMessage::setSourceLineNumber(unsigned int line)
{
    lineNumber = line;
}


unsigned int TestMessage::getSourceLineNumber()
{
    return lineNumber;
}


void TestMessage::setSourceFileName(const std::string filename)
{
    strFileName = filename;
}

const std::string TestMessage::getSourceFileName()
{
    return strFileName;
}

void TestMessage::clear()
{
    lineNumber = 0;
    strFileName.clear();
    strMessage.clear();
    strDetail.clear();
}
