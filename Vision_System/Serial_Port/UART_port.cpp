#include "uart_setting.h"

void uart_port::uart_setting_init()
{
    *serial = serial_port(io, "/dev/ttyUSB0");
    serial->set_option(serial_port_base::baud_rate(115200));
    serial->set_option(serial_port_base::character_size(8));
    serial->set_option(serial_port_base::parity(serial_port_base::parity::none));
    serial->set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    serial->set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
}

void uart_port::uart_send_int(int value)
{
    char send_buf[sizeof(int)];
    memcpy(send_buf, &value, sizeof(int));
    write(*serial, buffer(send_buf, sizeof(int)));
}

void uart_port::uart_send_double(double value)
{
    char send_buf[sizeof(double)];
    memcpy(send_buf, &value, sizeof(double));
    write(*serial, buffer(send_buf, sizeof(double)));
}

void uart_port::uart_send_int_vector(vector<int> vector_int)
{
    int size = vector_int.size();
    write(*serial, buffer(&size, sizeof(int)));
    write(*serial, buffer(vector_int.data(), size * sizeof(int)));
}

int uart_port::uart_receive_int()
{
    int receive_data;
    read(*serial, buffer(reinterpret_cast<char*>(&receive_data), sizeof(int)));
    return receive_data;
}
