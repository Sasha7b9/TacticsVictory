// 2021/12/21 17:55:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesClient_.h"


using namespace Pi;


MessagePing::MessagePing(uint time) :
    Message(PiTypeMessage::Ping, PiFlagMessage::Unordered | PiFlagMessage::Unreliable),
    timeSend(time)
{
}


void MessagePing::Compress(Compressor &data) const
{
    data << timeSend;
}


bool MessagePing::Decompress(Decompressor &data)
{
    data >> timeSend;

    return true;
}
