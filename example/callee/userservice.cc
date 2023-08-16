#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
/*
UserService原来是一个本地服务，提供了一个进程内的本地方法：Local_login
*/
class UserService : public fixbug::UserServiceRpc
{ // 使用在rpc服务端（rpc服务的提供者）
public:
    bool Local_login(std::string name, std::string pwd)
    {
        std::cout << "doing local service :Login" << std::endl;
        std::cout << "name : " << name << "pwd : " << pwd << std::endl;
        return true;
    }
    bool Local_register(uint32_t id, std::string name, std::string pwd)
    {

        std::cout << "doing local service :Register" << std::endl;
        std::cout << "id : " << id << "name : " << name << "pwd : " << pwd << std::endl;
        return true;
    }
    // 重写基类UserServiceRpc的虚函数，下面这些方法是框架调用的：
    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        // 框架给业务上报请求参数LoginRequest，应用获取相应的数据做本地的业务；

        std::string name = request->name();
        std::string pwd = request->pwd();

        // 做本地业务；
        bool login_result = Local_login(name, pwd);

        // 把响应写入  包括错误码，错误消息，返回值
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);

        // 执行回调操作：
        done->Run();
    }
    void Register(::google::protobuf::RpcController *controller,
                  const ::fixbug::RegisterRequest *request,
                  ::fixbug::RegisterResponse *response,
                  ::google::protobuf::Closure *done)
    {
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();

        bool ret = Local_register(id,name,pwd);
        
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);
        done->Run();

    }
};

int main(int argc, char **argv)
{ // 调用框架的初始化操作：
    MprpcApplication::Init(argc, argv);

    // provider是一个rpc网络服务对象。把UserService对象发布到rpc节点上。
    RpcProvider provider;
    provider.NotifyService(new UserService());
    // 启动一个rpc服务发布节点：  Run以后，进程进入阻塞状态，等待远程的rpc调用请求；
    provider.Run();
    return 0;
}
