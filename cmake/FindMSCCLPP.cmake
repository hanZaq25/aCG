# FindMSCCLPP.cmake
#
# Variables used by this module:
#
#  MSCCLPP_ROOT - When set, this path is inspected instead of standard library
#                 locations as the root of the MSCCLPP installation.
#                 The environment variable MSCCLPP_ROOT overrides this variable.
#  MSCCLPP_HOME - When set, this path is inspected instead of standard library
#                 locations as the root of the MSCCLPP installation.
#                 The environment variable MSCCLPP_HOME overrides this variable.
#
# This module defines:
#  MSCCLPP_FOUND, whether mscclpp has been found
#  MSCCLPP_INCLUDE_DIR, directory containing headers
#  MSCCLPP_LIBRARY, path to mscclpp library

find_path(MSCCLPP_INCLUDE_DIR
  NAMES mscclpp/core.hpp
  HINTS
    ${MSCCLPP_HOME}/include
    $ENV{MSCCLPP_HOME}/include
    ${MSCCLPP_ROOT}/include
    $ENV{MSCCLPP_ROOT}/include
)

find_library(MSCCLPP_LIBRARY
  NAMES mscclpp
  HINTS
    ${MSCCLPP_HOME}/lib
    $ENV{MSCCLPP_HOME}/lib
    ${MSCCLPP_ROOT}/lib
    $ENV{MSCCLPP_ROOT}/lib
)

message(STATUS "Using mscclpp library: ${MSCCLPP_LIBRARY}")
message(STATUS "Using mscclpp include: ${MSCCLPP_INCLUDE_DIR}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MSCCLPP DEFAULT_MSG
  MSCCLPP_INCLUDE_DIR MSCCLPP_LIBRARY)

mark_as_advanced(
  MSCCLPP_INCLUDE_DIR
  MSCCLPP_LIBRARY)