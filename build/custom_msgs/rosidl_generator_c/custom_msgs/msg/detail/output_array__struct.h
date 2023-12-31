// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_msgs:msg/OutputArray.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSGS__MSG__DETAIL__OUTPUT_ARRAY__STRUCT_H_
#define CUSTOM_MSGS__MSG__DETAIL__OUTPUT_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'outputs'
#include "custom_msgs/msg/detail/output__struct.h"

// Struct defined in msg/OutputArray in the package custom_msgs.
typedef struct custom_msgs__msg__OutputArray
{
  std_msgs__msg__Header header;
  custom_msgs__msg__Output__Sequence outputs;
} custom_msgs__msg__OutputArray;

// Struct for a sequence of custom_msgs__msg__OutputArray.
typedef struct custom_msgs__msg__OutputArray__Sequence
{
  custom_msgs__msg__OutputArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_msgs__msg__OutputArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_MSGS__MSG__DETAIL__OUTPUT_ARRAY__STRUCT_H_
