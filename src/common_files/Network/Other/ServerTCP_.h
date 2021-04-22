// 2021/04/09 14:45:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


struct ClientInfo
{
    struct SocketAddress
    {
        void SetHostIP(void *ip);

        // Возвращает полный адрес клиента в виде "host:port"
        std::string ToStringFull() const;

        // Возвращает только ip-дарес клиента
        std::string ToStringHost() const;

        sockaddr_in sin;
    }                        address;   // Адрес клиента

    std::vector<uint8>       bindata;   // Непосредственно принятые данные
    void                    *benv;      // Буфер событий libevent
    std::vector<uint8>       message;   // Здесь хранится принятое сообщение - сначала строка, а потом дополнительные
                                        // данные, если есть
    std::vector<std::string> words;     // Разбитая на слова текстовая часть сообщения
    std::string              name;      // Имя гостиной, как оно будет отображаться в окне выбора сервера у игроков

    void *GetRawData();                 // Возвращает указатель на данные, если таковые имеются в сообщении
};


class ServerTCP
{
public:

    typedef void (*handlerClient) (uint, ClientInfo &);

    void Run(uint16 port);

    void Stop() { run = false; }

    void AppendHandler(pchar command, handlerClient handler);

    void SendAnswer(void *bev, uint id, pchar message, void *data = nullptr, uint size = 0);
    void SendAnswer(void *bev, uint id, pchar message, pchar data);

    std::map<std::string, handlerClient> handlers;   // Здесь хранятся обработчики запросов по первому слову

    std::map<void *, ClientInfo> clients;

private:

    void Prepare();

    bool run = true;

    struct CallbackArgs
    {
        ServerTCP  *server;
        event_base *base;
    };

    // Вызывается при новом соединении
    static void CallbackRead(struct bufferevent *, void *arg);
    static void CallbackWrite(struct bufferevent *, void *arg);
    static void CallbackAccept(evutil_socket_t listener, short event, void *arg);
    static void CallbackError(struct bufferevent *bev, short what, void *ctx);
    static void CallbackLog(int, const char *);
};
