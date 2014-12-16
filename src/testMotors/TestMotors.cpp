// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/* 
 * Copyright (C) 2010 RobotCub Consortium, European Commission FP6 Project IST-004370
 * Author: Alessandro Scalzo
 * email: alessandro.scalzo@iit.it
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

#include "TestMotors.h"

#include <string>

TestMotors::TestMotors(yarp::os::Property& configuration) : UnitTest(configuration)
{}

TestMotors::~TestMotors()
{
    if (m_aTargetVal) delete [] m_aTargetVal;
    if (m_aMaxErr) delete [] m_aMaxErr;
    if (m_aMinErr) delete [] m_aMinErr;
    if (m_aRefVel) delete [] m_aRefVel;
    if (m_aRefAcc) delete [] m_aRefAcc;
    if (m_aTimeout) delete [] m_aTimeout;
    if (m_aHome) delete [] m_aHome;
}

bool TestMotors::init(yarp::os::Property& configuration)
{
    m_aTargetVal=NULL;
    m_aMaxErr=NULL;
    m_aMinErr=NULL;
    m_aRefVel=NULL;
    m_aRefAcc=NULL;
    m_aTimeout=NULL;
    m_aHome=NULL;
    m_initialized=false;

    iEncoders=NULL;
    iPosition=NULL;

    if (!configuration.check("portname"))
    {
        fprintf(stderr, "Missing portname parameter, cannot open device\n");
        return false;
    }
    m_portname=configuration.find("portname").asString();

    if (!configuration.check("joints"))
    {
        fprintf(stderr, "Missing joints parameter, cannot open device\n");
        return false;
    }
    m_NumJoints=configuration.find("joints").asInt();

    if (configuration.check("target"))
    {
        yarp::os::Bottle bot=configuration.findGroup("target").tail();

        int n=m_NumJoints<bot.size()?m_NumJoints:bot.size();

        m_aTargetVal=new double[m_NumJoints];
        m_aHome=new double [m_NumJoints];

        for (int i=0; i<n; ++i)
        {
            m_aTargetVal[i]=bot.get(i).asDouble();
            m_aHome[i]=0.0;
        }
    }
    else
    {
        return false;
    }

    if (configuration.check("min"))
    {
        yarp::os::Bottle bot=configuration.findGroup("min").tail();

        int n=m_NumJoints<bot.size()?m_NumJoints:bot.size();

        m_aMinErr=new double[m_NumJoints];

        for (int i=0; i<n; ++i)
           m_aMinErr[i]=bot.get(i).asDouble();
    }
    else
    {
        return false;
    }

    if (configuration.check("max"))
    {
        yarp::os::Bottle bot=configuration.findGroup("max").tail();

        int n=m_NumJoints<bot.size()?m_NumJoints:bot.size();

        m_aMaxErr=new double[m_NumJoints];

        for (int i=0; i<n; ++i)
             m_aMaxErr[i]=bot.get(i).asDouble();
    }
    else
    {
        return false;
    }

    if (configuration.check("refvel"))
    {
        yarp::os::Bottle bot=configuration.findGroup("refvel").tail();

        int n=m_NumJoints<bot.size()?m_NumJoints:bot.size();

        m_aRefVel=new double[m_NumJoints];

        for (int i=0; i<n; ++i)
            m_aRefVel[i]=bot.get(i).asDouble();
    }
    else
    {
        return false;
    }

    if (configuration.check("refacc"))
    {
        yarp::os::Bottle bot=configuration.findGroup("refacc").tail();

        int n=m_NumJoints<bot.size()?m_NumJoints:bot.size();

        m_aRefAcc=new double[m_NumJoints];

        for (int i=0; i<n; ++i)
            m_aRefAcc[i]=bot.get(i).asDouble();
    } 
    else
    {
        // nothing, accelerations are not mandatory
        // e.g. the simulator does not accept accelerations
    }

    if (configuration.check("timeout"))
    {
        yarp::os::Bottle bot=configuration.findGroup("timeout").tail();

        int n=m_NumJoints<bot.size()?m_NumJoints:bot.size();

        m_aTimeout=new double[m_NumJoints];

        for (int i=0; i<n; ++i)
            m_aTimeout[i]=bot.get(i).asDouble();
    }
    else
    {
        return false;
    }

    return true;
}

bool TestMotors::run()
{
    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("local",m_portname+"/client");
    options.put("remote",m_portname);

    bool ret=m_driver.open(options);

    Logger:: checkTrue(ret, "open device");

    if (!ret)
        return false;

    m_driver.view(iEncoders);
    m_driver.view(iPosition);

    ret=iEncoders&&iPosition;
    Logger::checkTrue(ret, "interfaces acquired");

    if (!ret)
        return false;

    int nJoints=0;
    iEncoders->getAxes(&nJoints);

    Logger::checkTrue(m_NumJoints==nJoints, "expected number of joints is consistent");

    Logger::report("Checking individual joints...\n");

    for (int joint=0; joint<m_NumJoints; ++joint)
    {
        Logger::report("Checking joint %d\n", joint);
        if (m_aRefAcc!=NULL)
            Logger::checkTrue(iPosition->setRefAcceleration(joint, m_aRefAcc[joint]), 
                "setting reference acceleration on joint %d", joint);

        Logger::checkTrue(iPosition->setRefSpeed(joint, m_aRefVel[joint]), 
            "setting reference speed on joint %d", joint);

        // wait some time
        double timeStart=yarp::os::Time::now();
        double timeNow=timeStart;
        bool read=false;

        printf("Checking encoders");
        while(timeNow<timeStart+m_aTimeout[joint] && !read)
        {
            // read encoders 
            read=iEncoders->getEncoder(joint,m_aHome+joint);
            yarp::os::Time::delay(0.1);
            printf(".");
        }
        printf("\n");
        Logger::checkTrue(read, "read encoder");

        Logger::checkTrue(iPosition->positionMove(joint, m_aTargetVal[joint]), 
            "moving joint %d to %.2lf", joint, m_aTargetVal[joint]);

        printf("Waiting timeout %.2lf", m_aTimeout[joint]);
        bool reached=false;
        while(timeNow<timeStart+m_aTimeout[joint] && !reached)
        {
            double pos;
            iEncoders->getEncoder(joint,&pos);

            if (pos>=m_aTargetVal[joint]+m_aMinErr[joint] && pos<=m_aTargetVal[joint]+m_aMaxErr[joint])
                reached=true;

            printf(".");
            timeNow=yarp::os::Time::now();
            yarp::os::Time::delay(0.1);
        }
        printf("\n");
        Logger::checkTrue(reached, "reached position");
    }

    return true;
}

bool TestMotors::release()
{
    Logger::report("Homing robot\n");

    iPosition->positionMove(m_aHome);
    double *encoders;
    bool *done;
    encoders=new double [m_NumJoints];
    done = new bool [m_NumJoints];

    bool reached=false;
    double timeStart=yarp::os::Time::now();
    double timeNow=timeStart;
    while(timeNow<timeStart+m_aTimeout[0] && !reached)
    {
        iEncoders->getEncoders(encoders);

        iPosition->checkMotionDone(done);

        reached=true;
        for(int j=0; j<m_NumJoints; j++)
        {
            reached=reached&&done[j];
        }
        
        printf(".");
        timeNow=yarp::os::Time::now();
        yarp::os::Time::delay(0.1);
    }

    printf("\n");
    delete [] encoders;
    delete [] done;

    return true;
}