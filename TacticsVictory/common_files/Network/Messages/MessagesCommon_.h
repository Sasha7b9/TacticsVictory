// 2021/12/25 14:03:58 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Network/Messages/MessagesTypes_.h"


namespace Pi
{
    class MessageServerCommand : public Message
    {
    public:
        MessageServerCommand(pchar _command = "") :
            Message(PiTypeMessage::ServerCommand, PiFlagMessage::Unordered), command(_command) {};
    private:
        String<> command;
        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *) const override;
    };
}
