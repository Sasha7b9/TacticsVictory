// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/SocketsTCP_.h"


/*
 *   Через класс ServerConnector осуществляется взаимодействие с сервером со стороны клиента
 */


struct TaskMasterServer
{
    pFuncUV    request = 0;        // Обработчик запроса. Должен возвращать id запроса
    pFuncpCpVU handler_answer = 0; // Обработчик ответа
    int64      delta_time = 0;     // Через такие промежутки времени выполнять задание
    int64      prev_time = 0;
    int64      last_tive_receive = 0;
};


class ServerConnector
{
public:

    void SetAddress(pchar _host, uint16 _port)
    {
        host = _host;
        port = _port;
    };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection);

    void Connect();

    void SetTasks();

    void Update();

    void Destroy();

    // Посылка запроса. Каждый запрос помечается уникальным 32-х битным идентификатором, который передаётся четырьмя
    // байтами в начале засылки.
    uint SendRequest(pchar request, const void *data = nullptr, uint size = 0);
    uint SendRequest(pchar request, pchar data);

    bool IsConnected();

    // Выполнять задачу через заданные промежутки времени
    void SetTask(int64 dT, TaskMasterServer *task);

    struct State { enum E {
        Idle,                   // Простой
        NeedConnection,         // Нужно подключать
        AttemptConnection,      // В процессе подлючения
        EventConnection,        // Произошло соединение, нужно вызывать функцию funcConnection
        EventFailConnection,    // Неудачное соединение, нужно вызывать функцию funcFailConnection
        InConnection,           // Подключено
        EventDisconnect,        // Событие обрыва связи с мастер-сервером
        GetPing                 // Получен пинг
    }; };

    std::vector<uint8> data;        // Здесь хранятся принятые данные

private:

    ConnectorTCP connector;         // Сюдой посылаем данные в сервер

    std::string host;
    uint16 port;                    // Порт засылки в сервер. порт чтения на 1 больше

    std::vector<TaskMasterServer *>    all_tasks;       // Здесь периодически выполняемые задачи
    std::map<uint, TaskMasterServer *> active_tasks;    // Задачи, ожидающие ответа

    bool destroy = false;
    std::mutex  mutex;              // Данный mutex будет захвачен, пока сервер находится в процессе соединения
    pFuncVV funcFailConnection = nullptr;   // Вызывается в случае неуспешной попытки соединения
    pFuncVV funcConnection     = nullptr;   // Вызывается в случае успешной попытки соединения
    pFuncVV funcDisconnection  = nullptr;   // Вызывается при потере связи с сервером

    State::E state = State::Idle;

    uint last_request_id = 0;

    void ExecuteTasks();

    // Принять имеющиеся данные
    void ReceiveData();

    // Обработать принятые данные
    void ProcessData();
};
