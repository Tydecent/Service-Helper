#include <cxxopts.hpp>

#include "utils.h"
#include "command.h"


int main(int argc, char *argv[]) {
    // 处理命令行参数

    cxxopts::Options options("service-helper", "Linux服务创建应用——用于快捷创建服务");

    options.add_options()
        ("h,help",      "帮助信息")
        ("v,version",   "版本信息")
        ("a,add",       "创建自定义服务")
        ("l,list",      "列出所有自定义服务")
        ("r,remove",    "删除自定义服务");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result.count("version")) {
        return ServiceHelper_command::version();
    }

    if (result.count("list")) {
        return ServiceHelper_command::list();
    }
    
    // 检查root权限
    check_root();

    if (result.count("add")) {
        return ServiceHelper_command::add();
    }

    if (result.count("remove")) {
        return ServiceHelper_command::remove();
    }

    std::cout << options.help();
    return 0;
}