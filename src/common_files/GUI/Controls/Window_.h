// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Controls/Buttons/ButtonToggled_.h"
#include "GUI/Logic/LineTranslator2D_.h"


class ButtonT;
class SliderWithTextAndButtons;


class WindowT : public Window
{
    URHO3D_OBJECT(WindowT, Window);

public:
    WindowT(Context *);
    static void RegisterObject();

    bool IsChildOfParent();
    void Toggle();
    void SetEnabled();
    void SetDisabled();
    SharedPtr<LineTranslator2D> GetTranslator();
    bool UnderCursor();
    SharedPtr<ButtonT> AddButton(char *text, int x = -1, int y = -1, int width = -1, int height = -1);
    SharedPtr<ButtonToggled> AddButtonToggled(char *text, int x, int y, int width, int height);
    SharedPtr<SliderWithTextAndButtons> AddSlider(char *text, int min, int max, int step, int x = -1, int y = -1,
        int widthText = -1, int widthRoller = -1);
    SharedPtr<DropDownListWithTextAndButton> AddDDList(char *text, int widthText, int widthDDList, int numItems,
        char *items[], int x = -1, int y = -1);
    SharedPtr<Label> AddLabel(char *text, int x = -1, int y = -1, int width = -1, int height = -1);

protected:
    HashMap<Button *, uint> mapButtonsActions;
    SharedPtr<LineTranslator2D> translator;
};
