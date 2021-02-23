// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GameObject : public Object
{
    URHO3D_OBJECT(GameObject, Object);

public:

    static Vector<GameObject *> storage;

    GameObject();
};
