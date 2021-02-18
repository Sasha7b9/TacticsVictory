// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class TWindow;


class GUI : public Object
{
    URHO3D_OBJECT(GUI, Object);

public:
    GUI();
    ~GUI();

    bool GheckOnDeadZoneForCursorBottomScreen(int x);
    bool UnderCursor();                                             // Возвращает true, если меню под курсором
    void SetVisibleWindow(TWindow *window, bool visible);
    void SetUnvisibleAllWindows();

private:
    void Create();
    void RegistrationObjects();
};
