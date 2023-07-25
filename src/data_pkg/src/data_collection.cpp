#include "data_collection.hpp"
Data::Data() : Node("data_collection")
{
  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
  bev_sub_ = this->create_subscription<OutputArray>("/track_output", qos_profile,std::bind(&Data::bevCallback, this, _1));

  frame = 0;
}

void Data::bevCallback(const OutputArray::SharedPtr msg)
{
  bev_output = msg;

  string frame_id = bev_output->header.frame_id;
  frame = stoi(frame_id.substr(5));

  Run();
  // RCLCPP_INFO_STREAM(this->get_logger(),"Callback");
}

void Data::Run()
{
  ReadParseFile();
  Parse();
  ReadCollectFile();
  Collect();
}

void Data::ReadParseFile()
{
  try {

    // JSON 파일을 읽기 모드로 열기

    ifstream ifs(parse_filePath);

    if (!ifs.is_open()) {
      throw runtime_error("failed to open the Parse file");
    }

    // 파일 내용을 문자열로 읽기

    string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    // JSON 문자열 파싱

    parse_doc.Parse(json.c_str());
  }

  catch (std::exception& e) {
    // 예외 처리
    std::cerr << "Error: " << e.what() << std::endl;

    std::cout << "Make a New Parse File..." << std::endl;

    Document new_doc;
    new_doc.SetObject();

    new_doc.AddMember("frame",NULL,new_doc.GetAllocator());

    Value ego_vehicle(kObjectType);
    ego_vehicle.AddMember("latitude",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("longitude",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("throttle",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("brake",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("steering_angle",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("speed",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("gear",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("total_distance",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("driving_distance",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("driving_mode",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("speed_limit",NULL,parse_doc.GetAllocator());
    ego_vehicle.AddMember("traffic_light",NULL,parse_doc.GetAllocator());

    new_doc.AddMember("ego_vehicle",ego_vehicle,parse_doc.GetAllocator());

    Value objects(kArrayType);
    for(int i=0;i<3;i++)
    {
      Value object(kObjectType);
      object.AddMember("id",NULL,parse_doc.GetAllocator());
      object.AddMember("type",NULL,parse_doc.GetAllocator());
      object.AddMember("score",NULL,parse_doc.GetAllocator());
      object.AddMember("pos_x",NULL,parse_doc.GetAllocator());
      object.AddMember("pos_y",NULL,parse_doc.GetAllocator());
      object.AddMember("width",NULL,parse_doc.GetAllocator());
      object.AddMember("length",NULL,parse_doc.GetAllocator());
      object.AddMember("height",NULL,parse_doc.GetAllocator());
      object.AddMember("yaw",NULL,parse_doc.GetAllocator());
      object.AddMember("vel_x",NULL,parse_doc.GetAllocator());
      object.AddMember("vel_y",NULL,parse_doc.GetAllocator());
      object.AddMember("relative_speed",NULL,parse_doc.GetAllocator());
      object.AddMember("ttc",NULL,parse_doc.GetAllocator());

      objects.PushBack(object,parse_doc.GetAllocator());
    }
  
    new_doc.AddMember("objects",objects,parse_doc.GetAllocator());


    StringBuffer buffer;
    PrettyWriter<StringBuffer> writer(buffer);
    new_doc.Accept(writer);

    ofstream outFile(parse_filePath);

    if (outFile.is_open()) {
      outFile << buffer.GetString();
      outFile.close();
      std::cout << "Parse JSON made in : " << parse_filePath << std::endl;
    } 
    else {
      std::cerr << "Cannot make Parse file" << std::endl;
    }

    std::cout << "New Parse File done" << std::endl;

    // 만든 파일을 읽어서 parse_doc만듬
    // JSON 파일을 읽기 모드로 열기

    ifstream ifs(parse_filePath);

    if (!ifs.is_open()) {
      throw runtime_error("failed to open the Parse file");
    }

    // 파일 내용을 문자열로 읽기

    string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    // JSON 문자열 파싱

    parse_doc.Parse(json.c_str());
  }
}

void Data::Parse()
{
  // frame 업데이트
  if (parse_doc.HasMember("frame")) {
    Value& new_frame = parse_doc["frame"];
    if (new_frame.IsInt()) {
        new_frame.SetInt(frame);
    }
  }

  // ego_vehicle 업데이트
  if (parse_doc.HasMember("ego_vehicle")) {
    Value& new_ego_vehicle = parse_doc["ego_vehicle"];
    if (new_ego_vehicle.IsObject()) {
      new_ego_vehicle.RemoveAllMembers();

      new_ego_vehicle.AddMember("latitude",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("longitude",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("throttle",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("brake",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("steering_angle",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("speed",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("gear",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("total_distance",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("driving_distance",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("driving_mode",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("speed_limit",NULL,parse_doc.GetAllocator());
      new_ego_vehicle.AddMember("traffic_light",NULL,parse_doc.GetAllocator());
    }
  }

  // objects 업데이트
  if (parse_doc.HasMember("objects")) {
    Value& new_objects = parse_doc["objects"];
    if (new_objects.IsArray()) {
      new_objects.SetArray();

      for(int i=0;i<bev_output->outputs.size();i++)
      {
        Value object(kObjectType);
        object.AddMember("id",bev_output->outputs[i].id,parse_doc.GetAllocator());
        object.AddMember("type",bev_output->outputs[i].label,parse_doc.GetAllocator());
        object.AddMember("score",bev_output->outputs[i].score,parse_doc.GetAllocator());
        object.AddMember("pos_x",bev_output->outputs[i].box.pos_x,parse_doc.GetAllocator());
        object.AddMember("pos_y",bev_output->outputs[i].box.pos_y,parse_doc.GetAllocator());
        object.AddMember("width",bev_output->outputs[i].box.width,parse_doc.GetAllocator());
        object.AddMember("length",bev_output->outputs[i].box.length,parse_doc.GetAllocator());
        object.AddMember("height",bev_output->outputs[i].box.height,parse_doc.GetAllocator());
        object.AddMember("yaw",bev_output->outputs[i].box.yaw,parse_doc.GetAllocator());
        object.AddMember("vel_x",NULL,parse_doc.GetAllocator());
        object.AddMember("vel_y",NULL,parse_doc.GetAllocator());
        object.AddMember("relative_speed",NULL,parse_doc.GetAllocator());
        object.AddMember("ttc",NULL,parse_doc.GetAllocator());

        new_objects.PushBack(object,parse_doc.GetAllocator());
      }
    }
  }

  // 파일에 업데이트

  StringBuffer buffer;
  PrettyWriter<StringBuffer> writer(buffer);
  parse_doc.Accept(writer);

  ofstream outFile(parse_filePath);
  
  if (outFile.is_open()) {
    outFile << buffer.GetString();
    outFile.close();
    std::cout << "Parse Data" << std::endl;
  } 
  else {
    std::cerr << "Cannot Parse file" << std::endl;
  }

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
      std::cerr << "Cannot make Collect file" << std::endl;
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
  
  element.AddMember("frame",frame,collect_doc.GetAllocator());

  Value ego_vehicle(kObjectType);
  ego_vehicle.AddMember("latitude",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("longitude",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("throttle",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("brake",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("steering_angle",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("speed",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("gear",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("total_distance",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("driving_distance",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("driving_mode",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("speed_limit",NULL,collect_doc.GetAllocator());
  ego_vehicle.AddMember("traffic_light",NULL,collect_doc.GetAllocator());
  
  element.AddMember("ego_vehicle",ego_vehicle,collect_doc.GetAllocator());

  Value objects(kArrayType);
  for(int i=0;i<bev_output->outputs.size();i++)
  {
    Value object(kObjectType);

    object.AddMember("id",bev_output->outputs[i].id,collect_doc.GetAllocator());
    object.AddMember("type",bev_output->outputs[i].label,collect_doc.GetAllocator());
    object.AddMember("score",bev_output->outputs[i].score,collect_doc.GetAllocator());
    object.AddMember("pos_x",bev_output->outputs[i].box.pos_x,collect_doc.GetAllocator());
    object.AddMember("pos_y",bev_output->outputs[i].box.pos_y,collect_doc.GetAllocator());
    object.AddMember("width",bev_output->outputs[i].box.width,collect_doc.GetAllocator());
    object.AddMember("length",bev_output->outputs[i].box.length,collect_doc.GetAllocator());
    object.AddMember("height",bev_output->outputs[i].box.height,collect_doc.GetAllocator());
    object.AddMember("yaw",bev_output->outputs[i].box.yaw,collect_doc.GetAllocator());
    object.AddMember("vel_x",NULL,collect_doc.GetAllocator());
    object.AddMember("vel_y",NULL,collect_doc.GetAllocator());
    object.AddMember("relative_speed",NULL,collect_doc.GetAllocator());
    object.AddMember("ttc",NULL,collect_doc.GetAllocator());

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
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}