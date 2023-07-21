#include "SortRos.h"
// #include "SortRos_custom.h"
#include "rclcpp/rclcpp.hpp"

int main(int argc, char* argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<SortRos>();
  node->setup();
  rclcpp::spin(node);
  return 0;
}