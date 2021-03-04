// 2021/03/03 21:55:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ObjectSpecificC : public ObjectSpecific
{
    URHO3D_OBJECT(ObjectSpecificC, ObjectSpecific);

public:

    ObjectSpecificC(ObjectT *object);

    static HashMap<uint, ObjectT *> remoteStorage;  // Здесь хранятся игровые объекты сцены по id сцены на сервере
};
