#include <iostream>
#include <string>

#include "utils.h"
#include "service_creator.h"


int main(int argc, char *argv[]) {
    // 检查root权限
    if (is_root() == false) {
        std::cout << "添加服务需要root权限，请以root或sudo权限运行本程序。" << std::endl;
        return -1;
    }

    // 询问信息
    std::vector<std::string> inquire_result = Inquire();

    // 为可执行文件添加可执行权限
    if (add_executable_to_path(inquire_result[0]) == false) {
        std::cout << "添加可执行权限失败。" << std::endl;
        return -3;
    }

    // 构造服务文件
    std::string service_file = construct_service_file(inquire_result);

    // 写入服务文件
    if (write_file(service_file, "/etc/systemd/system/" + inquire_result[1] + ".service")) {
        std::cout << "写入成功。" << std::endl;
    } else {
        std::cout << "文件写入失败。" << std::endl;
        return -2;
    }

    return 0;
}