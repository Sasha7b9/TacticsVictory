// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


static void HandlerClose(AcceptorTCP::Socket &socket, std::vector<std::string> &words, void *cookie = nullptr);
static void HandlerGet(AcceptorTCP::Socket &socket, std::vector<std::string> &words, void *cookie = nullptr);
static void HandlerTerminate(AcceptorTCP::Socket &socket, std::vector<std::string> &words, void *cookie);


void Master::PrepareHandlers()
{

}


void Master::HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar symbols, int number)
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

    if (words[0] == "get")
    {
        HandlerGet(socket, words);
    }
    else if (words[0] == "close" && words.size() == 2 && words[1] == "connection")          // close connection
    {
        HandlerClose(socket, words);
    }
    else if (words[0] == "terminate")                                                       // terminate //-V2516
    {
        HandlerTerminate(socket, words, (void *)&run);
    }

    buffer.erase(0, sizeof(uint) + (size_t)*sizeCommand); //-V201
}


static void HandlerClose(AcceptorTCP::Socket &socket, std::vector<std::string> &words, void *)
{
    if (words.size() == 2 && words[1] == "connection")
    {
        socket.sock.close();
    }
}


static void HandlerGet(AcceptorTCP::Socket &socket, std::vector<std::string> &words, void *)
{
    if (words.size() == 3)
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
}


static void HandlerTerminate(AcceptorTCP::Socket &, std::vector<std::string> &, void *cookie)
{
    bool *run = (bool *)cookie;

    *run = false;

    //            MasterServer master(gConfig);
    //
    //            master.Connnect("127.0.0.1", static_cast<uint16>(gConfig.GetIntValue("port")));
}
