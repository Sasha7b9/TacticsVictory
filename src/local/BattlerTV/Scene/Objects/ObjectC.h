// 2021/03/03 21:55:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GameObjectSpecificC : public ObjectSpecific
{
    URHO3D_OBJECT(GameObjectSpecificC, ObjectSpecific);

public:

    GameObjectSpecificC(ObjectT *object);
};
