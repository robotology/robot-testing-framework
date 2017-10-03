#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

set_property(GLOBAL APPEND PROPERTY RTF_TREE_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
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
        include/rtf/TestSuite.h
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
        src/TestSuite.cpp
        src/TextOutputter.cpp
        src/WebProgressListener.cpp)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/impl
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
        include/rtf/TestSuite.h
        include/rtf/TextOutputter.h)

    set(RTF_HDRS_IMPL)

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
        src/TestSuite.cpp
        src/TextOutputter.cpp)

    include_directories(${RTF_TREE_INCLUDE_DIRS}
                        ${RTF_INTERNAL_INCLUDE_DIRS})
endif()

if(WIN32)
    add_library(${PROJECT_NAME} STATIC ${RTF_SRCS} ${RTF_HDRS} ${RTF_HDRS_IMPL})
else()
    add_library(${PROJECT_NAME} SHARED ${RTF_SRCS} ${RTF_HDRS} ${RTF_HDRS_IMPL})
endif()

if(ENABLE_WEB_LISTENER)
    target_link_libraries(${PROJECT_NAME} RTF_mongoose)
else()
    target_link_libraries(${PROJECT_NAME})
endif()

target_compile_features(${PROJECT_NAME} PUBLIC cxx_nullptr)


# choose which header files should be installed
set_property(TARGET ${PROJECT_NAME} PROPERTY PUBLIC_HEADER ${RTF_HDRS})

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include/rtf)

set_property(GLOBAL APPEND PROPERTY RTF_LIBS ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRS ${RTF_TREE_INCLUDE_DIRS})
