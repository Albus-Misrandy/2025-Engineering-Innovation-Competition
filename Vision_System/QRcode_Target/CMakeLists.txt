add_library(QRcode_Target QRcode.cpp QRcode.h)

target_link_libraries(QRcode_Target PUBLIC ${OpenCV_LIBS})