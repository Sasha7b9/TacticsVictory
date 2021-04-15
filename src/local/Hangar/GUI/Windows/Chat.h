// 2021/04/12 23:12:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Control_.h"


class Chat : public Control
{
    URHO3D_OBJECT(Chat, Control);

public:

    Chat();

private:

    SharedPtr<LineEdit> lineEdit;       // Здесь вводим свой текст
    SharedPtr<Text>     text;           // Здесь выводятся последние сообщения - свои и собеседников

    void HandlerFinishedText(StringHash, VariantMap &);
    void HandlerUnhandledKey(StringHash, VariantMap &);
    void HandlerClick(StringHash, VariantMap &);
    void HandlerResize(StringHash, VariantMap &);
};
