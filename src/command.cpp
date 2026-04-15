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

        // 使服务生效
        effective_service(inquire_result[1] + ".service");

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
}