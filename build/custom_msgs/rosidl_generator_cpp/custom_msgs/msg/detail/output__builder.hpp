// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_msgs:msg/Output.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSGS__MSG__DETAIL__OUTPUT__BUILDER_HPP_
#define CUSTOM_MSGS__MSG__DETAIL__OUTPUT__BUILDER_HPP_

#include "custom_msgs/msg/detail/output__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_msgs
{

namespace msg
{

namespace builder
{

class Init_Output_label
{
public:
  explicit Init_Output_label(::custom_msgs::msg::Output & msg)
  : msg_(msg)
  {}
  ::custom_msgs::msg::Output label(::custom_msgs::msg::Output::_label_type arg)
  {
    msg_.label = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_msgs::msg::Output msg_;
};

class Init_Output_score
{
public:
  explicit Init_Output_score(::custom_msgs::msg::Output & msg)
  : msg_(msg)
  {}
  Init_Output_label score(::custom_msgs::msg::Output::_score_type arg)
  {
    msg_.score = std::move(arg);
    return Init_Output_label(msg_);
  }

private:
  ::custom_msgs::msg::Output msg_;
};

class Init_Output_box
{
public:
  Init_Output_box()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Output_score box(::custom_msgs::msg::Output::_box_type arg)
  {
    msg_.box = std::move(arg);
    return Init_Output_score(msg_);
  }

private:
  ::custom_msgs::msg::Output msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_msgs::msg::Output>()
{
  return custom_msgs::msg::builder::Init_Output_box();
}

}  // namespace custom_msgs

#endif  // CUSTOM_MSGS__MSG__DETAIL__OUTPUT__BUILDER_HPP_
