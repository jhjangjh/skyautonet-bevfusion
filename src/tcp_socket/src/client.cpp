#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>

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

void error_handling(char *message);

int main(int argc, char * argv[])
{
  int clnt_sock;
  struct sockaddr_in serv_addr;
  Bev bev;

  clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
  if(clnt_sock == -1) error_handling("socket error");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(PORT));

  if(connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) error_handling("connect error");
  
  
  while (1) {
    int len = recv(clnt_sock, (char*)&bev, sizeof(bev),0);
    if(len <= 0) {
      error_handling("read error");
      break;
      
    } 
    
    std::cout << " Object number : " << bev.size << std::endl;

    for(int i = 0; i<bev.size; i++)
    {
      std::cout << "-----------------------------------------" << std::endl;
      std::cout << std::endl;
      std::cout << "           Object[" << i << "]           " << std::endl;
      std::cout << "id : " << bev.obj[i].id << std::endl;
      std::cout << "score : " << bev.obj[i].score << std::endl;
      std::cout << "label : " << bev.obj[i].label << std::endl;
      std::cout << "Box info" << std::endl;
      std::cout << "pos_x : " << bev.obj[i].box.pos_x << std::endl;
      std::cout << "pos_y : " << bev.obj[i].box.pos_y << std::endl;
      std::cout << "width : " << bev.obj[i].box.width << std::endl;
      std::cout << "length : " << bev.obj[i].box.length << std::endl;
      std::cout << "height : " << bev.obj[i].box.height << std::endl;
      std::cout << "yaw : " << bev.obj[i].box.yaw << std::endl;
      std::cout << "vel_x : " << bev.obj[i].box.vel_x << std::endl;
      std::cout << "vel_y : " << bev.obj[i].box.vel_y << std::endl;
      std::cout << std::endl;
      

    }  
  }
  
 
  close(clnt_sock);
  return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}