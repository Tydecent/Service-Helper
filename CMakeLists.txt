cmake_minimum_required(VERSION 3.10)

project(service-helper)

add_executable(service-helper 

               src/main.cpp 
               src/utils.cpp 
               src/service_creator.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 使用cxxopts处理命令行。
find_package(cxxopts CONFIG REQUIRED)
target_link_libraries(service-helper PRIVATE cxxopts::cxxopts)

# 获取构建时间（配置阶段执行一次）
string(TIMESTAMP BUILD_TIMESTAMP "%Y-%m-%d %H:%M:%S")

# 获取 Git 哈希（配置阶段执行一次）
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

# 传递给所有目标
add_definitions(-DBUILD_TIMESTAMP="${BUILD_TIMESTAMP}")
add_definitions(-DGIT_HASH="${GIT_HASH}")