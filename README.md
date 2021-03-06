# cpp-server

This is a Game Server develop by c++ 17, implement any basic module, and you can extend you module easy.

The structure is like micrro service, all the service is access by api service. Dedicate server is manage by api service, and all the api service is manage by master server, you can easily extend the server when player is more.

Important: the current version is in developing, the api will be changed frequently, you may use this library when it release a stable version like v1.0.0.

## file structure

- src/rdm --- remote dream library

## file structure

service server 作为服务入口，通过 service server 访问外部服务。

manager sercer 用于管理所有服务器，包括关闭，启动，查看负载等。

网络连接：

- service server 理论上与所有其他 service server 连接，可以根据内部和外部服务，做区分，比如跟客户端连接的 sercie 和跟 db 连接的 server 之间不应该有连接；
- 其他类型的服务器只跟对应类型的 service server 连接；
- manager server 可以配置一台或多台，跟所有 service server 连接；
    
---

```
| --- manager_server (one or n)
|
| --- api_service(n)     --- chat_server A
|                           --- chat_server B
|                           --- chat_server ... (n)
|                  
| --- api_service(n)     --- login_server A
|                           --- login_server B
|                           --- login_server ... (n)
|               
| --- api_service(n)     --- game_server A
|                           --- game_server B
|                           --- game_server ... (n)
|
| --- api_service(n)     --- db_server A
|                           --- db_server B
|                           --- db_server ... (n)
|
| --- api_service(n)     --- client A
|                           --- client B
|                           --- client ... (n)
|
| --- service ......          
```

## ubuntu 20.04

```shell script
sudo apt update
sudo apt install libbenchmark-dev

sudo apt install libmysqlcppconn-dev
sudo apt install libspdlog-dev
sudo apt install libprotobuf-dev
sudo apt  install protobuf-compiler
sudo apt install libjsoncpp-dev
sudo apt install libtinyxml2-dev
sudo apt install libinih-dev
sudo apt install libyaml-cpp-dev
sudo apt install nlohmann-json3-dev

# 手动安装 boost
# sudo apt install libboost-all-dev
# or manual instal needed library
# sudo apt install libboost_filesystem-dev
```

### mongo driver cxx

```shell script
tar xzvf mongo-c-driver-1.15.0.tar.gz
cd mongo-c-driver-1.15.0
cmake . -DBUILD_VERSION=1.15.0
make -j 8
sudo make install

tar xzvf mongo-cxx-driver-r3.5.0.tar.gz
cd mongo-cxx-driver-r3.5.0/build
cmake ..                                            \
    -DCMAKE_BUILD_TYPE=Release                      \
    -DBUILD_SHARED_AND_STATIC_LIBS=ON               \
    -DCMAKE_PREFIX_PATH=/usr/local/lib/             \
    -DCMAKE_INSTALL_PREFIX=/usr/local               \
    -DBUILD_VERSION=3.5.0
sudo make
sudo make install
```

### Boost 1.73.0 安装

动态链接，依赖 boost 的项目链接 .so 文件，注意可执行文件发布以后，要把依赖的动态库拷贝到系统目录，不然程序找不到启动报错。

```shell script
./bootstrap.sh

./b2 stage \
  --with-random \
  --with-system \
  --with-filesystem \
  --with-thread \
  --with-date_time \
  --with-regex \
  --with-serialization \
  --toolset=gcc \
  address-model=64 \
  architecture=x86 \
  threading=multi \
  link=shared \
  runtime-link=shared 
 
sudo cp -rf ./boost /usr/local/include      && \
sudo cp ./stage/lib/*.a /usr/local/lib      && \
sudo cp ./stage/lib/*.so /usr/local/lib     && \
sudo ldconfig
```

### Boost 1.73.0 cmake 配置

```cmake
set(Boost_VERSION 1.73.0)
set(Boost_VERSION 107300)
set(Boost_DEBUG ON)

find_package(benchmark 1.5.0 REQUIRED)
find_package(Boost 1.73.0 REQUIRED COMPONENTS system filesystem)
```

