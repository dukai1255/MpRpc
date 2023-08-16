#pragma once // 防止头文件被重复包含
#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include"mprpccontroller.h"
// mprpc框架的基础类,负责框架的一些初始化操作；
class MprpcApplication
{

public:
    static void Init(int argc, char **grgv);
    static MprpcApplication &getInstance();
    static MprpcConfig& getConfig();
private:
    static MprpcConfig m_config;
    MprpcApplication() {}
    MprpcApplication(const MprpcApplication &) = delete;
    MprpcApplication(MprpcApplication &&) = delete;
};