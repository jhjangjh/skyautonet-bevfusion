#ifndef SORT_ROS_H
#define SORT_ROS_H

#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "custom_msgs/msg/output_array.hpp"
#include <memory>

#include "Sort.h"

using namespace visualization_msgs::msg;

class SortRos : public rclcpp::Node {
public:
  SortRos();

  void setup(void);

private:
  void rectArrayCallback(const custom_msgs::msg::OutputArray::SharedPtr markerArray);
  
  rclcpp::Publisher<MarkerArray>::SharedPtr pub;

  rclcpp::Subscription<custom_msgs::msg::OutputArray>::SharedPtr sub;

  Sort* sorter;

  // int param_maxAge;
  // int param_minHits;
  // double param_iouThreshold;
  
  
};

#endif