#pragma once
#include "GUI/Elements/Window.h"
#include "GUI/Elements/Button.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StartMenu : public WindowRTS
{
    URHO3D_OBJECT(StartMenu, WindowRTS);

public:
    StartMenu(Context *context = gContext);

private:
    void HandleButtonRelease(StringHash, VariantMap&);

    void SetFocusedNext();
    void SetFocusedPrev();
    int NumFocusedButton();

    PODVector<ButtonRTS*> buttons;

    SharedPtr<ButtonRTS> buttonStartServer;
    SharedPtr<ButtonRTS> buttonStartClient;
    SharedPtr<ButtonRTS> buttonStartEditor;
};
