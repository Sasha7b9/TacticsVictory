// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/GUI_.h"


class Label;
class WindowT;


class GUI : public GUIT
{
    URHO3D_OBJECT(GUI, GUIT);

public:
    GUI(GUI **self);

    // Добавить информационное сообщение
    void AppendInfo(pchar text);

    // Добавить предупреждающее сообщение
    void AppendWarning(pchar text);

    void SetPing(int) {};

private:
    void Create();
    void RegistrationObjects();
    void CreateLabelMaster();

    SharedPtr<Label> label_info;                    // Здесь выводится состояние мастер-сервера
};
