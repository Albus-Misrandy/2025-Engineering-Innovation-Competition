#include "socket_transmit.h"

int socket_transmission::socket_check()
{
    if (server_fd == -1)
    {
        cerr << "Socket create failed."<<endl;
        return -1;
    }
    else
    {
        return 0;
    }
}

int socket_transmission::socket_init()
{
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
        cerr<<"Connected failed!"<<endl;
        return -1;
    }
    if(listen(server_fd, 5) < 0)
    {
        cerr<<"Listened failed!"<<endl;
        return -1;
    }
    else
    {
        cout<<"Waiting for the listener connect..."<<endl;
        return 0;
    }
}

int socket_transmission::check_client()
{
    // 接受客户端连接
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);
    if (client_fd < 0) {
        cerr << "Connect to the client failed!" << endl;
        return -1;
    }
    std::cout << "Cilent has been connected!" << std::endl;
    return 0;
}

void socket_transmission::wifi_transmit_image(Mat mv)
{
    vector<uchar> buffer;
    vector<int> param = {IMWRITE_JPEG_QUALITY, IMAGE_QUALITY};
    imencode(".jpg", mv, buffer, param);
    int net_img_size = htonl(buffer.size());
    send(client_fd, &net_img_size, sizeof(net_img_size), 0);
    send(client_fd, buffer.data(), buffer.size(), 0);
}

void socket_transmission::double_data_transmit(double value)
{
    send(client_fd, &value, sizeof(value), 0); // 直接发送 double 的字节数据
}

void socket_transmission::close_socket()
{
    close(client_fd);
    close(server_fd);
}