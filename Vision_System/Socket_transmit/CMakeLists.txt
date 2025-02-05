add_library(Socket_transmit socket_transmit.cpp socket_transmit.h)

target_link_libraries(Socket_transmit PUBLIC ${OpenCV_LIBS})