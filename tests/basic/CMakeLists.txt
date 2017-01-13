#  RTF
#  Copyright: (C) 2015 Ali Paikan
#  Authors: Ali Paikan <ali.paikan@gmail.com>
#
#  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
#



#find_package(RTF)
#find_package(RTF COMPONENTS DLL)

get_property(RTF_TREE_INCLUDE_DIRS GLOBAL PROPERTY RTF_TREE_INCLUDE_DIRS)
get_property(RTF_LIBS GLOBAL PROPERTY RTF_LIBS)

include_directories(${CMAKE_SOURCE_DIR}
                    ${RTF_TREE_INCLUDE_DIRS})

# SingleTestCase
add_library(SingleTestCase MODULE SingleTestCase.cpp)
target_link_libraries(SingleTestCase ${RTF_LIBRARIES})


# SingleTestCase
add_library(MultiTestCases MODULE MultiTestCases.cpp)
target_link_libraries(MultiTestCases ${RTF_LIBRARIES})


# SingleTestSuite
add_library(SingleTestSuite MODULE SingleTestSuite.cpp)
target_link_libraries(SingleTestSuite ${RTF_LIBRARIES})

# SingleTestSuite
add_library(FixtureManager MODULE FixtureManager.cpp)
target_link_libraries(FixtureManager ${RTF_LIBRARIES})
