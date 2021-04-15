// 2021/04/15 15:05:20 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class WindowT : public Control
{
    URHO3D_OBJECT(WindowT, Control)

public:

    WindowT(pchar title);

protected:

    SharedPtr<Label> title;

    void HandlerResize(StringHash, VariantMap &);

    virtual void CallbackOnResize() = 0;
};
