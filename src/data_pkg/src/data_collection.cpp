#include "data_collection.hpp"
Data::Data() : Node("data_collection")
{
  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
  bev_sub_ = this->create_subscription<OutputArray>("/track_output", qos_profile,std::bind(&Data::bevCallback, this, _1));

  ReadExample();
}

void Data::ReadExample()
{
  try {

  // JSON 파일을 읽기 모드로 열기

  ifstream ifs("example.json");

  if (!ifs.is_open()) {
      throw runtime_error("failed to open the file");
  }

  // 파일 내용을 문자열로 읽기

  string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

  // JSON 문자열 파싱

  doc.Parse(json.c_str());
  }

  catch (std::exception& e) {
    // 예외 처리
    std::cerr << "Error: " << e.what() << std::endl;
    rclcpp::shutdown();
  }
}

void Data::bevCallback(const OutputArray::SharedPtr msg)
{
  bev_output = *msg;
}

void Data::Parse()
{

}

void Data::Collect()
{
  
}

int main (int argc, char * argv[])
{
	rclcpp::init (argc, argv);
  auto node = std::make_shared<Data>();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}