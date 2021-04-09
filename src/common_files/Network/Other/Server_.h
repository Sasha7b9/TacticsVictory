// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   Класс ServerConnector должны использовать все приложения, которым нужен доступ к мастер-серверу
*/


struct TaskMasterServer
{
    int         count;          // Сколько раз выполнять задание (0 - бесконечно)
    int64       delta_time;     // Через такие промежутки времени выполнять задание
    pFuncVV     func;           // Обработка ответа от мастер-сервера
    int64       prev_time;
};


class ServerConnector
{
public:

    void SetAddress(pchar _host, uint16 _port)
    {
        host = _host;
        port = _port;
    };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection, pFuncVI ping);

    void Connect();

    void Destroy();

    std::string GetAnswer(pchar key);

    void SendString(pchar string);

    std::string GetAnswer();

    bool IsConnected();

    void Update();

    // Выполнять задачу через заданные промежутки времени
    void SetTask(TaskMasterServer *task);

    struct State { enum E {
        Idle,                   // Простой
        NeedConnection,         // Нужно подключать
        AttemptConnection,      // В процессе подлючения
        EventConnection,        // Произошло соединение, нужно вызывать функцию funcConnection
        EventFailConnection,    // Неудачное соединение, нужно вызывать функцию funcFailConnection
        InConnection,           // Подключено
        WaitPing,               // Ожидание сообщения о пинге
        EventDisconnect,        // Событие обрыва связи с мастер-сервером
        GetPing                 // Получен пинг
    }; };

private:

    ConnectorTCP connOUT;       // Сюдой посылаем данные в сервер
    ConnectorTCP connIN;        // Сюда принимаем данные от сервера

    std::string host;
    uint16 port;                // Порт засылки в сервер. порт чтения на 1 больше

    bool destroy = false;
    std::mutex  mutex;          // Данный mutex будет захвачен, пока сервер находится в процессе соединения
    pFuncVV funcFailConnection = nullptr;   // Вызывается в случае неуспешной попытки соединения
    pFuncVV funcConnection     = nullptr;   // Вызывается в случае успешной попытки соединения
    pFuncVV funcDisconnection  = nullptr;   // Вызывается при потере связи с сервером
    pFuncVI funcPing           = nullptr;

    State::E state = State::Idle;

    void ExecuteTasks(int64 now);
};
