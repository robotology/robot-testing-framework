// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_TESTMESSAGE_H
#define _RTF_TESTMESSAGE_H


#include <string>

namespace RTF {
    class TestMessage;
}


/**
 * @brief A formated message with details.
 */

class RTF::TestMessage {

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
    TestMessage(std::string msg,
                std::string filename="",
                unsigned int line=0);

    /**
     * @brief TestMessage construct a test message
     * @param msg the message
     * @param detail the detail of the message
     * @param filename the source file name of the
     *        code for the corresponding message
     * @param line the line number of the code for
     *        the corresponding message
     */
    TestMessage(std::string msg,
                std::string detail,
                std::string filename="",
                unsigned int line=0);


    /**
     * @brief ~TestMessage Destructor
     */
    virtual ~TestMessage ();

    /**
     * @brief setMessage sets the message
     * @param message the message string
     */
    void setMessage(std::string message);

    /**
     * @brief setDetail sets the detail of the messsage
     * @param detail the detailed message string
     */
    void setDetail(std::string detail);

    /**
     * @brief getMessage returns the message string
     * @return string
     */
    const std::string getMessage ();

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
    void setSourceFileName(std::string filename);

    /**
     * @brief getSourceFileName
     * @return the source file name of the code for
     *         the corresponding message
     */
    const std::string getSourceFileName();

private:
    unsigned int lineNumber;
    std::string strFileName;
    std::string strMessage;
    std::string strDetail;
};

#define RTF_SOURCELINE()  __LINE__
#define RTF_SOURCEFILE()  __FILE__

#endif // TESTMESSAGE_H
