// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2014 iCub Facility, Istituto Italiano di Tecnologia
 * Author: Lorenzo Natale
 * email: lorenzo.natale@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include <cstdlib>

#include "TestCamera.h"

#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Image.h>
#include <yarp/os/Network.h>

using namespace yarp::os;
using namespace yarp::sig;

// these values can be parameters if needed but better to keep it simple
const int TIME=1;
const int FREQUENCY=30;
const int FRAMES_TOLERANCE=5;

using namespace Logger;

TestCamera::TestCamera(yarp::os::Property& configuration) : UnitTest(configuration)
{

}

TestCamera::~TestCamera()
{

}

bool TestCamera::init(yarp::os::Property &configuration)
{
    if (!configuration.check("portname"))
        return false;

    portname=configuration.find("portname").asString();

    return true;
}


bool TestCamera::run()
{
    BufferedPort<Image> port;
    if (!port.open("/iCubTest/camera"))
    {
        checkTrue(false, "opening port, is YARP network working?");
        return true;
    }

    Logger::report("connecting from %s to %s\n", port.getName().c_str(), portname.c_str());
    if (!Network::connect(portname, port.getName()))
    {
        checkTrue(false, "could not connect to remote port, camera unavailable");
        return true;
    }

    printf("Reading images...");

    double timeStart=yarp::os::Time::now();
    double timeNow=timeStart;

    int frames=0;
    while(timeNow<timeStart+TIME)
        {
           Image *image=port.read(false);

           if (image!=0)
               frames++;

           yarp::os::Time::delay(0.01);
           timeNow=yarp::os::Time::now();
           printf(".");
        }

    printf("\n");
    int expectedFrames=TIME*FREQUENCY;
    Logger::report("Received %d frames, expecting %d\n", frames, expectedFrames);

    checkTrue((abs(frames-expectedFrames)<FRAMES_TOLERANCE), "checking number of received frames");

    return true;
}
