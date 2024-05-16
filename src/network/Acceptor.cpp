#include "Acceptor.h"
#include "Socket.h"
#include "Channel.h"

Acceptor::Acceptor(EventLoop *loop) {
    sock_ = std::make_unique<Socket>();
    InetAddress *addr = new InetAddress("127.0.0.1", 1234);
    sock_->Bind(addr);
    //这里就不调用SetNonBlocking了，因为Accoptor使用阻塞式IO比较好
    sock_->Listen();
    accept_channel_ = std::make_unique<Channel>(loop, sock_->GetFd());
    std::function<void()> cb = std::bind(&Acceptor::AcceptConnection, this);
    accept_channel_->SetReadCallback(cb);
    accept_channel_->EnableRead(); //一起UpdateChannel了，把新的fd，ev加入epoll事件表
    delete addr;
}

Acceptor::~Acceptor(){}

void Acceptor::AcceptConnection(){
    InetAddress *clnt_addr = new InetAddress();
    Socket *clnt_sock = new Socket(sock_->Accept(clnt_addr));//接收连接
    //这里采用new的方式让它在堆区分配,如果是栈区分配，可能会在函数结束的时候，进行对象析构，关闭fd，而在堆区，又没有释放它，就使得其一直
    //被打开和使用
    //printf("new clinet fd %d! ip: %s port: %d \n", clnt_sock->GetFd(), clnt_addr->GetIp(), clnt_addr->GetPort());
    clnt_sock->SetNonBlocking();//设置新连接为非阻塞式
    new_connection_callback_(clnt_sock->GetFd());
    delete clnt_addr;
}

void Acceptor::SetNewConnectionCallback(std::function<void(int)> const & _cb){
    new_connection_callback_ = std::move(_cb);
}