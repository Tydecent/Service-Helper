#include <iostream>
#include <string>
#include <cxxopts.hpp>

#include "utils.h"


int main(int argc, char *argv[]) {
    // 处理命令行参数

    cxxopts::Options options("Service Helper", "Linux服务创建应用——用于快捷创建服务");

    options.add_options()
        ("h,help", "帮助信息")
        ("v,version", "版本信息")
        ("a,add", "创建服务");
   

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result.count("version")) {
        print_version_info();
        return 0;
    }

    if (result.count("add")) {
        return add_service();
    }

    std::cout << options.help();
    return 0;
}