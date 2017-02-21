#pragma once


#include "GUI/Logic/LineTranslator2D.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/ButtonToggled.h"


class ButtonRTS;
class SliderWithTextAndButtons;
class DropDownListWithTextAndButton;


class WindowRTS : public Window
{
    URHO3D_OBJECT(WindowRTS, Window);

public:
    WindowRTS(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    bool IsChildOfParent();
    void Toggle();
    SharedPtr<LineTranslator2D> GetTranslator();
    bool UnderCursor();

    SharedPtr<ButtonRTS> AddButton(char *text, int x = -1, int y = -1, int width = -1, int height = -1);
    SharedPtr<ButtonToggled> AddButtonToggled(char *text, int x, int y, int width, int height);
    SharedPtr<SliderWithTextAndButtons> AddSlider(char *text, int min, int max, int step, int x = -1, int y = -1, int widthText = -1, int widthRoller = -1);
    SharedPtr<DropDownListWithTextAndButton> AddDDList(char *text, int widthText, int widthDDList, int numItems, char *items[], int x = -1, int y = -1);
    SharedPtr<Label> AddLabel(char *text);

protected:
    HashMap<Button*, uint> mapButtonsActions;
    SharedPtr<LineTranslator2D> translator;

    CONSTRUCTORS(WindowRTS, Window);
};