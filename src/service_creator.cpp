#include "service_creator.h"

std::string construct_service_file(std::vector<std::string> inquire_result) {
    // 构造服务文件
    std::string exec_path = inquire_result[0];
    std::string service_name = inquire_result[1];
    std::string service_description = inquire_result[2];

    std::string service_file;
    service_file += "[Unit]\n";
    service_file += "Description=" + service_description + "\n";
    service_file += "After=network.target\n";
    service_file += "\n";
    service_file += "[Service]\n";
    service_file += "Type=simple\n";
    service_file += "ExecStart=" + exec_path + "\n";
    service_file += "Restart=on-failure\n";
    service_file += "RestartSec=3\n";
    service_file += "User=root\n";
    service_file += "Group=root\n";
    service_file += "\n";
    service_file += "[Install]";
    service_file += "WantedBy=multi-user.target";
    
    return service_file;
}