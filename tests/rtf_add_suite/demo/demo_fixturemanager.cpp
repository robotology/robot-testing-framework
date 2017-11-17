/*
 * Copyright: (C) 2017 Istituto Italiano di Tecnologia (IIT)
 * Authors: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
 * Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <rtf/FixtureManager.h>
#include <rtf/dll/Plugin.h>

class DemoFixtureManager : public RTF::FixtureManager
{
public:
    DemoFixtureManager() {};
    virtual ~DemoFixtureManager() {};

    virtual bool setup(int argc, char** argv) override {
        return true;
    }

    virtual bool check() override { return true; }

    virtual void tearDown() override {
    }
};

PREPARE_FIXTURE_PLUGIN(DemoFixtureManager)
