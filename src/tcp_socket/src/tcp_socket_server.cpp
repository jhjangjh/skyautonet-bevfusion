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
  std::cout << "Init start" << std::endl;
  std::cout << "Init 0" << std::endl;
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);

  int option = 1; // SO_REUSEADDR 의 옵션 값을 TRUE 로
  setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  if(serv_sock == -1) error_handling("socket error");
  std::cout << "Init 1" << std::endl;
  memset(&serv_addr, 0, sizeof(serv_addr));
  std::cout << "Init 2" << std::endl;
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  std::cout << "Init 2.5" << std::endl;

  serv_addr.sin_port=htons(atoi("1234"));
  std::cout << "Init 3" << std::endl;
  
  if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) error_handling("bind error");
  std::cout << "Init 4" << std::endl;
  
  if(listen(serv_sock, 5) == -1) error_handling("listen error");
  std::cout << "Init 5" << std::endl;

  clnt_addr_size = sizeof(clnt_addr);
  clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
  if(clnt_sock == -1) error_handling("accept error");
  std::cout << "Init end" << std::endl;

  flag = true;

}

void TCPServer::Run()
{
  Box b;
  b.pos_x = 1.7;
  b.pos_y = 2.7;
  b.width = 3.7;
  b.length = 4.7;
  b.height = 5.7;
  b.yaw = 6.7;
  b.vel_x = 7.7;
  b.vel_y = 8.7;  
    
  Info i;
  i.id = 1;
  i.score = 0.7;
  i.label = 3;
  i.box = b;

  int len = sizeof(i);
  send(clnt_sock, (char*)&i, len,0);
  RCLCPP_INFO_STREAM(this->get_logger(),"send");
}

void TCPServer::callback(const OutputArray::SharedPtr msg)
{
  if(flag)
  {
    Run();
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
  // node->Init();
  // node->Run();
  rclcpp::spin(node);
  rclcpp::shutdown();

  return 0;
}