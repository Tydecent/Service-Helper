#include "utils.h"

bool is_root() {
    // 判断是否为root权限
    if (getuid() == 0) {
        return true;
    } else {
        return false;
    }
}

std::string Inquire_once(std::string question) {
    // 询问一次信息
    std::string result;
    std::cout << question;
    std::cin >> result;
    return result;
}

std::vector<std::string> Inquire() {
    // 询问信息
    std::string exec_path = Inquire_once("请输入可执行文件位置：");

    // 检查文件是否符合要求
    int check_exec_exits = check_exec(exec_path);

    if (check_exec_exits != 0) {
        exit(check_exec_exits);
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

int check_exec(std::string exec_path) {
    // 对可执行文件进行系列检查
    if (check_file_exists(exec_path) == false) {
        std::cout << "文件不存在。Error_101" << std::endl;
        exit(101);
    }

    bool is_shebang         = check_shebang(exec_path);
    bool is_ELF             = check_ELF_magicnum(exec_path);
    std::string file_type   = get_file_type(exec_path);

    if (is_shebang == true || is_ELF == true) {
        goto add_executable_to_path_part;
    }

    if (file_type != "unknown") {
        bool user_choice_for_add_shebang = Inquire_add_shebang(file_type);
        if (user_choice_for_add_shebang == true) {
            if (add_shebang(exec_path, file_type) == false) {
                std::cout << "添加shebang失败。Error_105" << std::endl;
                exit(105);
            }

        } else {
            std::cout << "用户拒绝添加shebang。Error_102" << std::endl;
            exit(102);
        }
    } else {
        exit(104);
    }


add_executable_to_path_part:
    if (add_executable_to_path(exec_path) == false) {
        std::cout << "添加可执行权限失败。Error_103" << std::endl;
        exit(103);
    }

    return 0;
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
    // 打开文件
    std::ifstream file(exec_path);

    // 读取第一行
    std::string first_line;
    if (std::getline(file, first_line).fail()) {
        return false;
    }

    // 检查前两个字符为#!
    if ((first_line.length() >= 2 && first_line[0] == '#' && first_line[1] == '!') == false) {
        return false;
    }

    // 读取shebang
    std::string shebang = first_line.substr(2);

    // 求第一个单词
    std::string jieshiqi = get_string_first_word(shebang);
    if (check_shebang_kezhixing(jieshiqi) == false) {
        return false;
    }

    return true;
}

bool check_ELF_magicnum(std::string exec_path) {
    // 检查文件头是否为ELF格式，通过判断文件前4字节是否为魔术字:0x7F 0x45 0x4C 0x46
    std::ifstream file(exec_path);

    char buffer[4];

    file.read(buffer, 4);

    if (file.gcount() == 4) {
        if (buffer[0] == '\x7f' && buffer[1] == 'E' && buffer[2] == 'L' && buffer[3] == 'F') {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

std::string get_file_ext(std::string exec_path) {
    // 获取文件扩展名
    fs::path p = exec_path;
    return p.extension().string();
}

std::string get_file_type(std::string exec_path) {
    // 判断文件类型
    std::string file_ext = get_file_ext(exec_path);
    if (file_ext == ".sh") {
        return "shell";
    } else if (file_ext == ".py") {
        return "python";
    } else if (file_ext == ".js") {
        return "JavaScript";
    } else {
        return "unknown";
    }
}

bool Inquire_add_shebang(std::string file_type) {
    // 询问是否添加shebang
    std::string choice = Inquire_once("检测到文件类型为" + file_type + "但未检测到shebang，是否添加shebang? (Y/n):");
    if (choice == "Y" || choice == "y" || choice == "") {
        return true;
    } else if (choice == "N" || choice == "n") {
        return false;
    } else {
        return Inquire_add_shebang(file_type);
    }
}

bool add_shebang(std::string exec_path, std::string file_type) {
    // 为脚本文件添加shebang

    // 构造shebang
    std::string shebang;
    if (file_type == "shell") {
        shebang = "#!/bin/bash";
    } else if (file_type == "python") {
        shebang = "#!/usr/bin/env python";
    } else if (file_type == "JavaScript") {
        shebang = "#!/usr/bin/env node";
    }
    shebang = shebang + "\n";

    // 读取文件的全部内容
    std::ifstream ifs;
    ifs.open(exec_path);

    // 判断ifstream是否成功打开文件
    if (!ifs.is_open()) {
        std::cout << "文件打开失败。" << std::endl;
        return false;
    }

    std::stringstream original_file_buffer;
    original_file_buffer << ifs.rdbuf();
    std::string original_file = original_file_buffer.str();
    ifs.close();

    // 写入shebang+文件内容
    std::ofstream ofs;
    ofs.open(exec_path, std::ios::out);

    // 判断ofstream是否成功打开文件
    if (!ofs.is_open()) {
        std::cout << "文件写入失败。" << std::endl;
        return false;
    }

    ofs << shebang << original_file;
    ofs.close();

    // 保险起见，再检查一遍shebang
    return check_shebang(exec_path);
}

void effective_service(std::string service_name) {
    // 使服务生效
    system_call("systemctl enable " + service_name);
    system_call("systemctl start " + service_name);
}

std::string get_absolute_path(std::string path) {
    // 获取绝对路径
    return fs::canonical(path).string();
}

std::string get_string_first_word(std::string str) {
    // 获取字符串的首个单词
    int len = str.length();
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            return str.substr(0, i);
        }
    }
    return str;
}

bool check_shebang_kezhixing(std::string jieishiqi) {
    // 检查shebang的解释器是否存在并可执行
    if (access(jieshiqi.c_str(), X_OK) != 0) {
        return false;
    }
    return true;
}