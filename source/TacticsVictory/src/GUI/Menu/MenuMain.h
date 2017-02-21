#pragma once


#include "GUI/Elements/Window.h"


class ButtonSwitch;


class MenuMain : public WindowRTS
{
    URHO3D_OBJECT(MenuMain, WindowRTS);

public:
    MenuMain(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);
    void SetEnabled();
    void SetDisabled();

private:
    MenuMain& operator=(const MenuMain&)
    {};

    void HandleButtonRelease(StringHash, VariantMap&);  
    void HandleKeyDown(StringHash, VariantMap&);        // ���������� ������� ������ ��� �������� ����

    void SetFocusedNext();                              // ���������� ����� �� ��������� ������
    void SetFocusedPrev();                              // ���������� ����� �� ���������� ������
    int NumFocusedButton();                             // ���������� ����� ��������������� ������. ���� ����� �� ����������, ���������� 0

    PODVector<ButtonMain*> buttons;

    SharedPtr<ButtonMain> buttonNewGame;
    SharedPtr<ButtonMain> buttonEditor;
    SharedPtr<ButtonMain> buttonExit;
    SharedPtr<ButtonMain> buttonOptions;
    SharedPtr<ButtonSwitch> buttonLanguage;
};