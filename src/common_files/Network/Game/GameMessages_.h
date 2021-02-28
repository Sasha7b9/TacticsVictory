// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Game/GameMessagesID_.h"

class TConnection;

namespace Message
{

    struct Message
    {
        Message(int _id) : id(_id) {}
        void Handle(VariantMap &map);
        int id;
        VectorBuffer buffer;

        void Send(bool reliable);   // Метод действителен только для клиента. Серверу нужно ещё знать, в какое сое-
                                    // нение засылать
    };


    struct RequestForLevel : public Message
    {
        RequestForLevel() : Message(MSG_REQUEST_FOR_LEVEL) {}

        void Handle(const TConnection &connection);
    };


    struct ReturnLevel : public Message
    {
        ReturnLevel(const Vector3 &position)             // позиция созданной сущности клиента
            : Message(MSG_RETURN_LEVEL)
        {
            buffer.WriteVector3(position);
        }

        void Handle(MemoryBuffer & /*msg*/) {};
    };


    // Передача текстовой строки
    struct TextString : public Message
    {
        TextString(const String &message) : Message(MSG_TEXTSTRING)
        {
            buffer.WriteString(message);
        }

        void Handle(MemoryBuffer &msg)
        {
            URHO3D_LOGINFO(msg.ReadString());
        }
    };


    // Нажатие/отпускание кнопки
    struct KeyEvent : public Message
    {
        KeyEvent(Key key,                                       // Код клавиши
            bool press) : Message(MSG_KEY_EVENT)                // true - нажатие, false, отпускание
        {
            buffer.WriteInt(key);
            buffer.WriteBool(press);
        }

        void Handle(MemoryBuffer & /*msg*/) {};
    };
}
