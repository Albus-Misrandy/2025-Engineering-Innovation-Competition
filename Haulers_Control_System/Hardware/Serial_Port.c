#include "Serial_Port.h"

void send_16bits_data(int16_t value) {
    char buffer[20];
    sprintf(buffer, "%d,", value);
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void send_32bits_data(int32_t value) {
    char buffer[50];
    sprintf(buffer, "%d,", value);
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void send_int_data(int value) {
    char buffer[60];
    sprintf(buffer, "%d,", value);
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void send_16bitsfloat_data(float value) {
    char buffer[20];
    sprintf(buffer, "%.2f,", value);
    HAL_UART_Transmit(&huart1, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

int Receive_int_data(void)
{
    int receive_value = 0;
    uint8_t receive_buf[sizeof(int)];
    HAL_UART_Receive(&huart1, receive_buf, sizeof(int), HAL_MAX_DELAY);
    memcpy(&receive_value, receive_buf, sizeof(int));
    return receive_value;
}

int Receive_int_data_IT(void)
{
    int receive_value = 0;
    uint8_t receive_buf[sizeof(int)];
    HAL_UART_Receive_IT(&huart1, receive_buf, sizeof(int));
    memcpy(&receive_value, receive_buf, sizeof(int));
    return receive_value;
}

void send_float(float value)
{
    uint8_t b[4];
    memcpy(b, &value, sizeof(float));
    HAL_UART_Transmit(&huart1, b, sizeof(float), HAL_MAX_DELAY);
}
