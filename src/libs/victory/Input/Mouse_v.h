// 2021/02/24 15:30:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Mouse : public Object
{
    URHO3D_OBJECT(Mouse, Object);

public:

    Mouse(Mouse **self, Context *context);

private:

    void HandlerMouseDown(StringHash, VariantMap &);
    void ProcessMouseLeft();
    void ProcessMouseRight();
};
