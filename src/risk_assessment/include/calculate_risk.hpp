#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <std_msgs/msg/string.hpp>

#include "rclcpp/rclcpp.hpp"

#include "nav_msgs/msg/odometry.hpp"
#include "derived_object_msgs/msg/object_array.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "visualization_msgs/msg/marker_array.hpp"

#include <vector>
#include <string>

using namespace std::chrono_literals;
using std::placeholders::_1;
using namespace nav_msgs::msg;
using namespace derived_object_msgs::msg;
using namespace visualization_msgs::msg;

class Calculate : public rclcpp::Node
{
public:
  Calculate() : Node("calculate_risk")
  {
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    odom_sub_ = this->create_subscription<Odometry>("/carla/ego_vehicle/odometry", qos_profile,std::bind(&Calculate::OdometryCallback, this, _1));
    object_sub_ = this->create_subscription<ObjectArray>("/carla/objects", qos_profile,std::bind(&Calculate::ObjectCallback, this, _1));
    marker_pub_ = this->create_publisher<MarkerArray>("risk_marker", qos_profile);
    // timer_ = this->create_wall_timer( 1ns, std::bind(&Calculate::Run, this));

  }

  private:
    // void publish_sample_msg();
    void OdometryCallback(const Odometry::SharedPtr msg);
    void ObjectCallback(const ObjectArray::SharedPtr msg);
    void Run();
    void calculateRisk();
    double GetDistance(double x1, double y1, double x2, double y2);
    double GetRelaticeVelocity(double vx1, double vy1, double vx2, double vy2);
    double GetTTC(double distance, double rel_velocity);

    // rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<MarkerArray>::SharedPtr marker_pub_;
    rclcpp::Subscription<Odometry>::SharedPtr odom_sub_;
    rclcpp::Subscription<ObjectArray>::SharedPtr object_sub_;

    rclcpp::Logger logger = this->get_logger();

    double ego_x_;
    double ego_y_;

    double ego_yaw_;

    double ego_vx_;
    double ego_vy_;

    std::vector<Object> obj_vec_;

};