#ifndef __UART_SETTING_H__
#define __UART_SRTTING_H__

#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

class uart_port
{
public:
    io_service io;
    serial_port *serial;
    void uart_setting_init();
    void uart_send_int(int value);
    void uart_send_double(double value);
    void uart_send_int_vector(vector<int> vector_int);
    int uart_receive_int();
};



#endif