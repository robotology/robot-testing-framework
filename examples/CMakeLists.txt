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


    add_executable(rtf_simple simple.cpp)
    target_link_libraries(rtf_simple RTF)
    install(TARGETS rtf_simple
            EXPORT  rtf_simple
            RUNTIME DESTINATION bin)

    add_executable(rtf_simple_suite simple_suite.cpp)
    target_link_libraries(rtf_simple_suite RTF)
    install(TARGETS rtf_simple_suite
            EXPORT  rtf_simple_suite
            RUNTIME DESTINATION bin)

    add_executable(rtf_simple_collector simple_collector.cpp)
    target_link_libraries(rtf_simple_collector RTF)
    install(TARGETS rtf_simple_collector
            EXPORT  rtf_simple_collector
            RUNTIME DESTINATION bin)

    add_executable(rtf_simple_runner simple_runner.cpp)
    target_link_libraries(rtf_simple_runner RTF)
    install(TARGETS rtf_simple_runner
            EXPORT  rtf_simple_runner
            RUNTIME DESTINATION bin)

    add_executable(rtf_simple_fixture simple_fixture.cpp)
    target_link_libraries(rtf_simple_fixture RTF)
    install(TARGETS rtf_simple_fixture
            EXPORT  rtf_simple_fixture
            RUNTIME DESTINATION bin)

    if(ENABLE_WEB_LISTENER)
        add_executable(rtf_simple_web simple_web.cpp)
        target_link_libraries(rtf_simple_web RTF)
        install(TARGETS rtf_simple_web
                EXPORT  rtf_simple_web
                RUNTIME DESTINATION bin)
    endif()

    # Examples are also used for regression testing
#    macro(add_example_as_failing_test examplename)
#        add_test(NAME Test::${examplename} COMMAND ${examplename})
        # rtf examples are designed to explicitly fail (except for fixture test)
#        set_tests_properties(Test::${examplename} PROPERTIES WILL_FAIL true)
#    endmacro()

#    macro(add_example_as_successful_test examplename)
#        add_test(NAME Test::${examplename} COMMAND ${examplename})
#    endmacro()

#    add_example_as_failing_test(rtf_simple)
#    add_example_as_failing_test(rtf_simple_suite)
#    add_example_as_failing_test(rtf_simple_collector)
#    add_example_as_failing_test(rtf_simple_runner)
#    add_example_as_successful_test(rtf_simple_fixture)
#    if(ENABLE_WEB_LISTENER)
#        add_example_as_failing_test(rtf_simple_web)
#    endif()

endif(BUILD_EXAMPLES)

