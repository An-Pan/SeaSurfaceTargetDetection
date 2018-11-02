cmake_minimum_required(VERSION 3.5.1)
project(Verify)
find_package( OpenCV 3.3.0 REQUIRED )
find_package( Boost 1.58.0 COMPONENTS filesystem )

#include_directories(${PCL_INCLUDE_DIRS})
include_directories( ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "$ENV{CFLAGS} -O3 -Wall")


file(GLOB SOURCES "./*.cpp" "./*.h")


add_executable(Verify ${SOURCES})
target_link_libraries(Verify ${Boost_LIBRARIES} ${OpenCV_LIBS} ${PCL_LIBRARIES} -lboost_system -lboost_regex -lpthread)
