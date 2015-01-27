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

#include "TestFTSensors.h"

#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Vector.h>
#include <yarp/os/Network.h>

using namespace yarp::os;
using namespace yarp::sig;

using namespace Logger;

TestFTSensors::TestFTSensors(yarp::os::Property& configuration) : UnitTest(configuration)
{

}

TestFTSensors::~TestFTSensors()
{

}

bool TestFTSensors::init(yarp::os::Property &configuration)
{
    if (!configuration.check("portname"))
        return false;

    portname=configuration.find("portname").asString();

    return true;
}


bool TestFTSensors::run()
{
    BufferedPort<Vector> port;
    if (!port.open("/iCubTest/FTsensor"))
    {
        checkTrue(false, "opening port, is YARP network working?");
        return true;
    }

    Logger::report("connecting from %s to %s\n", port.getName().c_str(), portname.c_str());
    if (!Network::connect(portname, port.getName()))
    {
        checkTrue(false, "could not connect to remote port, FT sensor unavailable");
        return true;
    }

    printf("Reading FT sensors...");
    Vector *readSensor = port.read();
    if (!readSensor)
    {
        checkTrue(false, "could not read FT data from sensor");
        return true;
    }
    
    checkTrue(readSensor->size() == 6, "sensor has 6 values");

    Network::disconnect(portname, port.getName());
    port.close();
    return true;
}
