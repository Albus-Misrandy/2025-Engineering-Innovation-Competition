add_library(Serial_Port UART_port.cpp uart_setting.h)

target_link_libraries(Serial_Port PUBLIC ${OpenCV_LIBS})