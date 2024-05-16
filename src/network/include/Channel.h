#pragma once
#include <functional>
#include <cstdint>
class Socket;
class EventLoop;
class Channel   //Channel类的作用就是封装网络库，让代码风格更加简洁
//通过Channel类，原本需要在socket类里处理的事情变得简单
{
    public:
     Channel(EventLoop *_loop, int _fd);
     ~Channel();

     void HandleEvent();  //本质上channel类封装的还是对epoll_wiat之后的事件的处理
     void EnableRead();

     int GetFd();
     uint32_t GetListenEvents();
     uint32_t GetReadyEvents();
     bool GetInEpoll();
     void SetInEpoll(bool _in = true);
     void UseET();
     void disableAll(); 
      bool isWriting();

     void SetReadyEvents(uint32_t);
     void SetReadCallback(std::function<void()>);
     void SetCloseCallback(std::function<void()>);
     void Delete();

    private:
     EventLoop *loop_;
     int fd_;
     uint32_t listen_events_;
     uint32_t ready_events_;
     bool in_epoll_;
     std::function<void()> read_callback_;
     std::function<void()> write_callback_;
     std::function<void()> close_callback_;
};