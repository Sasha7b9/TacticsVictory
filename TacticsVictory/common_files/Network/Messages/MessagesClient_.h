// 2021/12/21 17:55:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Messages/MessagesTypes_.h"


namespace Pi
{
    class MessageRequestGameObjects : public Message
    {
    public:
        MessageRequestGameObjects() : Message(PiTypeMessage::RequestGameObjects) {};
    private:
        virtual bool HandleMessage(Player *sender) const override;
    };


    class MessagePing : public Message
    {
    public:
        MessagePing(uint time);
        MessagePing() : Message(PiTypeMessage::Ping) {};
    private:
        uint timeSend = 0;                                  // Время отправления сообщения серверу
        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };


    class MessageServerCommand : public Message
    {
    public:
        MessageServerCommand(pchar command);
        MessageServerCommand();
    private:
        String<> command;
        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };
}
