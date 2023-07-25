#include "data_collection.hpp"
Data::Data() : Node("data_collection")
{
  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
  bev_sub_ = this->create_subscription<OutputArray>("/track_output", qos_profile,std::bind(&Data::bevCallback, this, _1));

  id = 1;
}

void Data::Run()
{
  // ReadExample();
  ReadCollectFile();
  Collect();
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

void Data::ReadCollectFile()
{
  try {

    // JSON 파일을 읽기 모드로 열기

    ifstream ifs(collect_filePath);

    if (!ifs.is_open()) {
      throw runtime_error("failed to open the COLLECT file");
    }

    // 파일 내용을 문자열로 읽기

    string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    // JSON 문자열 파싱

    collect_doc.Parse(json.c_str());
  }

  catch (std::exception& e) {
    // 예외 처리
    std::cerr << "Error: " << e.what() << std::endl;

    std::cout << "Make a New Collect File..." << std::endl;

    Document new_doc;
    new_doc.SetObject();

    Value data(kArrayType);
    new_doc.AddMember("data",data,new_doc.GetAllocator());

    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    new_doc.Accept(writer);

    ofstream outFile(collect_filePath);

    if (outFile.is_open()) {
      outFile << buffer.GetString();
      outFile.close();
      std::cout << "Collect JSON made in : " << collect_filePath << std::endl;
    } 
    else {
      std::cerr << "Cannot make file" << std::endl;
    }

    std::cout << "New Collect File done" << std::endl;

    // 만든 파일을 읽어서 collect_doc만듬
    // JSON 파일을 읽기 모드로 열기

    ifstream ifs(collect_filePath);

    if (!ifs.is_open()) {
      throw runtime_error("failed to open the COLLECT file");
    }

    // 파일 내용을 문자열로 읽기

    string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    // JSON 문자열 파싱

    collect_doc.Parse(json.c_str());
  }
}

void Data::Collect()
{
  
  
  Value element(kObjectType);
  
  element.AddMember("frame",id++,collect_doc.GetAllocator());

  Value ego_vehicle(kObjectType);
  ego_vehicle.AddMember("latitude",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("longitude",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("throttle",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("brake",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("steering_angle",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("speed",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("gear",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("total_distance",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("driving_distance",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("driving_mode",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("speed_limit",127.103803276738,collect_doc.GetAllocator());
  ego_vehicle.AddMember("traffic_light",127.103803276738,collect_doc.GetAllocator());
  
  element.AddMember("ego_vehicle",ego_vehicle,collect_doc.GetAllocator());

  Value objects(kArrayType);
  for(int i=0;i<3;i++)
  {
    Value object(kObjectType);
    object.AddMember("id",0+i,collect_doc.GetAllocator());
    object.AddMember("type",1+i,collect_doc.GetAllocator());
    object.AddMember("score",0.781+i,collect_doc.GetAllocator());
    object.AddMember("pos_x",-13.879913330078125+i,collect_doc.GetAllocator());
    object.AddMember("pos_y",25.54883575439453+i,collect_doc.GetAllocator());
    object.AddMember("width",1.9385488033294678+i,collect_doc.GetAllocator());
    object.AddMember("length",4.593875408172607+i,collect_doc.GetAllocator());
    object.AddMember("height",1.7216850519180298+i,collect_doc.GetAllocator());
    object.AddMember("yaw",1.7347204685211182+i,collect_doc.GetAllocator());
    object.AddMember("vel_x",-5.9045305252075195+i,collect_doc.GetAllocator());
    object.AddMember("vel_y",0.9427621364593506+i,collect_doc.GetAllocator());
    object.AddMember("relative_speed",4.67+i,collect_doc.GetAllocator());
    object.AddMember("ttc",2.1+i,collect_doc.GetAllocator());

    objects.PushBack(object,collect_doc.GetAllocator());
  }
  
  element.AddMember("objects",objects,collect_doc.GetAllocator());

  collect_doc["data"].PushBack(element,collect_doc.GetAllocator());
  
  StringBuffer buffer;
  PrettyWriter<StringBuffer> writer(buffer);
  collect_doc.Accept(writer);

  ofstream outFile(collect_filePath);
  
  if (outFile.is_open()) {
    outFile << buffer.GetString();
    outFile.close();
    std::cout << "Collect Data" << std::endl;
  } 
  else {
    std::cerr << "Cannot Collect file" << std::endl;
  }
}

int main (int argc, char * argv[])
{
	rclcpp::init (argc, argv);
  auto node = std::make_shared<Data>();
  node->Run();
  node->Run();
  node->Run();
  node->Run();
  node->Run();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}