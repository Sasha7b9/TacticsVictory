// 2021/12/21 17:55:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Messages/MessagesTypes_.h"


namespace Pi
{
    class MessagePing : public Message
    {
    public:
        MessagePing();
    private:
        uint timeSend = 0;                                  // Время отправления сообщения серверу
        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
        static uint time_prev;      // Время предыдущего приёма сообщения пинга. Если оно равно нулю
                                    // либо прошло более 10 секунд после предыщего приёма, сервер потерян
    };


    class MessageRequestCreateGameObject : public Message
    {
    public:
        MessageRequestCreateGameObject(int _id = -1) :
            Message(PiTypeMessage::RequestCreateGameObject, PiFlagMessage::Unreliable), id(_id) {}
    private:
        int id;
        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };
}
