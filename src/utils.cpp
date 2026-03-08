#include "utils.h"

bool is_root() {
    if (getuid() == 0) {
        return true;
    } else {
        return false;
    }
}

std::string Inquire_once(std::string question) {
    std::string result;
    std::cout << question << std::endl;
    std::cin >> result;
    return result;
}

std::vector<std::string> Inquire() {
    // 询问信息
    std::string exec_path = Inquire_once("请输入可执行文件位置：");
    std::string service_name = Inquire_once("请输入服务名称：");
    std::string service_description = Inquire_once("请输入服务描述：");

    // 构造vector并返回
    std::vector<std::string> result = {exec_path, service_name, service_description};
    return result;
}

bool write_file(std::string content, std::string path) {
    // 写入文件，第一个参数为待写入的文件内容，第二个参数为文件路径，如不存在则创建
    std::ofstream ofs;
    ofs.open(path, std::ios::out);
    if (ofs.is_open()) {
        ofs << content;
        ofs.close();
        return true;
    } else {
        return false;
    }
}