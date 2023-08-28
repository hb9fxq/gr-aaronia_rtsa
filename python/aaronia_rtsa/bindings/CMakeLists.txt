# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT aaronia_rtsa_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT aaronia_rtsa_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND aaronia_rtsa_python_files
    rtsa_http_server_source_python.cc
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(aaronia_rtsa
   ../../..
   gr::aaronia_rtsa
   "${aaronia_rtsa_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET aaronia_rtsa_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:aaronia_rtsa_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/aaronia_rtsa/
)

install(TARGETS aaronia_rtsa_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/aaronia_rtsa COMPONENT pythonapi)
