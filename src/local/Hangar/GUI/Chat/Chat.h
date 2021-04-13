// 2021/04/12 23:12:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class Chat : public WindowT
{
    URHO3D_OBJECT(Chat, WindowT);

public:

    Chat();

private:

    SharedPtr<LineEdit> line_edit;      // Здесь вводим свой текст
    SharedPtr<Text>     text;           // Здесь выводятся последние сообщения - свои и собеседников

    void HandleFinishedText(StringHash, VariantMap &);
    void HandleUnhandledKey(StringHash, VariantMap &);
    void HandleClick(StringHash, VariantMap &);
};
