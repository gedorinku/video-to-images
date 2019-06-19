cmake_minimum_required(VERSION 3.14)
project(video_to_images)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 2.4.3 REQUIRED)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     ON)
find_package(Boost 1.69 REQUIRED COMPONENTS filesystem system)

include_directories(
        "${PROJECT_SOURCE_DIR}"
        "${Boost_INCLUDE_DIRS}")

add_executable(video_to_images main.cpp)
target_link_libraries(video_to_images
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        )
