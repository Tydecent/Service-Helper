#include <iostream>
#include <string>
#include <cxxopts.hpp>

#include "utils.h"
#include "service_creator.h"


int main(int argc, char *argv[]) {
    // 处理命令行参数
    try {
        cxxopts::Options options("Service Helper", "Linux服务创建应用——用于快捷创建服务");

        options.add_options()
            ("h,help", "帮助信息")
            ("v,version", "版本信息");

    } catch (const cxxopts::exceptions::exception& e) {
        std::cout << "命令行参数错误：" << e.what() << std::endl;
        return -1;
    }

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result.count("version")) {
        std::cout << "版本信息" << std::endl;
        return 0;
    }

    // 检查root权限
    if (is_root() == false) {
        std::cout << "添加服务需要root权限，请以root或sudo权限运行本程序。" << std::endl;
        return -1;
    }

    // 询问信息
    std::vector<std::string> inquire_result = Inquire();

    // 处理相对路径
    inquire_result[0] = get_absolute_path(inquire_result[0]);

    // 检查可执行文件
    check_exec(inquire_result[0]);

    // 构造服务文件
    std::string service_file = construct_service_file(inquire_result);

    // 写入服务文件
    if (write_file(service_file, "/etc/systemd/system/" + inquire_result[1] + ".service")) {
        std::cout << "写入成功。" << std::endl;
    } else {
        std::cout << "文件写入失败。" << std::endl;
        return -2;
    }

    // 使服务生效
    effective_service(inquire_result[1] + ".service");

    return 0;
}