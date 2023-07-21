// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_msgs:msg/Bbox.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_MSGS__MSG__DETAIL__BBOX__BUILDER_HPP_
#define CUSTOM_MSGS__MSG__DETAIL__BBOX__BUILDER_HPP_

#include "custom_msgs/msg/detail/bbox__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_msgs
{

namespace msg
{

namespace builder
{

class Init_Bbox_yaw
{
public:
  explicit Init_Bbox_yaw(::custom_msgs::msg::Bbox & msg)
  : msg_(msg)
  {}
  ::custom_msgs::msg::Bbox yaw(::custom_msgs::msg::Bbox::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_msgs::msg::Bbox msg_;
};

class Init_Bbox_height
{
public:
  explicit Init_Bbox_height(::custom_msgs::msg::Bbox & msg)
  : msg_(msg)
  {}
  Init_Bbox_yaw height(::custom_msgs::msg::Bbox::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_Bbox_yaw(msg_);
  }

private:
  ::custom_msgs::msg::Bbox msg_;
};

class Init_Bbox_length
{
public:
  explicit Init_Bbox_length(::custom_msgs::msg::Bbox & msg)
  : msg_(msg)
  {}
  Init_Bbox_height length(::custom_msgs::msg::Bbox::_length_type arg)
  {
    msg_.length = std::move(arg);
    return Init_Bbox_height(msg_);
  }

private:
  ::custom_msgs::msg::Bbox msg_;
};

class Init_Bbox_width
{
public:
  explicit Init_Bbox_width(::custom_msgs::msg::Bbox & msg)
  : msg_(msg)
  {}
  Init_Bbox_length width(::custom_msgs::msg::Bbox::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_Bbox_length(msg_);
  }

private:
  ::custom_msgs::msg::Bbox msg_;
};

class Init_Bbox_pos_y
{
public:
  explicit Init_Bbox_pos_y(::custom_msgs::msg::Bbox & msg)
  : msg_(msg)
  {}
  Init_Bbox_width pos_y(::custom_msgs::msg::Bbox::_pos_y_type arg)
  {
    msg_.pos_y = std::move(arg);
    return Init_Bbox_width(msg_);
  }

private:
  ::custom_msgs::msg::Bbox msg_;
};

class Init_Bbox_pos_x
{
public:
  Init_Bbox_pos_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Bbox_pos_y pos_x(::custom_msgs::msg::Bbox::_pos_x_type arg)
  {
    msg_.pos_x = std::move(arg);
    return Init_Bbox_pos_y(msg_);
  }

private:
  ::custom_msgs::msg::Bbox msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_msgs::msg::Bbox>()
{
  return custom_msgs::msg::builder::Init_Bbox_pos_x();
}

}  // namespace custom_msgs

#endif  // CUSTOM_MSGS__MSG__DETAIL__BBOX__BUILDER_HPP_
