// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2010-2014 RobotCub Consortium, European Commission FP6 Project IST-004370, Istituto Italiano di Tecnologia
 * Author: Alessandro Scalzo and Lorenzo Natale
 * email: alessandro.scalzo@iit.it, lorenzo.natale@iit.it
 * website: www.robotcub.org
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

/**
*
\mainpage Robot Testing

A suite of tests for generic robot platforms.

\section intro_sec Description

This is a suite of unit tests for YARP robotic platforms. A test can be made of several subtests 
(i.e. motors, encoders, inertial unit, cameras, force-torque sensors, ...).
The subtests are executed in sequential order, and the results are written to std output. The list of
test is statically populated, but a configuration file specifies which tests are actually executed. In addition
tests may receive parameters from file, this allows to execute the same unit test for different robots or robot part.

This is a sketch of the steps required to add a test:

- Create a new class deriving from UnitTest.
- Implement abstract functions UnitTest::run() (mandatory) and UnitTest::init(), UnitTest::release() (optional)
- Add test to main.cpp
- Add test and optional parameter file to the main .ini file

Please add main testing code to run(). Use init() to read parameters (return true/false on success/failure), perform 
cleanup activities within release().

Use helper functions defined in \ref Logger to report the verify the status of a test:

- report(): report general information on the result of a test
- checkTrue(): check and report result of a test

Check TestCamera for a simple example.

\section lib_sec Libraries

YARP_OS
YARP_sig
YARP_dev
YARP_math

\section parameters_sec Parameters
Provide a comprehensive list of the parameters you can pass to the module. For example:

--from <full_path_to_/mytest.ini: configuration file to use

\section conf_file_sec Configuration Files

robot-testing needs a main configuration and one configuration file for each subtest.

The main configuration file consists of the following sections:

The file consists in a few sections:
\code
[REFERENCES]
user "Alice Cooper"
comment "Testing left and right arms."

[TESTS]
TestCamera right_camera.ini
TestCamera left_camera.ini
TestMotors test_right_arm.ini
TestMotors test_left_arm.ini
\endcode

- \e user who executes the test
- \e comment textual comment

- \e TestCamera test type should match identifier used within main.cpp
- \e right_camera.ini test configuration file

Optionally you can specify an [ENVIRONMENT] section which includes variables that
can be expanded when reading each test individual ini files. A typical example is the 
name of the robot which is used to form port names of tests.

Example if in the main configuration file you specify this environment:

\code
[ENVIRONMENT]
robotname icubGazeboSim
\endcode

Then inside right_camera.ini:

\code
portname /${robotname}/cam/right
\endcode

will be expanded to /icubGazeboSim/cam/right

\section example_sec Example Instantiation of the Module

Make sure the simulator is running.

robot-testing --from <full_path_to>/app/iCubTest/test.ini

\author Alessandro Scalzo and Lorenzo Natale

Copyright (C) 2014 RobotCub Consortium and Istituto Italiano di Tecnologia

CopyPolicy: Released under the terms of the GNU GPL v2.0.

This file can be edited at src/main.cpp.
**/


#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Value.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Network.h>

#include "TestSet.h"
#include "testCamera/TestCamera.h"
#include "testMotors/TestMotors.h"
#include "testFTSensors/TestFTSensors.h"

#include <yarp/dev/Drivers.h>

YARP_DECLARE_DEVICES(icubmod)

int main(int argc,char* argv[])
{
    YARP_REGISTER_DEVICES(icubmod)
    yarp::os::Network yarp;
    yarp.setVerbosity(-1);

    if (!yarp.checkNetwork())
    {
        fprintf(stderr, "Sorry YARP network does not seem to be available, is the yarp server available?\n");
        return -1;
    }

    yarp::os::ResourceFinder rf;
    rf.setVerbose();
    rf.setDefaultContext("RobotTesting");
    rf.setDefaultConfigFile("test.ini");
    rf.configure(argc,argv);

    yarp::os::Bottle references=rf.findGroup("REFERENCES");
    yarp::os::Bottle environment=rf.findGroup("ENVIRONMENT");
    
    TestSet ts;
    ts.init(references);
  
    // add tests to the test set
    yarp::os::Bottle testSet=rf.findGroup("TESTS").tail();
    
    for (int t=0; t<testSet.size(); ++t)
    {       
        yarp::os::Bottle test(testSet.get(t).toString());
        std::string testType(test.get(0).asString());
        std::string fileName(test.get(1).asString());

        std::string file=rf.findFileByName(fileName);
        
        yarp::os::Property config;

        // open test ini file, pass environment with variables inherited from the
        // main ini file.
        config.fromConfigFile(file, environment);

        if (testType=="TestMotors")
        {
            ts.addTest(new TestMotors(config));
        }
        else if (testType=="iCubTestMotorsStiction")
        {
//            ts.addTest(new iCubTestMotorsStiction(testRf));
        }
        else if (testType=="iCubTestMotorsStictionIncremental")
        {
//            ts.addTest(new iCubTestMotorsStictionIncremental(testRf));
        }
        else if (testType=="iCubTestRoie")
        {
//            ts.addTest(new iCubTestRoie(testRf));
        }
        else if (testType=="TestCamera")
        {
            ts.addTest(new TestCamera(config));
            //fprintf(stderr,"iCubTestCamera not yet implemented\n");
        }
        else if (testType == "TestFTSensors")
        {
            ts.addTest(new TestFTSensors(config));
        }
        else if (testType=="iCubTestInertial")
        {
            //ts.AddTest(new iCubTestInertial(testRf));
            fprintf(stderr,"iCubTestInertial not yet implemented\n");
        }
        else if (testType=="iCubTestForceTorque")
        {
            //ts.AddTest(new iCubTestForceTorque(testRf));
            fprintf(stderr,"iCubTestForceTorque not yet implemented\n");
        }
    }
    
    // execute tests
    int numFailures=ts.run();
    
    // save test reports in XML format
    ts.printReport();

    ts.cleanup();
    // return number of failed tests
    return numFailures;
}
