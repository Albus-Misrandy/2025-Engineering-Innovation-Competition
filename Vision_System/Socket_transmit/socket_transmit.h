#ifndef __SOCKET_TRANSMIT_H__
#define __SOCKET_TRANSMIT_H__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>

#define PORT 8888
#define IMAGE_QUALITY 60  // JPEG压缩质量

using namespace std;
using namespace cv;

class socket_transmission
{
    public:
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    int socket_check();
    int socket_init();
    int check_client();
    void wifi_transmit_image(Mat mv);
    void double_data_transmit(double value);
    void close_socket();
};

#endif