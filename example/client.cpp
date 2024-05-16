#include <Connection.h>
#include <Socket.h>
#include <iostream>

int main(){
    Socket *sock = new Socket();  //创建一个new socket_fd
    sock->Connect("127.0.0.1", 1234);

    Connection *conn = new Connection(sock->GetFd(), nullptr);

    while(true){
        conn->GetlineSendBuffer();
        conn->Write();
        if(conn->GetState() == Connection::State::Closed){
            conn->Close();
            break;
        }
        conn->Read();
        std::cout << "Message from server: " << conn->ReadBuffer() << std::endl;
    }
    delete conn;
    delete sock;
    return 0;
}
//总结来说就是socket类实现的是socket模块的封装，包括初始socket_fd的构建，传入的InetAddress(IP+Port信息)
//以及封装了绑定和监听的过程，客户端发起连接的过程以及接收连接的过程，以及设置阻塞或者非阻塞的过程
//Connection类封装了数据收发和业务处理的过程