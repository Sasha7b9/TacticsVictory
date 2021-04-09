// 2021/04/09 14:45:08 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"
#include "Network/Other/SocketsTCP_.h"


void Server::AppendHandler(pchar command, pFuncVV handler)
{
    handlers[command] = handler;
}


void Server::AppendServerInfo(const ServerInfo &info)
{
    clients[info.address] = info;
}


void Server::Run()
{
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
                socket.Run(HandlerReceivedSocket);
            }
            else
            {
                LOGERROR("Error accept");
            }
        }
    }

}
