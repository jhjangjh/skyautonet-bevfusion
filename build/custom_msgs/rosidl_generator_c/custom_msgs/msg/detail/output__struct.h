// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_msgs:msg/Output.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSGS__MSG__DETAIL__OUTPUT__STRUCT_H_
#define CUSTOM_MSGS__MSG__DETAIL__OUTPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'box'
#include "custom_msgs/msg/detail/bbox__struct.h"

// Struct defined in msg/Output in the package custom_msgs.
typedef struct custom_msgs__msg__Output
{
  int64_t id;
  double score;
  int64_t label;
  custom_msgs__msg__Bbox box;
} custom_msgs__msg__Output;

// Struct for a sequence of custom_msgs__msg__Output.
typedef struct custom_msgs__msg__Output__Sequence
{
  custom_msgs__msg__Output * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_msgs__msg__Output__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_MSGS__MSG__DETAIL__OUTPUT__STRUCT_H_
