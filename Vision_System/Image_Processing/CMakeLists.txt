add_library(Image_Processing image_processing.cpp image_processing.h)

target_link_libraries(Image_Processing PUBLIC ${OpenCV_LIBS})