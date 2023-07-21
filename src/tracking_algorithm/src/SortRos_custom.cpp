#include "SortRos_custom.h"

SortRos::SortRos() : Node("sort_ros_custom") {
  this->declare_parameter("param_maxAge", 1);
  this->declare_parameter("param_minHits", 2);
  this->declare_parameter("param_iouThreshold", 0.9);
}

void SortRos::setup() {
  // double maxAge = 2;
  // double minHits = 3;
  // double iouThreshold = 0.3;

  // sorter = new Sort(maxAge, minHits, iouThreshold);
  sorter = new Sort(param_maxAge, param_minHits, param_iouThreshold);

  pub = this->create_publisher<MarkerArray>("/markers_tracked",
                                            rclcpp::QoS(rclcpp::KeepLast(10)));
  sub = this->create_subscription<custom_msgs::msg::OutputArray>(
      "/model_output", rclcpp::QoS(rclcpp::KeepLast(10)),
      std::bind(&SortRos::rectArrayCallback, this, std::placeholders::_1));
}

void SortRos::rectArrayCallback(const custom_msgs::msg::OutputArray::SharedPtr outputArray) {

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();




  param_maxAge = this->get_parameter("param_maxAge").as_int();
  param_minHits = this->get_parameter("param_minHits").as_int();
  param_iouThreshold = this->get_parameter("param_iouThreshold").as_double();
  // std:: cout << "param_maxAge : " << param_maxAge << std::endl;
  // std:: cout << "param_minHits : " << param_minHits << std::endl;
  // std:: cout << "param_iouThreshold : " << param_iouThreshold << std::endl;
  std::string frame_id = "map";
  std::vector<SortRect> rects;

  // builtin_interfaces::msg::Time timestamp = outputArray->stamp;
  // std:: cout << "timestamp sec : " << timestamp.sec << std::endl;
  // std:: cout << "timestamp nanosec : " << timestamp.nanosec << std::endl;

  
  for (auto output : outputArray->outputs) {

    
    // std:: cout << "--------------------------" << std::endl;
    SortRect rect;
    rect.id = 0;
    rect.centerX = output.box.pos_x;
    rect.centerY = output.box.pos_y;
    rect.width = output.box.width;
    rect.length = output.box.length;
    rect.height = output.box.height;
    rect.yaw = output.box.yaw;
    

    // std:: cout << "pose_x : " << rect.centerX << std::endl;
    // std:: cout << "pose_y : " << rect.centerY << std::endl;
    // std:: cout << "width : " << rect.width << std::endl;
    // std:: cout << "length : " << rect.length << std::endl;
    // std:: cout << "height : " << rect.height << std::endl;
    // std:: cout << "yaw : " << rect.yaw << std::endl;

    rects.push_back(rect);
  }

  std::vector<SortRect> output = sorter->update(rects);
  
  MarkerArray markerArrayOutput;

  Marker delete_marker;
  delete_marker.action = Marker::DELETEALL; 
  markerArrayOutput.markers.push_back(delete_marker);

  for (auto rect : output) {
    
    std:: cout << "Object ID : " << rect.id << std::endl;
    std:: cout << "pose_x : " << rect.centerX << std::endl;
    std:: cout << "pose_y : " << rect.centerY << std::endl;
    std:: cout << "width : " << rect.width << std::endl;
    std:: cout << "length : " << rect.length << std::endl;
    std:: cout << "height : " << rect.height << std::endl;
    std:: cout << "yaw : " << rect.yaw << std::endl;

    Marker marker;

    marker.header.stamp = this->now();
    marker.header.frame_id = frame_id;

    marker.frame_locked = true;
    marker.lifetime = rclcpp::Duration(0.5);
    marker.ns = "bounding_box";
    marker.id = rect.id;
    marker.action = Marker::ADD;
    marker.type = Marker::TEXT_VIEW_FACING;
    marker.text = to_string(rect.id);

    marker.pose.position.x = rect.centerX;
    marker.pose.position.y = rect.centerY;
    marker.pose.position.z = 1.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    marker.scale.x = rect.width;
    marker.scale.y = rect.length;
    // marker.scale.x = 1;
    // marker.scale.y = 3;
    marker.scale.z = 1.0;
    marker.color.a = 0.7;
    marker.color.r = 1.0;
    marker.color.g = 1.0;
    marker.color.b = 1.0;

    markerArrayOutput.markers.push_back(marker);
  }

  pub->publish(markerArrayOutput);
  std:: cout << "===========================" << std::endl;

  prev_output = *outputArray;


  std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
  std::cout << "걸리는 시간(초) : " << sec.count() <<"seconds"<< std::endl;

}