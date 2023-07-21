// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_msgs:msg/OutputArray.idl
// generated code does not contain a copyright notice
#include "custom_msgs/msg/detail/output_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `outputs`
#include "custom_msgs/msg/detail/output__functions.h"

bool
custom_msgs__msg__OutputArray__init(custom_msgs__msg__OutputArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    custom_msgs__msg__OutputArray__fini(msg);
    return false;
  }
  // outputs
  if (!custom_msgs__msg__Output__Sequence__init(&msg->outputs, 0)) {
    custom_msgs__msg__OutputArray__fini(msg);
    return false;
  }
  return true;
}

void
custom_msgs__msg__OutputArray__fini(custom_msgs__msg__OutputArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // outputs
  custom_msgs__msg__Output__Sequence__fini(&msg->outputs);
}

bool
custom_msgs__msg__OutputArray__are_equal(const custom_msgs__msg__OutputArray * lhs, const custom_msgs__msg__OutputArray * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // outputs
  if (!custom_msgs__msg__Output__Sequence__are_equal(
      &(lhs->outputs), &(rhs->outputs)))
  {
    return false;
  }
  return true;
}

bool
custom_msgs__msg__OutputArray__copy(
  const custom_msgs__msg__OutputArray * input,
  custom_msgs__msg__OutputArray * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // outputs
  if (!custom_msgs__msg__Output__Sequence__copy(
      &(input->outputs), &(output->outputs)))
  {
    return false;
  }
  return true;
}

custom_msgs__msg__OutputArray *
custom_msgs__msg__OutputArray__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_msgs__msg__OutputArray * msg = (custom_msgs__msg__OutputArray *)allocator.allocate(sizeof(custom_msgs__msg__OutputArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_msgs__msg__OutputArray));
  bool success = custom_msgs__msg__OutputArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_msgs__msg__OutputArray__destroy(custom_msgs__msg__OutputArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_msgs__msg__OutputArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_msgs__msg__OutputArray__Sequence__init(custom_msgs__msg__OutputArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_msgs__msg__OutputArray * data = NULL;

  if (size) {
    data = (custom_msgs__msg__OutputArray *)allocator.zero_allocate(size, sizeof(custom_msgs__msg__OutputArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_msgs__msg__OutputArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_msgs__msg__OutputArray__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_msgs__msg__OutputArray__Sequence__fini(custom_msgs__msg__OutputArray__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_msgs__msg__OutputArray__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_msgs__msg__OutputArray__Sequence *
custom_msgs__msg__OutputArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_msgs__msg__OutputArray__Sequence * array = (custom_msgs__msg__OutputArray__Sequence *)allocator.allocate(sizeof(custom_msgs__msg__OutputArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_msgs__msg__OutputArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_msgs__msg__OutputArray__Sequence__destroy(custom_msgs__msg__OutputArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_msgs__msg__OutputArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_msgs__msg__OutputArray__Sequence__are_equal(const custom_msgs__msg__OutputArray__Sequence * lhs, const custom_msgs__msg__OutputArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_msgs__msg__OutputArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_msgs__msg__OutputArray__Sequence__copy(
  const custom_msgs__msg__OutputArray__Sequence * input,
  custom_msgs__msg__OutputArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_msgs__msg__OutputArray);
    custom_msgs__msg__OutputArray * data =
      (custom_msgs__msg__OutputArray *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_msgs__msg__OutputArray__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          custom_msgs__msg__OutputArray__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_msgs__msg__OutputArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
