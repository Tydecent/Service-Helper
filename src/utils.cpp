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
    std::cout << question;
    std::cin >> result;
    return result;
}

std::vector<std::string> Inquire() {
again:

    // 询问信息
    std::string exec_path = Inquire_once("请输入可执行文件位置：");

    // 检查文件是否存在
    if (check_exec(exec_path) ==  false) {
        std::cout << "文件不存在，请重新输入！\n";
        goto again;
    }

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

int system_call(std::string command) {
    // 执行系统命令，返回命令执行结果
    return std::system(command.c_str());
}

bool add_executable_to_path(std::string exec_path) {
    // 为用户指定的运行程序添加可执行权限，使用chmod命令
    std::string chmod_command = "chmod +x " + exec_path;
    return system_call(chmod_command) == 0;
}

bool check_file_exists(std::string exec_path) {
    // 检查文件是否存在
    std::ifstream ifs(exec_path);
    return ifs.is_open();
}

bool check_shebang(std::string exec_path) {
    // 检查可执行文件的shebang，返回true表示shebang存在且正确
    std::ifstream file(exec_path);

    char buffer[2];

    file.read(buffer, 2);

    if (file.gcount() == 2) {
        if (buffer[0] == '#' && buffer[1] == '!') {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

}


int check_exec(std::string exec_path) {
    // 对可执行文件进行系列检查
    if (check_file_exists(exec_path) == false) {
        std::cout << "文件不存在。Error_101" << std::endl;
        exit(-101);
    }

    if (check_shebang(exec_path) == false) {
        std::cout << "文件shebang错误。Error_102" << std::endl;
        exit(-102);
    }

    if (add_executable_to_path(exec_path) == false) {
        std::cout << "添加可执行权限失败。Error_103" << std::endl;
        exit(-103);
    }

    return 0;
}