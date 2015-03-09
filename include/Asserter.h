// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef _RTF_ASSERTER_H
#define _RTF_ASSERTER_H


#include <Exception.h>
#include <TestMessage.h>
#include <TestResult.h>

namespace RTF {
    class Asserter;
}

class RTF::Asserter {

//    static void report(RTF::TestResult* result,
//                        RTF::TestMessage msg);

    static void fail(RTF::TestMessage msg);

    static void fail(bool shouldFail,
                       RTF::TestMessage msg);

    static void error(RTF::TestMessage msg);

    static void error(bool shouldFail,
                       RTF::TestMessage msg);
/*
    static void checkTrue(RTF::TestResult* result,
                   RTF::TestMessage msg,
                   bool shouldFail);
*/
    //static void
};

#define RTF_SOURCELINE()  __LINE__
#define RTF_SOURCEFILE()  __FILE__

#define RTF_ASSERT_FAILED(message)

#endif // _RTF_ASSERTER_H
