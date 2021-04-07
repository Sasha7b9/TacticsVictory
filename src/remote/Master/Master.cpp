// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


/*
    - Прочитать из файла конфигурации адрес порта, к которому нужно подключиться - "port"
    - Подключиться к данному порту на прослушивание и обрабатывать комнады:
*/


bool Master::run = true;

std::map<std::string, ServerInfo> Master::servers;


int Master::Run()
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
                servers[socket.sock.address().to_string()] = ServerInfo();

                socket.Run(HandlerReceivedSocket);
            }
            else
            {
                LOGERROR("Error accept");
            }
        }
    }

    return 0;
}


void Master::Terminate()
{
    run = false;
}
