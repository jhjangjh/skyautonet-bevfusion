#include <thread>

#include "tcp_socket_server.hpp"

TCPServer::TCPServer() : Node("tcp_socket")
{
  auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
  tracking_sub_ = this->create_subscription<OutputArray>("/track_output", qos_profile,
                                                          std::bind(&TCPServer::callback, this, _1));
  flag = false;

  tcp_server_thread_ = std::thread(&TCPServer::Init, this);
}

TCPServer::~TCPServer() {
  close(clnt_sock);
  close(serv_sock);
}

void TCPServer::Init()
{
  std::cout << "Waiting client..." << std::endl;
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);

  int option = 1; // SO_REUSEADDR 의 옵션 값을 TRUE 로
  setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  if(serv_sock == -1) error_handling("socket error");
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);

  serv_addr.sin_port=htons(atoi(PORT));
  
  if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) error_handling("bind error");
  
  if(listen(serv_sock, 5) == -1) error_handling("listen error");

  clnt_addr_size = sizeof(clnt_addr);
  clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
  if(clnt_sock == -1) error_handling("accept error");
  std::cout << "Client Connected!" << std::endl;

  flag = true;

}

void TCPServer::Run(const OutputArray::SharedPtr msg)
{
  Bev bev;
  bev.size = msg->outputs.size();
  
  for(int i = 0; i < bev.size; i++)
  {
    Box box;

    box.pos_x  = msg->outputs[i].box.pos_x;
    box.pos_y  = msg->outputs[i].box.pos_y;
    box.width  = msg->outputs[i].box.width;
    box.length = msg->outputs[i].box.length;
    box.height = msg->outputs[i].box.height;
    box.yaw    = msg->outputs[i].box.yaw;
    box.vel_x  = msg->outputs[i].box.vel_x;
    box.vel_y  = msg->outputs[i].box.vel_y;  
      
    Object obj;
    obj.id    = msg->outputs[i].id;
    obj.score = msg->outputs[i].score;
    obj.label = msg->outputs[i].label;
    obj.box = box;

    bev.obj[i] = obj;
  }

  bev.time = std::chrono::high_resolution_clock::now();

  int len = sizeof(bev);
  send(clnt_sock, (char*)&bev, len,0);
  RCLCPP_INFO_STREAM(this->get_logger(),"send " + msg->header.frame_id);
}

void TCPServer::callback(const OutputArray::SharedPtr msg)
{
  if(flag)
  {
    Run(msg);
  }
}

void TCPServer::error_handling(std::string message)
{
  RCLCPP_WARN_STREAM(this->get_logger(), ("error_handling : " + message));
  rclcpp::shutdown();
}

int main (int argc, char * argv[])
{
	rclcpp::init (argc, argv);
  auto node = std::make_shared<TCPServer>();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}