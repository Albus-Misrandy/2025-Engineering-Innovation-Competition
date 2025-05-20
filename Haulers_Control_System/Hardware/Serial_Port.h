#ifndef __SERIAL_PORT_H__
#define __SERIAL_PORT_H__

#include "usart.h"
#include <stdio.h>  // 用于 sprintf 函数
#include <string.h> // 用于 strlen 函数

void send_16bits_data(int16_t value);
void send_32bits_data(int32_t value);
void send_int_data(int value);
void send_16bitsfloat_data(float value);
int Receive_int_data(void);
void send_float(float value);

#endif
