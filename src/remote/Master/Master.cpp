#include "stdafx.h"


/*
    - Прочитать из файла конфигурации адрес порта, к которому нужно подключиться - "port"
    - Подключиться к данному порту на прослушивание и обрабатывать комнады:
*/


static void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar data, int size);

// Мастер работает, пока run == true
static bool run = true;


int Master::Run()
{
    uint16 port = static_cast<uint16>(TheConfig.GetIntValue("port"));

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

    return 0;
}


static void HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar symbols, int number)
{
    static std::string buffer;

    buffer.append(symbols, (size_t)number); //-V201

    if (buffer.size() < 5)
    {
        return;
    }

    uint *sizeCommand = (uint *)&buffer[0]; //-V206

    if ((uint)(buffer.size() - sizeof(uint)) < *sizeCommand) //-V202
    {
        return;
    }

    std::vector<std::string> words;

    SU::SplitToWords(&buffer[sizeof(uint)], (int)*sizeCommand, words);

    if (words[0] == "get" && words.size() == 3)
    {
        if (words[1] == "address")                                                          // get address
        {
            pchar address = TheConfig.GetStringValue("address", words[2].c_str());
            if (address)
            {
                socket.Transmit(address);
            }
            else
            {
                LOGERROR("Invalid request : \"%s %s %s\"", words[0].c_str(), words[1].c_str(), words[2].c_str());
            }
        }
    }
    else if (words[0] == "close" && words.size() == 2 && words[1] == "connection")          // close connection
    {
        socket.sock.close();
    }
    else if (words[0] == "terminate")                                                       // terminate //-V2516
    {
        run = false;

        //            MasterServer master(gConfig);
        //
        //            master.Connnect("127.0.0.1", static_cast<uint16>(gConfig.GetIntValue("port")));
    }

    buffer.erase(0, sizeof(uint) + (size_t)*sizeCommand); //-V201
}
