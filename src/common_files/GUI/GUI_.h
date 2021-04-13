// 2021/04/13 11:25:00 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GUIT : public Object
{
    URHO3D_OBJECT(GUIT, Object);

public:

    GUIT(GUIT **self);

    // Возвращает true, если меню под курсором
    bool UnderCursor();
};
