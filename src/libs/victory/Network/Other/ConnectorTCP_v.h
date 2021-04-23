// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Other/NetworkTypes_v.h"
#include <map>
#include <mutex>
#include <thread>
#include <queue>


// Клиент клиента
class BaseConnectorTCP
{
public:

    virtual ~BaseConnectorTCP();

    void Release();

    bool Connect(const std::string &host, uint16 port);

    void SetReadTimeOut(uint timeout);

    void SetWriteTimeOut(uint timeout);

    void Disconnect();

    bool IsConnected() const;

    // Передаёт size байт из массива data
    void Transmit(const void *data, uint size);

    // Делает попытку приёма size байт в массив data. Возвращает количество реально принятых байт.
    // В случае ошибки возрващает -1
    // Если size == 0, то ничего не читает, а возвращает количество доступных для чтения байт
    ssize_t Receive(void *data, uint size);

private:

    std::unique_ptr<sockpp::tcp_connector>  connection;
};


/*
 *   Через класс ConnectorTCP осуществляется взаимодействие с сервером со стороны клиента
 */

class ConnectorTCP
{
public:

    void Init(pchar _host, uint16 _port)
    {
        host = _host;
        port = _port;
    };

    void SetCallbacks(pFuncVV fail, pFuncVV connection, pFuncVV disconnection);

    void RunCycle();

    void Connect();

    void Disconnect();

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

    // Единожды выполнить задачу
    void RunTask(TaskMasterServer *task);

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

    std::vector<uint8> data;                        // Здесь хранятся принятые данные

    bool thread_need_stopped = false;       // true, если поток нуждается в запуске
    bool thread_is_stopped = true;          // true, если поток остановлен

private:

    BaseConnectorTCP connector;                     // Сюдой посылаем данные в сервер

    std::string host;
    uint16 port;                                    // Порт засылки в сервер. порт чтения на 1 больше

    std::map<uint, TaskMasterServer *> wait_tasks;  // Задачи, ожидающие ответа (выполненные)
    std::vector<TaskMasterServer *>    new_tasks;   // Задачи, ожидающие выполнения (поставленные в очередь для
                                                    // выполнения

    bool destroy = false;
    std::mutex  mutex;                      // Данный mutex будет захвачен, пока сервер находится в процессе соединения
    pFuncVV funcFailConnection = nullptr;   // Вызывается в случае неуспешной попытки соединения
    pFuncVV funcConnection     = nullptr;   // Вызывается в случае успешной попытки соединения
    pFuncVV funcDisconnection  = nullptr;   // Вызывается при потере связи с сервером

    std::unique_ptr<std::thread> thread_update = nullptr;

    State::E state = State::Idle;

    uint last_request_id = 0;

    // Выполнить имеющиеся задания
    void ExecuteTasks();

    // Принять имеющиеся данные
    void ReceiveData();

    // Обработать принятые данные
    void ProcessData();

    // Возвращает false, если соединение с сервером потеряно
    bool ExistConnection();
};
