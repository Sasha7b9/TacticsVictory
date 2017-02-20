#pragma once


#include "GUI/Logic/LineTranslator2D.h"


class ButtonToggled;
class ButtonMain;
class SliderWithTextAndButtons;
class DropDownListWithTextAndButton;
class Label;


class lWindow : public Window
{
    URHO3D_OBJECT(lWindow, Window);

public:
    lWindow(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    bool IsChildOfParent();
    void Toggle();
    SharedPtr<LineTranslator2D> GetTranslator();
    bool UnderCursor();

    SharedPtr<ButtonMain> AddButton(char *text, int x = -1, int y = -1, int width = -1, int height = -1);
    SharedPtr<ButtonToggled> AddButtonToggled(char *text, int x, int y, int width, int height);
    SharedPtr<SliderWithTextAndButtons> AddSlider(char *text, int min, int max, int step, int x = -1, int y = -1, int widthText = -1, int widthRoller = -1);
    SharedPtr<DropDownListWithTextAndButton> AddDDList(char *text, int widthText, int widthDDList, int numItems, char *items[], int x = -1, int y = -1);
    SharedPtr<Label> AddLabel(char *text);

protected:
    lWindow& operator=(const lWindow&)
    {};

    HashMap<Urho3D::Button*, uint> mapButtonsActions;
    SharedPtr<LineTranslator2D> translator;
};