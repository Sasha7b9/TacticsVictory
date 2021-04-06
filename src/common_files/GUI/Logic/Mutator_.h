// 2021/04/06 12:10:34 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Mutator : public Object
{
    URHO3D_OBJECT(Mutator, Object);
public:
    Mutator(UIElement *node);
    virtual ~Mutator() {}

    virtual void Update(float dT) = 0;

    static Mutator *Empty();

protected:

    UIElement *node;
};
