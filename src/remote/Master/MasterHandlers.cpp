// 2021/03/31 22:30:19 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "Network/Other/NetworkTypes_.h"
#include "Network/Other/Server_.h"
#include "Network/Other/SocketsTCP_.h"
#include "Utils/StringUtils_.h"


static void HandlerClose();
static void HandlerGet();
static void HandlerPing();
extern void HandlerTerminate();


static AcceptorTCP::Socket *sock = nullptr;             // Используется в обработчиках
static std::vector<std::string> *words = nullptr;       // Используется в обработчиках


std::map<std::string, pFuncVV> Server::map;
std::map<std::string, ServerInfo> Server::livingrooms;


void Server::Prepare()
{
    AppendHandler("close", HandlerClose);
    AppendHandler("get", HandlerGet);
    AppendHandler("ping", HandlerPing);
    AppendHandler("terminate", HandlerTerminate);

    AppendServerInfo( { "127.0.0.0", "master1", 10, 100 } );
    AppendServerInfo( { "127.0.0.1", "master2", 11, 100 } );
    AppendServerInfo( { "127.0.0.2", "master3", 12, 100 } );
}


void Server::HandlerReceivedSocket(AcceptorTCP::Socket &socket, pchar symbols, int number)
{
    sock = &socket;

    static std::string buffer;

    buffer.append(symbols, (size_t)number);

    if (buffer.size() < 5)
    {
        return;
    }

    uint *size_сommand = (uint *)&buffer[0];

    if ((uint)(buffer.size() - sizeof(uint)) < *size_сommand)
    {
        return;
    }

    std::vector<std::string> _words;

    SU::SplitToWords(&buffer[sizeof(uint)], (int)*size_сommand, _words);

    words = &_words;

    auto iter = map.find(_words[0]);

    if (iter != map.end())
    {
        iter->second();
    }

    buffer.erase(0, sizeof(uint) + (size_t)*size_сommand);
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
    if (words->size() == 2)
    {
        if ((*words)[1] == "livingrooms")
        {
            std::string data;

            auto room = Server::livingrooms.begin();

            while (room != Server::livingrooms.end())
            {
                room->second.AppendInfo(room->first, data);

                room++;
            }

            sock->Transmit(data);
        }
    }
    else if (words->size() == 3)
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
    sock->Transmit(std::string("ping"));
}


void HandlerTerminate()
{
    TheServer.Stop();
}
