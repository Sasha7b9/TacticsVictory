// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"


void Server::AppendHandler(pchar command, pFuncVV handler)
{
    handlers[command] = handler;
}


void Server::AppendServerInfo(const ServerInfo &info)
{
    infos[info.address] = info;
}


//static void SocketThread(AcceptorTCP::Socket socket, void (*onReceive)(AcceptorTCP::Socket &, pchar, int))
//{
//    while (socket.sock.is_open())
//    {
//        static const int MAX_RECEIVED = 512;
//
//        char received[MAX_RECEIVED];
//
//        ssize_t n = socket.sock.read(received, MAX_RECEIVED);
//
//        if (n <= 0)
//        {
//            LOGWRITEF("Close connection %s", socket.peer->to_string().c_str());
//            break;
//        }
//
//        onReceive(socket, received, static_cast<int>(n));
//    }
//}


void Server::Run()
{
    struct event_base *base;
//    struct evconnlistener *listener;
//    struct event *signal_event;

    struct sockaddr_in sin = { 0 };

#ifdef WIN32
    WSADATA wsa_data;
    WSAStartup(0x0201, &wsa_data);
#endif

    base = event_base_new();






    /*
    Prepare();

    uint16 port = static_cast<uint16>(TheConfig.GetInt("port"));

    AcceptorTCP acceptor;

    if (acceptor.Bind(port))
    {
        LOGWRITE("Wait connections ...");

        while (run)
        {
            AcceptorTCP::Socket socket;

            if (acceptor.Accept(socket))
            {
                std::thread thread(SocketThread, std::move(socket), HandlerReceivedSocket);
                thread.detach();
            }
            else
            {
                LOGERROR("Error accept");
            }
        }
    }
    */
}
