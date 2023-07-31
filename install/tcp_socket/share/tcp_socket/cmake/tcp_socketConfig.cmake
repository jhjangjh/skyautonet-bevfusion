# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_tcp_socket_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED tcp_socket_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(tcp_socket_FOUND FALSE)
  elseif(NOT tcp_socket_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(tcp_socket_FOUND FALSE)
  endif()
  return()
endif()
set(_tcp_socket_CONFIG_INCLUDED TRUE)

# output package information
if(NOT tcp_socket_FIND_QUIETLY)
  message(STATUS "Found tcp_socket: 0.0.0 (${tcp_socket_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'tcp_socket' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${tcp_socket_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(tcp_socket_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${tcp_socket_DIR}/${_extra}")
endforeach()
