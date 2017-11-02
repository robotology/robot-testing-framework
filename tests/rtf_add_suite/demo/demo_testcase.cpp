/*
 * Copyright (C) 2017 Istituto Italiano di Tecnologia (IIT)
 * Authors: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <rtf/TestCase.h>
#include <rtf/TestAssert.h>
#include <rtf/dll/Plugin.h>

class DemoTestCase : public RTF::TestCase
{
public:
    DemoTestCase() : TestCase("DemoTestCase") { }

    virtual void run() override {
        RTF_TEST_CHECK(2<3, "two is less than three");
    }
};

PREPARE_PLUGIN(DemoTestCase)
