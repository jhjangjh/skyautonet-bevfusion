#include "SortRos.h"

SortRos::SortRos() : Node("sort_ros") {
  // this->declare_parameter("param_maxAge", 1);
  // this->declare_parameter("param_minHits", 2);
  // this->declare_parameter("param_iouThreshold", 0.9);
}

void SortRos::setup() {
  double maxAge = 7;
  double minHits = 0;
  double iouThreshold = 0.00001;

  sorter = new Sort(maxAge, minHits, iouThreshold);
  // sorter = new Sort(param_maxAge, param_minHits, param_iouThreshold);

  viz_pub = this->create_publisher<MarkerArray>("/markers_tracked",
                                            rclcpp::QoS(rclcpp::KeepLast(10)));

  output_pub = this->create_publisher<custom_msgs::msg::OutputArray>("/track_output",
                                            rclcpp::QoS(rclcpp::KeepLast(10)));                                            

  sub = this->create_subscription<custom_msgs::msg::OutputArray>(
      "/bev_output", rclcpp::QoS(rclcpp::KeepLast(10)),
      std::bind(&SortRos::rectArrayCallback, this, std::placeholders::_1));
}

void SortRos::rectArrayCallback(const custom_msgs::msg::OutputArray::SharedPtr outputArray) {

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();



  // param_maxAge = this->get_parameter("param_maxAge").as_int();
  // param_minHits = this->get_parameter("param_minHits").as_int();
  // param_iouThreshold = this->get_parameter("param_iouThreshold").as_double();
  // std:: cout << "param_maxAge : " << param_maxAge << std::endl;
  // std:: cout << "param_minHits : " << param_minHits << std::endl;
  // std:: cout << "param_iouThreshold : " << param_iouThreshold << std::endl;
  std::string frame_id = outputArray->header.frame_id;
  std::vector<SortRect> rects;

  for (auto output : outputArray->outputs) {
    // if(sqrt(pow(output.pose.position.x,2)+pow(output.pose.position.y,2))>30) continue;
    if((abs(output.box.pos_x) > 21) || abs(output.box.pos_y) > 50) continue;
    
    SortRect rect;
    rect.id = 0;
    rect.centerX = output.box.pos_x;
    rect.centerY = output.box.pos_y;

    // std:: cout << "--------------------------" << std::endl;
    // std:: cout << "x좌표 : " << rect.centerX << std::endl;
    // std:: cout << "y좌표 : " << rect.centerY << std::endl;

    rect.width = output.box.width;
    rect.length = output.box.length;
    rect.height = output.box.height;
    rect.yaw = output.box.yaw;
    rect.score = output.score;
    rect.label = output.label;

    rects.push_back(rect);
  }

  std::vector<SortRect> output = sorter->update(rects);
  
  MarkerArray markerArrayOutput;


//============== 시각화용=========================================
  Marker delete_marker;
  delete_marker.action = Marker::DELETEALL; 
  markerArrayOutput.markers.push_back(delete_marker);

  Marker rectangle_marker;
  rectangle_marker.header.frame_id = "map";
  rectangle_marker.action = Marker::ADD;
  rectangle_marker.type = Marker::LINE_STRIP;

  geometry_msgs::msg::Point p1;
  p1.x = -21;
  p1.y = 50;
  rectangle_marker.points.push_back(p1);

  geometry_msgs::msg::Point p2;
  p2.x = 21;
  p2.y = 50;
  rectangle_marker.points.push_back(p2);

  geometry_msgs::msg::Point p3;
  p3.x = 21;
  p3.y = -50;
  rectangle_marker.points.push_back(p3);

  geometry_msgs::msg::Point p4;
  p4.x = -21;
  p4.y = -50;
  rectangle_marker.points.push_back(p4);

  geometry_msgs::msg::Point p5;
  p5.x = -21;
  p5.y = 50;
  rectangle_marker.points.push_back(p5);

  rectangle_marker.color.a = 1;
  rectangle_marker.color.r = 1;
  rectangle_marker.color.g = 1;
  rectangle_marker.color.b = 0;

  rectangle_marker.scale.x = 1;
  rectangle_marker.scale.y = 1;
  rectangle_marker.scale.z = 1;

  markerArrayOutput.markers.push_back(rectangle_marker);





//===============================================================

  for (auto rect : output) {
    
    std:: cout << "Object ID : " << rect.id << std::endl;

    Marker marker;

    marker.header.stamp = this->now();
    marker.header.frame_id = "map";

    // marker.frame_locked = true;
    // marker.lifetime = rclcpp::Duration(0.5);
    marker.ns = "bounding_box";
    marker.id = rect.id;
    marker.action = Marker::ADD;
    // marker.type = Marker::CUBE;
    marker.type = Marker::TEXT_VIEW_FACING;
    string id_text = to_string(rect.id);
    marker.text = id_text;

    marker.pose.position.x = rect.centerX;
    marker.pose.position.y = rect.centerY;
    marker.pose.position.z = 1.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // marker.scale.x = rect.width;
    // marker.scale.y = rect.length;
    // marker.scale.z = 1.0;
    marker.scale.x = 5;
    marker.scale.y = 5;
    marker.scale.z = 5;
    marker.color.a = 0.7;
    marker.color.r = 1.0;
    marker.color.g = 1.0;
    marker.color.b = 1.0;

    markerArrayOutput.markers.push_back(marker);
  }

  custom_msgs::msg::OutputArray track_output;
  track_output.header.frame_id = frame_id;
  track_output.header.stamp = this->now();

  for (auto rect : output) {
    custom_msgs::msg::Output track;

    track.box.pos_x = rect.centerX;
    track.box.pos_y = rect.centerY;
    track.box.width = rect.width;
    track.box.length = rect.length;
    track.box.height = rect.height;
    track.box.yaw = rect.yaw;

    track.score = rect.score;
    track.label = track.label;

    track_output.outputs.push_back(track);
  }

  viz_pub->publish(markerArrayOutput);
  output_pub->publish(track_output);

  std:: cout << "===========================" << std::endl;

  std::chrono::duration<double>sec = std::chrono::system_clock::now() - start;
  std::cout << "Tracking 알고리즘 수행시간(초) : " << sec.count() <<"sec"<< std::endl;
}