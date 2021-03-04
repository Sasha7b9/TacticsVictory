// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


enum Messages
{
    SERV_TEXTSTRING = MSG_USER,
    SERV_REQUEST_FOR_LEVEL,         // Запрос на загрузку уровня
    SERV_KEY_EVENT,

    CLNT_RETURN_LEVEL,              // В этом сообщении сервер возрващает уровень
    CLNT_CREATE_GAME_OBJECT,        // Создание нового компонента
    CLNT_SEND_OBJECT_STATE,
    CLNT_SEND_TANK_POSITION,        // Передаёт позицию танка
    CLNT_SEND_SCENE                 // Посылает состояние сцены
};
