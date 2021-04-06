// 2021/04/06 12:10:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Mutator : public Component
{
    URHO3D_OBJECT(Mutator, Component);

public:
    Mutator(Context *context);
    virtual ~Mutator();

    virtual void Update();

    static Mutator *Empty();
};
