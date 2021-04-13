// 2021/04/12 23:12:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/Window_.h"


class Chat : public WindowT
{
    URHO3D_OBJECT(Chat, WindowT);

public:

    Chat();

private:

    SharedPtr<LineEdit> line_edit;      // ����� ������ ���� �����
    SharedPtr<Text>     text;           // ����� ��������� ��������� ��������� - ���� � ������������

    void HandlerFinishedText(StringHash, VariantMap &);
    void HandlerUnhandledKey(StringHash, VariantMap &);
    void HandlerClick(StringHash, VariantMap &);
    void HandlerResize(StringHash, VariantMap &);
};
