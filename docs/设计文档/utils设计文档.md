# `utils.cpp/.h`设计文档

## 目录
- [`utils.cpp/.h`设计文档](#utilscpph设计文档)
  - [目录](#目录)
  - [函数设计](#函数设计)
    - [`is_root()`](#is_root)
    - [`Inquire_once(question)`](#inquire_oncequestion)
    - [`Inquire()`](#inquire)
  
## 函数设计

### `is_root()`
用于判断进程是否以root权限运行（由于添加服务需要root权限）

若进程以root权限运行，则返回`true`，否则返回`false`.

通过`getuid()`获取进程PID，若PID为0，则说明进程以root权限运行。

### `Inquire_once(question)`
用于询问用户，并返回用户输入的内容。

### `Inquire()`
用于串联多个`Inquire_once()`函数，询问用户多个信息，并返回一个`std::vector<std::string>`。