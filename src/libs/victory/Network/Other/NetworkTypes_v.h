// 2021/04/07 20:38:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


// Обрабатываемые мастер-сервером запросы
#define MSG_NTW_PING                "ping"                  // запрос пинга
#define MSG_NTW_INFO_LIVINGROOM     "info_livingroom"       // Этим сообщением гостиная сообщает мастер-серверу о
                                                            // своём состоянии
#define MSG_NTW_SET_NAME_LIVINGROOM "set_name_livingrom"    // Установка имени гостиной
                                                            // Запрос смещения порта гостевой комнаты относительно

#define MSG_NTW_GET                 "get"
#define MSG_NTW_GET_PORT_LIVINGROOM_BROADCAST_UDP           \
                                            MSG_NTW_GET " port livingroom_broadcast_udp"   // порта мастер-сервера


struct TaskMasterServer
{
    pFuncUV    request = 0;             // Обработчик запроса. Должен возвращать id запроса
    pFuncpCpVU handler_answer = 0;      // Обработчик ответа
    int64      delta_time = 0;          // Через такие промежутки времени выполнять задание
    int64      prev_time = 0;
    int64      last_tive_receive = 0;
    uint       counter = 0xFFFFFFFF;     // Столько раз выполнять задачу

    // Возвращает true, если существуют выполненные задания (те, у которых счётчик == 0)
    static bool ExistCompleted(std::vector<TaskMasterServer *> &tasks);
};


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
    void *benv;      // Буфер событий libevent
    std::vector<uint8>       message;   // Здесь хранится принятое сообщение - сначала строка, а потом дополнительные
                                        // данные, если есть
    std::vector<std::string> words;     // Разбитая на слова текстовая часть сообщения
    std::string              name;      // Имя гостиной, как оно будет отображаться в окне выбора сервера у игроков

    void *GetRawData();                 // Возвращает указатель на данные, если таковые имеются в сообщении

    static uint GetID(std::vector<uint8> &received);

    static uint GetSize(std::vector<uint8> &received);

    // Перемещает байты запроса из received в data. При этом из искоходного вектора перемещённые данные удаляются
    static void MoveData(std::vector<uint8> &received, std::vector<uint8> &data);
};


struct SockAddrIn
{
    void Init(uint16 family, pchar ip, uint16 port);

    // Возвращает количество принятых байт
    int RecvFrom(evutil_socket_t socket, char *buffer, int size_buffer);

    char *GetIP();
    uint16 GetPort();

    sockaddr *GetSockAddr();

private:

    sockaddr_in addr = { 0 };
};
