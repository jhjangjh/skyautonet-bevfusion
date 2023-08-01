#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <custom_msgs/msg/output_array.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;
using namespace custom_msgs::msg;

using std::placeholders::_1;

typedef struct _box
{
  float pos_x;
  float pos_y;
  float width;
  float length;
  float height;
  float yaw;
  float vel_x;
  float vel_y; 
}Box;

typedef struct _object
{
  int id;
  float score;
  int label;
  Box box;
}Object;

typedef struct _bev
{
  int size;
  Object obj[50];
}Bev;

const char* PORT = "1234";

class TCPServer : public rclcpp::Node
{
  public:
    TCPServer();
    virtual ~TCPServer();

    void Init();
    void Run(const OutputArray::SharedPtr msg);

  private:
    void callback(const OutputArray::SharedPtr msg);

    rclcpp::Subscription<OutputArray>::SharedPtr tracking_sub_;

    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size;

    void error_handling(std::string message);
    bool flag = false;

    std::thread tcp_server_thread_;

};