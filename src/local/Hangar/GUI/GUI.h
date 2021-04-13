// 2021/04/12 22:58:28 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GUI : public Object
{
    URHO3D_OBJECT(GUI, Object);

public:

    GUI(GUI **self);

    // Возвращает true, если меню под курсором
    bool UnderCursor();

private:

    void Create();
    void RegistrationObjects();
};
