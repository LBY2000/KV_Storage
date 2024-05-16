# KV_Storage
##### 项目简介

本项目是仿照陈硕老师的Muduo网络库实现的KV存储引擎。

本项目基于Reactor模式实现了网络I/O库，采用epoll模型实现网络I/O多路复用。内部采用跳表，自适应基数树，以及可扩展Hash等结构实现了KV存储引擎，支持数据插入，删除，查询和范围查询。

自适应基数树的实现和可扩展Hash结构复用了之前的工作：[LBY2000/Hybird_Search_Index: this is a temp repository for my thesis's design and I will keep updating (github.com)](https://github.com/LBY2000/Hybird_Search_Index)

##### 项目特点

* 底层使用Epoll边沿触发的IO多路复用，结合非阻塞I/O实现主从Reactor模型

- 采用 one loop per thread 线程模型，封装线程池避免线程频繁创建销毁的开销
- 遵循RAII思想，使用智能指针管理内存，减少内存泄漏
- 提供多种索引结构以实现灵活的存储引擎选择

##### 配置ART和Extendible_hash的动态库

```c++
$ cd My_CCEH_DRAM
$ g++ -fPIC -shared -o libexhash.so Extendible_Hash.cpp
$ sudo cp libexhash.so /usr/lib
$ cd ..
$ cd ARTree
$ g++ -fPIC -shared -o libartree.so art.cpp
$ sudo cp libartree.so /usr/lib
```

也可以直接运行配置脚本，但是注意脚本的运行路径

`````
$ bash ./config_index_library.sh
`````

其后在编译文件中应当添加相应动态库的链接，即 -lartree 以及 -lexhash；为了使用跳表以外的索引结构，应当修改src/storege中的SkipListwork.cpp函数，并添加相应头文件

##### 项目构建

`````
mkdir build && cd build
cmake ..
make
`````

##### 项目运行

服务端执行：

`````
cd ./example
./KVServer
set asd 1234
`````

客户端执行：

`````
cd ./example
./Client
get asd
`````

如果想要修改服务器的IP和端口，应该修改src/network/Acceptor.cpp中的IP+Port：
https://github.com/LBY2000/KV_Storage/blob/73397b339ad2bfd3597b7fb1af88328e74a96845/src/network/Acceptor.cpp#L20-L22
以及example/client.cpp中的IP+Port:
https://github.com/LBY2000/KV_Storage/blob/2c1814321436266f7d942840660b70644e895fe6/example/client.cpp#L5-L7
