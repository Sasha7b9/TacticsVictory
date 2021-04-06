﻿// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Label;
class WindowT;


class GUI : public Object
{
    URHO3D_OBJECT(GUI, Object);

public:
    GUI(GUI **self);

    bool UnderCursor();                                             // Возвращает true, если меню под курсором

private:
    void Create();
    void RegistrationObjects();
    void CreateLabelMaster();

    SharedPtr<Label> label_info;                    // Здесь выводится состояние мастер-сервера
};
