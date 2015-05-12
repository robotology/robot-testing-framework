// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef _MYTEST_H_
#define _MYTEST_H_

#include <rtf/TestCase.h>

class MyTest : public RTF::TestCase {
public:
    MyTest();
    virtual ~MyTest();

    virtual bool setup(int argc, char** argv);

    virtual void tearDown();

    virtual void run();
};

#endif //_MYTEST_H_
