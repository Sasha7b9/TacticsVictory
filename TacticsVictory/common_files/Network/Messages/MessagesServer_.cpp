// 2021/12/21 17:52:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Network/Messages/MessagesServer_.h"
#include "Objects/GameObject_.h"
#include "Objects/Units/Unit_.h"
#include "Objects/Units/Air/AirUnit_.h"
#include "Objects/Units/Ground/GroundUnit_.h"
#include "Objects/Units/Water/WaterUnit_.h"


using namespace Pi;


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


void MessageCreateGameObject::Compress(Compressor &data) const
{
    data << num_objects;
    data.Write(states,  (uint)sizeof(states[0]) * num_objects);
}


bool MessageCreateGameObject::Decompress(Decompressor &data)
{
    data >> num_objects;
    data.Read(states,   (uint)sizeof(states[0]) * num_objects);

    return true;
}


void MessageGameObjectState::Compress(Compressor &data) const
{
    data << num_objects;
    data.Write(states, (uint)sizeof(states[0]) * num_objects);
}


bool MessageGameObjectState::Decompress(Decompressor &data)
{
    data >> num_objects;
    data.Read(states, (uint)sizeof(states[0]) * num_objects);

    return true;
}
