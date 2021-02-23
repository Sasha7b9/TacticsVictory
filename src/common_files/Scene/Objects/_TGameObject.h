// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GameObject : public Component
{
    URHO3D_OBJECT(GameObject, Component);

public:

    static Vector<GameObject *> storage;

protected:

    GameObject(Context *context);
};
