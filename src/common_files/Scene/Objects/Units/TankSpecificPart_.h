// 2021/02/25 21:33:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TankSpecificPart : public Object
{
    URHO3D_OBJECT(TankSpecificPart, Object);

public:

    TankSpecificPart();

    virtual void Start(Node *) {};

    virtual void OnMouseClick(VariantMap &, Node *) { };
};
