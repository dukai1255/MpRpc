#pragma once
#include <semaphore.h>
#include <zookeeper/zookeeper.h>
#include <string>

//封装的ZK客户端类：
class ZkClient
{

public:
    ZkClient();
    ~ZkClient();
    //zkclient启动连接ZKServer
    void Start();
    //在ZKserver上根据指定的path创建znode节点；
    void Create(const char *path, const char *data, int datalen, int state = 0);
    //根据参数指定的znode节点的路径，获取znode节点的值；
    std::string GetData(const char *path);

private:
    zhandle_t *m_zhandle;
};