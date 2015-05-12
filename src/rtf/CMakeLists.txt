#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

project(RTF)

set_property(GLOBAL APPEND PROPERTY RTF_TREE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")
get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
get_property(RTF_INTERNAL_INCLUDE_DIRS GLOBAL PROPERTY RTF_INTERNAL_INCLUDE_DIRS)
get_property(RTF_INTERNAL_LIBS GLOBAL PROPERTY RTF_INTERNAL_LIBS)
get_property(RTF_INTERNAL_DEFS GLOBAL PROPERTY RTF_INTERNAL_DEFS)

# Create the library
if(ENABLE_WEB_LISTENER)
    set(RTF_HDRS
        include/rtf/Arguments.h
        include/rtf/Asserter.h
        include/rtf/ConsoleListener.h
        include/rtf/Exception.h
        include/rtf/FixtureManager.h
        include/rtf/PluginLoader.h
        include/rtf/ResultEvent.h
        include/rtf/rtf_config.h
        include/rtf/TestAssert.h
        include/rtf/TestCase.h
        include/rtf/Test.h
        include/rtf/TestListener.h
        include/rtf/TestMessage.h
        include/rtf/TestResultCollector.h
        include/rtf/TestResult.h
        include/rtf/TestRunner.h
        include/rtf/TestSuit.h
        include/rtf/TextOutputter.h
        include/rtf/WebProgressListener.h)

     set(RTF_HDRS_IMPL
        include/rtf/impl/WebProgressListener_impl.h)

     set(RTF_SRCS
        src/Arguments.cpp
        src/Asserter.cpp
        src/ConsoleListener.cpp
        src/FixtureManager.cpp
        src/TestCase.cpp
        src/TestMessage.cpp
        src/TestResultCollector.cpp
        src/TestResult.cpp
        src/TestRunner.cpp
        src/TestSuit.cpp
        src/TextOutputter.cpp
        src/WebProgressListener.cpp)

     include_directories(${PROJECT_SOURCE_DIR}/include/impl
                        ${RTF_TREE_INCLUDE_DIRS}
                        ${RTF_INTERNAL_INCLUDE_DIRS})
else()
    set(RTF_HDRS
        include/rtf/Arguments.h
        include/rtf/Asserter.h
        include/rtf/ConsoleListener.h
        include/rtf/Exception.h
        include/rtf/FixtureManager.h
        include/rtf/PluginLoader.h
        include/rtf/ResultEvent.h
        include/rtf/rtf_config.h
        include/rtf/TestAssert.h
        include/rtf/TestCase.h
        include/rtf/Test.h
        include/rtf/TestListener.h
        include/rtf/TestMessage.h
        include/rtf/TestResultCollector.h
        include/rtf/TestResult.h
        include/rtf/TestRunner.h
        include/rtf/TestSuit.h
        include/rtf/TextOutputter.h)

     set(RTF_HDRS_IMPL )

     set(RTF_SRCS
        src/Arguments.cpp
        src/Asserter.cpp
        src/ConsoleListener.cpp
        src/FixtureManager.cpp
        src/TestCase.cpp
        src/TestMessage.cpp
        src/TestResultCollector.cpp
        src/TestResult.cpp
        src/TestRunner.cpp
        src/TestSuit.cpp
        src/TextOutputter.cpp)

     include_directories(${RTF_TREE_INCLUDE_DIRS}
                        ${RTF_INTERNAL_INCLUDE_DIRS})
endif()


if(WIN32)
    add_library(RTF STATIC ${RTF_SRCS} ${RTF_HDRS} ${RTF_HDRS_IMPL})
else()
    add_library(RTF SHARED ${RTF_SRCS} ${RTF_HDRS} ${RTF_HDRS_IMPL})
endif()

if(ENABLE_WEB_LISTENER)
    target_link_libraries(RTF RTF_mongoose)
else()
    target_link_libraries(RTF)
endif()

# choose which header files should be installed
set_property(TARGET RTF PROPERTY PUBLIC_HEADER ${RTF_HDRS})

install(TARGETS RTF
        EXPORT RTF
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/rtf)

set_property(GLOBAL APPEND PROPERTY RTF_LIBS RTF)
set_property(TARGET RTF PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})

