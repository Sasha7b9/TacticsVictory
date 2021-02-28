// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


enum Messages
{
    MSG_TEXTSTRING = MSG_USER,
    MSG_REQUEST_FOR_LEVEL,          // Запрос на загрузку уровня
    MSG_RETURN_LEVEL,               // В этом сообщении сервер возрващает уровень
    MSG_KEY_EVENT,
    MSG_SEND_OBJECT_STATE
};
