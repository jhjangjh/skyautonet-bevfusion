// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_msgs:msg/Bbox.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSGS__MSG__DETAIL__BBOX__STRUCT_H_
#define CUSTOM_MSGS__MSG__DETAIL__BBOX__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Bbox in the package custom_msgs.
typedef struct custom_msgs__msg__Bbox
{
  double pos_x;
  double pos_y;
  double width;
  double length;
  double height;
  double yaw;
} custom_msgs__msg__Bbox;

// Struct for a sequence of custom_msgs__msg__Bbox.
typedef struct custom_msgs__msg__Bbox__Sequence
{
  custom_msgs__msg__Bbox * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_msgs__msg__Bbox__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_MSGS__MSG__DETAIL__BBOX__STRUCT_H_
