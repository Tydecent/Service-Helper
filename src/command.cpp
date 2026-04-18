#include "command.h"

#include "utils.h"
#include "service_creator.h"

namespace ServiceHelper_command {
    int add() {
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

        effective_service(std::string service_name);

        return 0;
    }

    int version() {
        // 打印版本信息
        std::cout << "Service Helper\n"
                  << "Version Info\n"
                  << "--------------\n"
                  << "Git Tag: " << GIT_TAG << "\n"
                  << "Git Hash: " << GIT_HASH << "\n"
                  << "Build Time: " << BUILD_TIMESTAMP << std::endl;
        
        return 0;
    }

    int list() {
        // 列出所有自定义服务
        fs::path service_path("/etc/systemd/system/");
        for (const auto& entry : fs::directory_iterator(service_path)) {
            if (entry.path().extension() == ".service") {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }

        return 0;
    }

    int remove() {
        // 询问服务名称
        std::string service_name = Inquire_once("请输入要删除的服务名称：");

        // 构造服务文件路径
        std::string service_file_path = "/etc/systemd/system/" + service_name + ".service";

        // 删除服务文件
        int remove_return_code = system_call("rm " + service_file_path); 
        
        if (remove_return_code != 0) {
            std::cout << "删除失败，system_call_return_code：" << remove_return_code << std::endl;
            return remove_return_code;
        }

        return 0;
    }
}