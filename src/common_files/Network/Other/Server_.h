// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ClientInfo
{
    struct SocketAddress
    {
        std::string ToString() const;

        sockaddr_in sin;
    }                        address;   // Адрес клиента

    std::vector<uint8>       bindata;   // Непосредственно принятые данные
    void                    *benv;      // Буфер событий libevent
    std::vector<uint8>       message;   // Здесь хранится принятое сообщение - сначала строка, а потом дополнительные
                                        // данные, если есть
    std::vector<std::string> words;     // Разбитая на слова текстовая часть сообщения

    void *GetRawData();                 // Возвращает указатель на данные, если таковые имеются в сообщении
};


class Server
{
public:

    typedef void (*handlerClient) (uint, ClientInfo &);

    void Run();

    void Stop() { run = false; }

    void AppendHandler(pchar command, handlerClient handler);

    void Prepare();

    void SendAnswer(void *bev, uint id, pchar message, void *data = nullptr, uint size = 0);

    static std::map<std::string, handlerClient> handlers;   // Здесь хранятся обработчики запросов по первому слову

private:

    bool run = true;
};
