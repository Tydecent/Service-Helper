cmake_minimum_required(VERSION 3.10)

project(service-helper)

add_executable(service-helper 

               src/main.cpp 
               src/utils.cpp 
               src/service_creator.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 使用cxxopts处理命令行。
include(FetchContent)
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts
  GIT_TAG        v3.3.1
)
FetchContent_MakeAvailable(cxxopts)
target_link_libraries(service-helper PRIVATE cxxopts)