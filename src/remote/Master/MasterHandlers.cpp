// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


static void HandlerClose();
static void HandlerGet();
static void HandlerPing();
static void HandlerTerminate();


typedef void (*Handler)();


static std::map<std::string, Handler> map;


static AcceptorTCP::Socket *sock = nullptr;
static std::vector<std::string> *words = nullptr;


void Master::PrepareHandlers()
{
    map["close"] = HandlerClose;
    map["get"] = HandlerGet;
    map["ping"] = HandlerPing;
    map["terminate"] = HandlerTerminate;
}


void Master::HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar symbols, int number)
{
    sock = &socket;

    static std::string buffer;

    buffer.append(symbols, (size_t)number);

    if (buffer.size() < 5)
    {
        return;
    }

    uint *size_ñommand = (uint *)&buffer[0];

    if ((uint)(buffer.size() - sizeof(uint)) < *size_ñommand)
    {
        return;
    }

    std::vector<std::string> _words;

    SU::SplitToWords(&buffer[sizeof(uint)], (int)*size_ñommand, _words);

    words = &_words;

    auto iter = map.find(_words[0]);

    if (iter != map.end())
    {
        iter->second();
    }

    buffer.erase(0, sizeof(uint) + (size_t)*size_ñommand);
}


static void HandlerClose()
{
    if (words->size() == 2 && (*words)[1] == "connection")
    {
        sock->sock.close();
    }
}


static void HandlerGet()
{
    if (words->size() == 3)
    {
        if ((*words)[1] == "address")                                                          // get address
        {
            pchar address = TheConfig.GetString("address", (*words)[2].c_str());
            if (address)
            {
                sock->Transmit(address);
            }
            else
            {
                LOGERRORF("Invalid request : \"%s %s %s\"",
                    (*words)[0].c_str(), (*words)[1].c_str(), (*words)[2].c_str());
            }
        }
    }
}


static void HandlerPing()
{
    if (words->size() == 2)
    {
        sock->Transmit(std::string("ping ") + (*words)[1]);
    }
}


static void HandlerTerminate()
{
    Master::Terminate();

    //            MasterServer master(gConfig);
    //
    //            master.Connnect("127.0.0.1", static_cast<uint16>(gConfig.GetIntValue("port")));
}
