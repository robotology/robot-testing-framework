// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef _MYFIXMANAGER_H_
#define _MYFIXMANAGER_H_

#include <FixtureManager.h>

class MyFixManager : public RTF::FixtureManager {
public:
    virtual bool setup(int argc, char** argv);

    virtual void tearDown();
};

#endif //_MYFIXMANAGER_H_
