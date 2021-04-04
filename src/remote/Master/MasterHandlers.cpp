// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


static void HandlerClose(AcceptorTCP::Socket &socket, const std::vector<std::string> &words);
static void HandlerGet(AcceptorTCP::Socket &socket, const std::vector<std::string> &words);
static void HandlerTerminate(AcceptorTCP::Socket &socket, const std::vector<std::string> &words);


typedef void (*Handler)(AcceptorTCP::Socket &, const std::vector<std::string> &);


static std::map<std::string, Handler> map;


void Master::PrepareHandlers()
{
    map["close"] = HandlerClose;
    map["get"] = HandlerGet;
    map["terminate"] = HandlerTerminate;
}


void Master::HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar symbols, int number)
{
    static std::string buffer;

    buffer.append(symbols, (size_t)number); //-V201

    if (buffer.size() < 5)
    {
        return;
    }

    uint *size_ñommand = (uint *)&buffer[0]; //-V206

    if ((uint)(buffer.size() - sizeof(uint)) < *size_ñommand)
    {
        return;
    }

    std::vector<std::string> words;

    SU::SplitToWords(&buffer[sizeof(uint)], (int)*size_ñommand, words);

    auto iter = map.find(words[0]);

    if (iter != map.end())
    {
        iter->second(socket, words);
    }

    buffer.erase(0, sizeof(uint) + (size_t)*size_ñommand); //-V201
}


static void HandlerClose(AcceptorTCP::Socket &socket, const std::vector<std::string> &words)
{
    if (words.size() == 2 && words[1] == "connection")
    {
        socket.sock.close();
    }
}


static void HandlerGet(AcceptorTCP::Socket &socket, const std::vector<std::string> &words)
{
    if (words.size() == 3)
    {
        if (words[1] == "address")                                                          // get address
        {
            pchar address = TheConfig.GetString("address", words[2].c_str());
            if (address)
            {
                socket.Transmit(address);
            }
            else
            {
                LOGERRORF("Invalid request : \"%s %s %s\"", words[0].c_str(), words[1].c_str(), words[2].c_str());
            }
        }
    }
}


static void HandlerTerminate(AcceptorTCP::Socket &, const std::vector<std::string> &)
{
    Master::Terminate();

    //            MasterServer master(gConfig);
    //
    //            master.Connnect("127.0.0.1", static_cast<uint16>(gConfig.GetIntValue("port")));
}
