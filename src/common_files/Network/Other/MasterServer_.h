// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
*   Класс MasterServer должны использовать все приложения, которым нужен доступ к мастер-серверу
*/


struct TaskMasterServer
{
    int         count;          // Сколько раз выполнять задание (0 - бесконечно)
    int64        delta_time;     // Через такие промежутки времени выполнять задание
    int64        prev_time;
    std::string request;        // Выполняемыз запрос
    pFuncVpCh   process;        // Обработка ответа от мастер-сервера
};


class MasterServer
{
public:

    void SetAddress(pchar full_address) {address = full_address; };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection, pFuncVI ping);

    void Connect();

    void Destroy();

    std::string GetValue(pchar key);

    bool IsConnected();

    pchar GetAddress() const { return address.c_str(); }

    void Update();

    void AppendTask(TaskMasterServer *task);

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

    ConnectorTCP connector;     // Соединитель для связи с удалённым мастер-сервером
    bool destroy = false;
    std::mutex  mutex;          // Данный mutex будет захвачен, пока сервер находится в процессе соединения
    std::string address;
    pFuncVV funcFailConnection = nullptr;   // Вызывается в случае неуспешной попытки соединения
    pFuncVV funcConnection     = nullptr;   // Вызывается в случае успешной попытки соединения
    pFuncVV funcDisconnection  = nullptr;   // Вызывается при потере связи с сервером
    pFuncVI funcPing           = nullptr;

    State::E state = State::Idle;
};