### Boost 1.73.0 cmake 警告忽略

```cmake
# boost 版本太新会有警告，修改文件 /usr/share/cmake-3.16/Modules/FindBoost.cmake，版本号改小，或者删除警告。
if(NOT Boost_VERSION_STRING VERSION_LESS 1.74.0)
    message(WARNING "New Boost version may have incorrect or missing dependencies and imported targets")
endif()
```

### mongo-cxx-driver

```shell script
tar xzvf mongo-c-driver-1.16.2.tar.gz mongo-c-driver-1.16.2
cd mongo-c-driver-1.16.2
cmake . -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF
sudo make install

tar xzvf mongo-cxx-driver-r3.5.0.tar.gz 
cd mongo-cxx-driver-r3.5.0/build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local

sudo cp -r /usr/local/include/mongocxx/v_noabi/mongocxx/ /usr/local/include/
sudo cp -r /usr/local/include/bsoncxx/v_noabi/bsoncxx/ /usr/local/include/

sudo cp -r /opt/mongo-cxx-driver/include//mongocxx/v_noabi/mongocxx/ /usr/local/include/
sudo cp -r /opt/mongo-cxx-driver/include//bsoncxx/v_noabi/bsoncxx/ /usr/local/include/

```

### 第三方开源库地址

```
https://github.com/benhoyt/inih
https://github.com/leethomason/tinyxml2
https://github.com/nlohmann/json
https://github.com/gabime/spdlog
https://github.com/github/gitignore
```

### 常用命令行

catch2 指定用例 `./test <test-name>`

参考：https://github.com/catchorg/Catch2/blob/master/docs/command-line.md#specifying-which-tests-to-run

benchmark 指定用例 `./benchmark --benchmark_filter=<regex>`

参考：https://github.com/google/benchmark

### yaml 格式转 json

https://onlineyamltools.com/convert-yaml-to-json

### linux 检查端口占用

```shell script
netstat -tunlp | grep [port]
kill -9 [pid]
```

### vmware 使用

```shell script
# 收缩磁盘
vmware-toolbox-cmd disk shrink /

# 克隆后获取新 ip
netplan apply
reboot
```

### clion 使用

cmake 文件中的 Target 没有自动加入到 Run/Debug Configurations... 里面，尝试删除 .idea 目录下的 workspace.xml，重新启动 clion 加载 cmake 工程

clion on windows with msvc 多线程编译，下载 JOM 解压后，路径添加到 PATH 环境变量，设置 Preferences | Build, Execution, Deployment | CMake | Cmake options
```
-G "NMake Makefiles JOM" -DCMAKE_TOOLCHAIN_FILE=D:\usr\local\vcpkg\scripts\buildsystems\vcpkg.cmake
```

### mongodb 配置

```
# https://docs.mongodb.com/manual/reference/configuration-options/#storage.wiredTiger.engineConfig.cacheSizeGB
# Where and how to store data.
storage:
  dbPath: C:\usr\MongoDB\data
  journal:
    enabled: true
  wiredTiger:
    engineConfig:
      cacheSizeGB: 0.25 # 配置内存上限，机器配置低，这个值设置小一点
```

### cmake 命令

```shell
cmake.exe -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE=c:\root\opt\vcpkg\scripts\buildsystems\vcpkg.cmake ..
cmake.exe -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE=c:\root\opt\vcpkg\scripts\buildsystems\vcpkg.cmake ..

cmake --build . --target [target-name] --config Debug
cmake --build . --target [target-name] --config Release
```


### TODO

- [ ] google c++ 基础库接入 https://abseil.io/docs/cpp/quickstart-cmake.html；
- [ ] yaml-cpp 库用 apt install 或者 github 上面源代码安装，获取 yaml 文件的数据一直崩溃，先将源代码放到项目
        的 third_party 目录中，创建 cmake 文件编译，然后其他项目原来它，测试使用正常，之后再排查哪里出问题；
- [ ] add direct connect support between all type servers, when machine performanc is low, the more service will consume more resource.
- [ ] connection id 回收机制