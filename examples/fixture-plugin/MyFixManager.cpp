// -*- mode:C++ { } tab-width:4 { } c-basic-offset:4 { } indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2015 iCub Facility
 * Authors: Ali Paikan
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <stdio.h>
#include <rtf/dll/Plugin.h>
#include "MyFixManager.h"

using namespace RTF;

PREPARE_FIXTURE_PLUGIN(MyFixManager)

bool MyFixManager::setup(int argc, char** argv) {
    printf("Called from fixture plugin: setupping fixture...\n");
    // do the setup here
    // ...
    return true;
}

void MyFixManager::tearDown() {
    printf("Called from fixture plugin: tearing down the fixture...\n");
    // do the tear down here
    // ...
}
