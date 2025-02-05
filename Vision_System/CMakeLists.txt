cmake_minimum_required(VERSION 3.10)
project(Vision_System)

find_package(OpenCV REQUIRED)

add_subdirectory(Image_Processing)
add_subdirectory(Socket_transmit)

add_executable(main main.cpp)

target_include_directories(
    main
    PUBLIC ${PROJECT_SOURCE_DIR} ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(main Image_Processing Socket_transmit ${OpenCV_LIBS})

message(STATUS "Albus Misrandy")
