// 2021/12/22 9:17:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace PiTypeMessage
    {
        enum
        {
            // Сообщения от сервера клиенту
            CreateLandscape = BaseCount,            // Сообщение о создании ландшафта при подключении нового клиента
            CreateGameObject,                       // Сообщение о создании нового GameObject
            SendGameObjectState,                    // Сообщение с новым пространственным преобразованием Game Object

            // Сообщения от клиента серверу
            RequestCreateGameObject,                // Когда клиент получает сообщение SendGameObjectState с id
                                                    // несуществующего объекта, он посылает запрос на создание этого
                                                    // объекта

            // Симметричные команды
            ServerCommand,                          // Команда серверу. Ответ от сервера
            Ping
        };
    }
}
