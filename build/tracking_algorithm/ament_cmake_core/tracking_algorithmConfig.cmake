# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_tracking_algorithm_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED tracking_algorithm_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(tracking_algorithm_FOUND FALSE)
  elseif(NOT tracking_algorithm_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(tracking_algorithm_FOUND FALSE)
  endif()
  return()
endif()
set(_tracking_algorithm_CONFIG_INCLUDED TRUE)

# output package information
if(NOT tracking_algorithm_FIND_QUIETLY)
  message(STATUS "Found tracking_algorithm: 0.0.0 (${tracking_algorithm_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'tracking_algorithm' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${tracking_algorithm_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(tracking_algorithm_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${tracking_algorithm_DIR}/${_extra}")
endforeach()
