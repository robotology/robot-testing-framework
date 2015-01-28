# Copyright: 2014 iCub Facility, Istituto Italiano di Tecnologia
# Author: Lorenzo Natale
# CopyPolicy: Released under the terms of the GNU GPL v2.0.
#

cmake_minimum_required(VERSION 2.8.7)

set(PROJECTNAME robot-testing)
project(${PROJECTNAME})

find_package(YARP)

add_subdirectory(src)
