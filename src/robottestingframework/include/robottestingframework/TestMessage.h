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


#ifndef ROBOTTESTINGFRAMEWORK_TESTMESSAGE_H
#define ROBOTTESTINGFRAMEWORK_TESTMESSAGE_H

#include <string>

namespace robottestingframework {

/**
 * @brief A formated message with details.
 */
class TestMessage
{
public:
    /**
     * @brief TestMessage construct an emty test message
     */
    TestMessage();

    /**
     * Copy constructor
     * @param other a TestMessage
     */
    TestMessage(const TestMessage& other);


    /**
     * @brief TestMessage construct a test message
     * @param msg the message
     * @param filename the source file name of the
     *        code for the corresponding message
     * @param line the line number of the code for
     *        the corresponding message
     */
    TestMessage(const std::string msg,
                const std::string filename = "",
                unsigned int line = 0);

    /**
     * @brief TestMessage construct a test message
     * @param msg the message
     * @param detail the detail of the message
     * @param filename the source file name of the
     *        code for the corresponding message
     * @param line the line number of the code for
     *        the corresponding message
     */
    TestMessage(const std::string msg,
                const std::string detail,
                const std::string filename = "",
                unsigned int line = 0);


    /**
     * @brief ~TestMessage Destructor
     */
    virtual ~TestMessage();

    /**
     * @brief setMessage sets the message
     * @param message the message string
     */
    void setMessage(const std::string message);

    /**
     * @brief setDetail sets the detail of the messsage
     * @param detail the detailed message string
     */
    void setDetail(const std::string detail);

    /**
     * @brief getMessage returns the message string
     * @return string
     */
    const std::string getMessage();

    /**
     * @brief getMessage returns the detail string
     * @return string
     */
    const std::string getDetail();


    /**
     * @brief setSourceLineNumber set the line number
     *        of the code for the corresponding message
     * @param line number
     */
    void setSourceLineNumber(unsigned int line);


    /**
     * @brief getSourceLineNumber
     * @return the line number of the code for
     *         the corresponding message
     */
    unsigned int getSourceLineNumber();


    /**
     * @brief setSourceFileName set the source file name
     *        of the code for the corresponding message
     * @param filename source file name
     */
    void setSourceFileName(const std::string filename);

    /**
     * @brief getSourceFileName
     * @return the source file name of the code for
     *         the corresponding message
     */
    const std::string getSourceFileName();

    /**
     * @brief clears the test message
     */
    void clear();

private:
    unsigned int lineNumber;
    std::string strFileName;
    std::string strMessage;
    std::string strDetail;
};

} // namespace robottestingframework

#define ROBOTTESTINGFRAMEWORK_SOURCELINE() __LINE__
#define ROBOTTESTINGFRAMEWORK_SOURCEFILE() __FILE__

#endif // ROBOTTESTINGFRAMEWORK_TESTMESSAGE_H
