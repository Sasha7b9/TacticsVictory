// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Label;
class WindowT;


class GUI : public Object
{
    URHO3D_OBJECT(GUI, Object);

public:
    GUI(GUI **self);

    // Возвращает true, если меню под курсором
    bool UnderCursor();

    // Добавить информационное сообщение
    void AppendInfo(pchar text);

    // Добавить предупреждающее сообщение
    void AppendWarning(pchar text);

private:
    void Create();
    void RegistrationObjects();
    void CreateLabelMaster();

    SharedPtr<Label> label_info;                    // Здесь выводится состояние мастер-сервера
};
