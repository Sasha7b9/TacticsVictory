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
}
