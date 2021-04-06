// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class WindowT;


class GUI : public Object
{
    URHO3D_OBJECT(GUI, Object);

public:
    GUI(GUI **self);
    ~GUI();

    bool UnderCursor();                                             // Возвращает true, если меню под курсором

private:
    void Create();
    void RegistrationObjects();
};
