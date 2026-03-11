# Service Helper


## 概述
Service Helper是一个帮助开发者~~管理~~添加Linux系统服务的工具。

相信大家在写Linux程序的时候，经常需要将你自己编写的程序作为服务安装，以便于后台运行。但是，安装服务的过程并不简单，尤其是在复杂的系统环境下。Service Helper就是为了解决这个问题而生的。

Service Helper可以帮助你快速安装服务。它还可以帮助你自动生成服务配置文件，并将服务添加到系统服务管理器中。

## 功能
- 傻瓜式添加：只需按照引导操作，即可快速添加服务。
- 自动生成服务配置文件：Service Helper可以自动生成服务配置文件，并将其添加到系统服务目录中。

## 项目结构
```
Service-Helper
├── src
│   ├── main.cpp            # 主函数
│   ├── service_creator.cpp # 服务配置文件生成器
│   ├── service_creator.h   
│   ├── utils.cpp           # 工具模块
│   └── utils.h             
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## 法律与许可
本开源项目遵循MIT许可证，这意味着你可以自由地使用、修改、分发本项目。唯一的要求是保留版权标识。
许可全文详见[LICENSE](LICENSE)文件。