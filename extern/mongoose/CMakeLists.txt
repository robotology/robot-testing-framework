# Copyright (C) 2012  iCub Facility, Istituto Italiano di Tecnologia
# Author: Ali Paikan <ali.paikan@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT


# Mongoose
set(PROJECTNAME RTF_mongoose)
project(${PROJECTNAME})

set(mongoose_SRCS
    src/mongoose.c
)

set(mongoose_HDRS
    src/mongoose.h
)

add_definitions("-DMONGOOSE_ENABLE_THREADS")
if(WIN32)
    add_library(${PROJECTNAME} STATIC ${mongoose_SRCS})
else()
    add_library(${PROJECTNAME} STATIC ${mongoose_SRCS})
    target_link_libraries(${PROJECTNAME} pthread)
endif()
set_target_properties(${PROJECTNAME} PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_LIBS ${PROJECTNAME})
set_property(GLOBAL APPEND PROPERTY RTF_INTERNAL_DEFS "-DMONGOOSE_ENABLE_THREADS")

install(TARGETS ${PROJECTNAME}
        EXPORT RTF
        COMPONENT runtime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
set_property(GLOBAL APPEND PROPERTY RTF_LIBS ${PROJECTNAME})
