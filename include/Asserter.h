// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan and Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_ASSERTER_H
#define _RTF_ASSERTER_H


#include <Exception.h>
#include <TestMessage.h>
#include <TestCase.h>

namespace RTF {
    class Asserter;
}

class RTF::Asserter {

public:
    static void fail(RTF::TestMessage msg);

    static void fail(bool condition,
                       RTF::TestMessage msg);

    static void error(RTF::TestMessage msg);

    static void error(bool condition,
                       RTF::TestMessage msg);

    static void report(RTF::TestMessage msg,
                        RTF::TestCase* testcase);

    static void check(bool condition,
                      RTF::TestMessage msg,
                      RTF::TestCase* testcase);

    /**
     * @brief format can be used to format data to in
     *        the same way that \c sprintf formats.
     * @param msg a format-control string
     * @return the formated std::string
     */
    static std::string format(const char* msg, ...);
};

#endif // _RTF_ASSERTER_H
