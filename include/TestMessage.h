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
 * class TestMessage 
 */

class RTF::TestMessage {

public:

    /**
     * Copy constructor
     * @param other a TestMessage
     */
    TestMessage(const TestMessage& other);

    /**
     * @param msg
     * @param filename
     * @param line
     */
    TestMessage(std::string msg,
                std::string filename="",
                unsigned int line=0);

    /**
     * @param msg
     * @param detail
     * @param filename
     * @param line
     */
    TestMessage(std::string msg,
                std::string detail,
                std::string filename="",
                unsigned int line=0);

    virtual ~TestMessage ();

    /**
     * @return string
     */
    const std::string getMessage ();

    /**
     * @return string
     */
    const std::string getDetail();


    /**
     * @param  line
     */
    void setSourceLineNumber(unsigned int line);


    /**
     * @return int
     */
    unsigned int getSourceLineNumber();


    /**
     * @param string
     */
    void setSourceFileName(std::string filename);

    /**
     * @return string
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
