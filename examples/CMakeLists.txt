#  Robot Testing Framework
#  Copyright: (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#

# Build examples
if (BUILD_EXAMPLES)
    get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
    get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)

    include_directories(${CMAKE_SOURCE_DIR}
                        ${RTF_TREE_INCLUDE_DIRS})
     

    add_executable(simple simple.cpp)
    target_link_libraries(simple ${RTF_LIBS})
    install(TARGETS simple
            EXPORT  simple
            RUNTIME DESTINATION bin)

    add_executable(simple_suit simple_suit.cpp)
    target_link_libraries(simple_suit ${RTF_LIBS})
    install(TARGETS simple_suit
            EXPORT  simple_suit
            RUNTIME DESTINATION bin)

    add_executable(simple_collector simple_collector.cpp)
    target_link_libraries(simple_collector ${RTF_LIBS})
    install(TARGETS simple_collector
            EXPORT  simple_collector
            RUNTIME DESTINATION bin)

    add_executable(simple_fixture simple_fixture.cpp)
    target_link_libraries(simple_fixture ${RTF_LIBS})
    install(TARGETS simple_fixture
            EXPORT  simple_fixture
            RUNTIME DESTINATION bin)
endif(BUILD_EXAMPLES)

