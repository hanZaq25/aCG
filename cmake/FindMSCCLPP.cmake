#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# Tries to find MSCCLPP headers and libraries.
#
# Usage of this module as follows:
#
#  find_package(MSCCLPP)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  MSCCLPP_ROOT - When set, this path is inspected instead of standard library
#                 locations as the root of the MSCCLPP installation.
#                 The environment variable MSCCLPP_ROOT overrides this variable.
#  MSCCLPP_HOME - When set, this path is inspected instead of standard library
#                 locations as the root of the MSCCLPP installation.
#                 The environment variable MSCCLPP_HOME overrides this variable.
#
# This module defines
#  MSCCLPP_FOUND, whether MSCCLPP has been found
#  MSCCLPP_INCLUDE_DIR, directory containing header
#  MSCCLPP_LIBRARY, path to MSCCLPP library
#
# This module assumes that the user has already called find_package(CUDA)

# Default paths - adjust these to match your local installation
set(MSCCLPP_DEFAULT_PATH "$ENV{HOME}/mscclpp_double")

find_path(MSCCLPP_INCLUDE_DIR
  NAMES mscclpp/core.hpp
  HINTS 
    ${MSCCLPP_HOME}/include 
    $ENV{MSCCLPP_HOME}/include 
    ${MSCCLPP_ROOT}/include 
    $ENV{MSCCLPP_ROOT}/include
    ${MSCCLPP_DEFAULT_PATH}/include
    ${MSCCLPP_DEFAULT_PATH}/build/include
  PATHS
    /usr/local/include
    /usr/include)

if(USE_DLOPEN_MSCCLPP)
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(MSCCLPP DEFAULT_MSG MSCCLPP_INCLUDE_DIR)

  mark_as_advanced(MSCCLPP_INCLUDE_DIR)
else()
  find_library(MSCCLPP_LIBRARY
    NAMES mscclpp libmscclpp
    HINTS 
      ${MSCCLPP_HOME}/lib 
      $ENV{MSCCLPP_HOME}/lib 
      ${MSCCLPP_ROOT}/lib 
      $ENV{MSCCLPP_ROOT}/lib
      ${MSCCLPP_HOME}/build/lib
      $ENV{MSCCLPP_HOME}/build/lib
      ${MSCCLPP_ROOT}/build/lib
      $ENV{MSCCLPP_ROOT}/build/lib
      ${MSCCLPP_DEFAULT_PATH}/lib
      ${MSCCLPP_DEFAULT_PATH}/build/lib
    PATHS
      /usr/local/lib
      /usr/lib)

  if(MSCCLPP_LIBRARY)
    message(STATUS "Using MSCCLPP library: ${MSCCLPP_LIBRARY}")
  endif()

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(MSCCLPP DEFAULT_MSG
    MSCCLPP_INCLUDE_DIR MSCCLPP_LIBRARY)

  mark_as_advanced(
    MSCCLPP_INCLUDE_DIR
    MSCCLPP_LIBRARY)
endif()