#include "service_creator.h"

std::string construct_service_file(std::vector<std::string> inquire_result) {
    // 构造服务文件
    std::string exec_path = inquire_result[0];
    std::string service_name = inquire_result[1];
    std::string service_description = inquire_result[2];

    std::string service_file = "[Unit]\n" +
                               "Description=" + service_description + "\n"
                               "After=network.target\n"
                               "\n"
                               "[Service]\n"
                               "Type=simple\n"
                               "ExecStart=" + exec_path + "\n"
                               "Restart=on-failure\n"
                               "RestartSec=3\n"
                               "User=root\n"
                               "Group=root\n"
                               "\n"
                               "[Install]"
                               "WantedBy=multi-user.target";

    return service_file;
}