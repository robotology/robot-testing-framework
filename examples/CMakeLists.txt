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

    add_executable(simple_suit simple_suit.cpp)
    target_link_libraries(simple_suit ${RTF_LIBS})

    add_executable(simple_collector simple_collector.cpp)
    target_link_libraries(simple_collector ${RTF_LIBS})

    add_executable(simple_fixture simple_fixture.cpp)
    target_link_libraries(simple_fixture ${RTF_LIBS})

    if(ENABLE_PLUGIN)
        add_subdirectory(plugin)
    endif(ENABLE_PLUGIN)

endif(BUILD_EXAMPLES)

