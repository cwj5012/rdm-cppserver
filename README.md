rdm (remote dream library)

## structure

- src/rdm --- remote dream library

## ubuntu 20.04

```shell
$ sudo apt update
$ sudo apt install libbenchmark-dev
$ sudo apt install libboost-all-dev
$ sudo apt install libmysqlcppconn-dev
$ sudo apt install libspdlog-dev
$ sudo apt install libprotobuf-dev
$ sudo apt install libjsoncpp-dev
$ sudo apt install libtinyxml2-dev
$ sudo apt install libinih-dev
$ sudo apt install nlohmann-json3-dev

$ sudo apt install apt-file
```

### Boost 1.73.0 安装

```
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
  link=static \
  runtime-link=shared 
 
sudo cp -rf ./boost /usr/local/include
sudo cp ./stage/lib/*.a /usr/local/lib
```

### Boost 1.73.0 cmake 配置

```
set(Boost_VERSION 1.73.0)
set(Boost_VERSION 107300)
set(Boost_DEBUG ON)

find_package(benchmark 1.5.0 REQUIRED)
find_package(Boost 1.73.0 REQUIRED COMPONENTS system filesystem)
```

### Boost 1.73.0 cmake 警告忽略

```
boost 版本太新会有警告，修改文件 /usr/share/cmake-3.16/Modules/FindBoost.cmake，版本号改小，或者删除警告。

if(NOT Boost_VERSION_STRING VERSION_LESS 1.74.0)
    message(WARNING "New Boost version may have incorrect or missing dependencies and imported targets")
endif()
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

### TODO

- [ ] google c++ 基础库接入 https://abseil.io/docs/cpp/quickstart-cmake.html