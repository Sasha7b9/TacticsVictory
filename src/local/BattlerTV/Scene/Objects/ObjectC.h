// 2021/03/03 21:55:55 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GameObjectSpecificC : public GameObjectSpecific
{
    URHO3D_OBJECT(GameObjectSpecificC, GameObjectSpecific);

public:

    GameObjectSpecificC(ObjectT *object);
};
