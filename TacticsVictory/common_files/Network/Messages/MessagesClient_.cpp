// 2021/12/21 17:55:23 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesClient_.h"


using namespace Pi;


uint MessagePing::time_prev = 0;


void MessagePing::Compress(Compressor &data) const
{
    data << timeSend;
}


bool MessagePing::Decompress(Decompressor &data)
{
    data >> timeSend;

    return true;
}


void MessageRequestCreateGameObject::Compress(Compressor &data) const
{
    data << id;
}


bool MessageRequestCreateGameObject::Decompress(Decompressor &data)
{
    data >> id;

    return true;
}
