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

class RTF::TestMessage
{
public:

    /**
     * @param  msg
     */
    TestMessage(std::string msg);

    /**
     * @param  msg
     * @param  detail
     */
    TestMessage (std::string msg, std::string detail);


    virtual ~TestMessage ();

    /**
     * @return string
     */
    std::string getMessage ();

    /**
     * @return string
     */
    std::string getDetail();


    /**
     * @param  line
     */
    void setSourceLineNumber(int line);


    /**
     * @return int
     */
    int getSourceLineNumber();


    /**
     * @return string
     */
    std::string getSourceFileName();

private:
    unsigned int lineNumber;
    std::string strMessage;
    std::string strDetail;
};

#endif // TESTMESSAGE_H
