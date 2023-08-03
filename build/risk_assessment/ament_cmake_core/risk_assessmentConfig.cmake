# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_risk_assessment_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED risk_assessment_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(risk_assessment_FOUND FALSE)
  elseif(NOT risk_assessment_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(risk_assessment_FOUND FALSE)
  endif()
  return()
endif()
set(_risk_assessment_CONFIG_INCLUDED TRUE)

# output package information
if(NOT risk_assessment_FIND_QUIETLY)
  message(STATUS "Found risk_assessment: 0.0.0 (${risk_assessment_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'risk_assessment' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${risk_assessment_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(risk_assessment_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${risk_assessment_DIR}/${_extra}")
endforeach()
