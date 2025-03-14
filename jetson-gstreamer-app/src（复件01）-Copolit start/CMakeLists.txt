project(jetson-gstreamer-app)

cmake_minimum_required(VERSION 3.10)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-video-1.0)

include_directories(${GSTREAMER_INCLUDE_DIRS})

add_executable(jetson-gstreamer-app main.cpp)

target_link_libraries(jetson-gstreamer-app ${GSTREAMER_LIBRARIES})