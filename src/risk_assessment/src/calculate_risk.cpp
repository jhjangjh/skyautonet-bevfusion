#include "calculate_risk.hpp"

void Calculate::OdometryCallback(const Odometry::SharedPtr msg)
{
  ego_x_ = msg->pose.pose.position.x;
  ego_y_ = msg->pose.pose.position.y;

  tf2::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf2::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
  ego_yaw_ = yaw;

  ego_vx_ = msg->twist.twist.linear.x;
  ego_vy_ = msg->twist.twist.linear.y;
}

void Calculate::ObjectCallback(const ObjectArray::SharedPtr msg)
{
  Object temp;
  for(auto i = 0 ; i < msg->objects.size() ; i++)
  {
    if(msg->objects[i].shape.dimensions[0]<0.01 || msg->objects[i].shape.dimensions[1]<0.01 || msg->objects[i].shape.dimensions[2]<0.01) continue;
    temp = msg->objects[i];
    obj_vec_.push_back(temp);
  }

  Run();
}

void Calculate::Run()
{
  calculateRisk();
}

void Calculate::calculateRisk()
{
  RCLCPP_INFO_STREAM(logger,"cal");

  // MarkerArray risk_marker_arr;

  // Marker delete_marker;
  // delete_marker.action = Marker::DELETEALL; 
  // risk_marker_arr.markers.push_back(delete_marker);

  for (std::vector<Object>::iterator itr = obj_vec_.begin(); itr != obj_vec_.end(); ++itr) {
    if(itr->id == 145) continue;
    double distance;
    double rel_velocity;
    double ttc;

    distance = GetDistance(ego_x_,ego_y_,itr->pose.position.x,itr->pose.position.y);
    rel_velocity = GetRelaticeVelocity(ego_vx_,ego_vy_,itr->twist.linear.x,itr->twist.linear.y);
    ttc = GetTTC(distance,rel_velocity);

    RCLCPP_INFO_STREAM(logger,"Object ID :" << itr->id);
    RCLCPP_INFO_STREAM(logger,"distance :" << distance);
    RCLCPP_INFO_STREAM(logger,"relative velocity :" << rel_velocity);
    RCLCPP_INFO_STREAM(logger,"time to collision :" << ttc);

    // Marker risk_marker;

    // risk_marker.header.stamp = this->now();
    // risk_marker.header.frame_id = "map";

    // risk_marker.id = itr->id;
    // risk_marker.ns = "risk";
    // risk_marker.action = Marker::ADD;
    // risk_marker.type = Marker::TEXT_VIEW_FACING;
    // std::string id_text = std::to_string(ttc);
    // risk_marker.text = id_text;

    // risk_marker.pose.position.x = itr->pose.position.x;
    // risk_marker.pose.position.y = itr->pose.position.y;
    // risk_marker.pose.position.z = itr->pose.position.z;
    // risk_marker.pose.orientation.x = 0.0;
    // risk_marker.pose.orientation.y = 0.0;
    // risk_marker.pose.orientation.z = 0.0;
    // risk_marker.pose.orientation.w = 1.0;

    // risk_marker.scale.x = 5;
    // risk_marker.scale.y = 5;
    // risk_marker.scale.z = 5;
    // risk_marker.color.a = 0.7;
    // risk_marker.color.r = 1.0;
    // risk_marker.color.g = 1.0;
    // risk_marker.color.b = 1.0;

    // risk_marker_arr.markers.push_back(risk_marker);

  }

  // marker_pub_->publish(risk_marker_arr);
}

double Calculate::GetDistance(double x1, double y1, double x2, double y2)
{
  double distance;
  distance = sqrt(pow((x1-x2),2)+pow((y1-y2),2));

  return distance;
}

double Calculate::GetRelaticeVelocity(double vx1, double vy1, double vx2, double vy2)
{
  double rel_velocity;
  rel_velocity = sqrt(pow((vx1-vx2),2)+pow((vy1-vy2),2));

  return rel_velocity;
}

double Calculate::GetTTC(double distance, double rel_velocity)
{
  double ttc;
  ttc = distance/rel_velocity;

  return ttc;
}

int main (int argc, char * argv[])
{
	rclcpp::init (argc, argv);
    auto node = std::make_shared<Calculate>();
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}