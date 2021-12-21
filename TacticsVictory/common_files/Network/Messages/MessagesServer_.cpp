// 2021/12/21 17:52:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesServer_.h"


using namespace Pi;


MessageCreateLandscape::MessageCreateLandscape(pchar _name_file) : Message(PiTypeMessage::CreateLandscape)
{
    pchar pointer = &_name_file[strlen(_name_file) - 1];

    while (*pointer != '\\' && *pointer != '/')
    {
        pointer--;
    }

    pointer--;

    while (*pointer != '\\' && *pointer != '/')
    {
        pointer--;
    }

    name_file = pointer + 1;
}


MessageCreateLandscape::MessageCreateLandscape() : Message(PiTypeMessage::CreateLandscape)
{
}


void MessageCreateLandscape::Compress(Compressor &data) const
{
    data << name_file.Length() + 1;
    data << name_file.c_str();
}


bool MessageCreateLandscape::Decompress(Decompressor &data)
{
    int size = 0;
    data >> size;
    name_file.SetLength(size);

    data.Read((char *)name_file.c_str(), (uint)size);

    return true;
}


bool MessageCreateLandscape::HandleMessage(Player *sender) const
{
    return false;
}
