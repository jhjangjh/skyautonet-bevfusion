#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <std_msgs/msg/string.hpp>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
#include "custom_msgs/msg/output_array.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"



using std::placeholders::_1;

using namespace std::chrono_literals;
using namespace custom_msgs::msg;
using namespace std;
using namespace rapidjson;

class Data : public rclcpp::Node
{
public:
  Data();
  void Run();

private:
  void bevCallback(const OutputArray::SharedPtr msg);
  void ReadParseFile();
  void Parse();
  void ReadCollectFile();
  void Collect();

  const char* collect_filePath = "/home/bev/bev_ws/src/data_pkg/collect.json";
  const char* parse_filePath = "/home/bev/bev_ws/src/data_pkg/parse.json";

  rclcpp::Subscription<OutputArray>::SharedPtr bev_sub_;

  // for data parse
  OutputArray bev_output; 
  Document parse_doc;

  // for data collect
  int frame;
  Document collect_doc;
  
};