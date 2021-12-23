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
    data << id;
    data << typeGameObject;
    data << (int)typeUnit;
    data << typeAirUnit;
    data << typeGroundUnit;
    data << typeWaterUnit;
    data.Write(&transform, sizeof(transform));
}


bool MessageCreateGameObject::Decompress(Decompressor &data)
{
    data >> id;
    data >> typeGameObject;

    int type = 0;
    data >> type;
    typeUnit = (TypeUnit)type;

    data >> typeAirUnit;
    data >> typeGroundUnit;
    data >> typeWaterUnit;

    data.Read(&transform, sizeof(transform));

    return true;
}


void MessageGameObjectNodeTransform::Compress(Compressor &data) const
{
    data << num_objects;

    data.Write(id, sizeof(id[0]) * num_objects);

    data.Write(position, sizeof(position[0]) * num_objects);
}


bool MessageGameObjectNodeTransform::Decompress(Decompressor &data)
{
    data >> num_objects;

    data.Read(id, sizeof(id[0]) * num_objects);

    data.Read(position, sizeof(position[0]) * num_objects);

    return true;
}
