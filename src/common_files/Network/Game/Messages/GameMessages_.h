// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Game/Messages/GameMessagesID_.h"

class TConnection;

namespace Message
{

    struct Message
    {
        Message(int _id) : id(_id) {}
        void Handle(VariantMap &map);
        int id;
        VectorBuffer buffer;

        void Send(bool reliable);   // ����� ������������ ������ ��� �������. ������� ����� ��� �����, � ����� ���-
                                    // ����� ��������
    };


    struct RequestForLevel : public Message
    {
        RequestForLevel() : Message(MSG_REQUEST_FOR_LEVEL) {}

        void Handle(const TConnection &connection);
    };


    struct ReturnLevel : public Message
    {
        ReturnLevel();

        void Handle(MemoryBuffer & /*msg*/) {};
    };


    // �������� ��������� ������
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


    // �������/���������� ������
    struct KeyEvent : public Message
    {
        KeyEvent(Key key,                                       // ��� �������
            bool press) : Message(MSG_KEY_EVENT)                // true - �������, false, ����������
        {
            buffer.WriteInt(key);
            buffer.WriteBool(press);
        }

        void Handle(MemoryBuffer & /*msg*/) {};
    };
}
