// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_msgs:msg/OutputArray.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSGS__MSG__DETAIL__OUTPUT_ARRAY__BUILDER_HPP_
#define CUSTOM_MSGS__MSG__DETAIL__OUTPUT_ARRAY__BUILDER_HPP_

#include "custom_msgs/msg/detail/output_array__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_msgs
{

namespace msg
{

namespace builder
{

class Init_OutputArray_outputs
{
public:
  explicit Init_OutputArray_outputs(::custom_msgs::msg::OutputArray & msg)
  : msg_(msg)
  {}
  ::custom_msgs::msg::OutputArray outputs(::custom_msgs::msg::OutputArray::_outputs_type arg)
  {
    msg_.outputs = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_msgs::msg::OutputArray msg_;
};

class Init_OutputArray_header
{
public:
  Init_OutputArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_OutputArray_outputs header(::custom_msgs::msg::OutputArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_OutputArray_outputs(msg_);
  }

private:
  ::custom_msgs::msg::OutputArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_msgs::msg::OutputArray>()
{
  return custom_msgs::msg::builder::Init_OutputArray_header();
}

}  // namespace custom_msgs

#endif  // CUSTOM_MSGS__MSG__DETAIL__OUTPUT_ARRAY__BUILDER_HPP_
