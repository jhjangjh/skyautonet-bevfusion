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
  
  rclcpp::Publisher<MarkerArray>::SharedPtr viz_pub;

  rclcpp::Publisher<custom_msgs::msg::OutputArray>::SharedPtr output_pub;

  rclcpp::Subscription<custom_msgs::msg::OutputArray>::SharedPtr sub;

  Sort* sorter;

  std::vector<SortRect> pre_output;
  rclcpp::Time pre_timestamp;
  rclcpp::Time now_timestamp;


  void getVelocity(SortRect rect);

  float vel_x;
  float vel_y;

  // double param_maxAge;
  // double param_minHits;
  // double param_iouThreshold;
  
};

#endif