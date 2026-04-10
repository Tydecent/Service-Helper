#!/bin/bash
set -e
sudo apt update

# 安装 cxxopts 库
sudo apt install libcxxopts-dev

mkdir -p build
cd build
cmake ..
make