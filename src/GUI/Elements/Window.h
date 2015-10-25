#pragma once


#include "GUI/Logic/LineTranslator2D.h"


class lWindow : public Window
{
    OBJECT(lWindow)

public:
    lWindow(Context *context = gContext);

    static void RegisterObject(Context *context);

    bool IsChildOfParent();
    void Toggle();
    bool IsInside(IntVector2 position, bool isScreen);
    SharedPtr<lLineTranslator2D> GetTranslator();

    SharedPtr<lButton> AddButton(char *text, int x = -1, int y = -1, int width = -1, int height = -1);
    SharedPtr<lButtonToggled> AddButtonToggled(char *text, int x, int y, int width, int height);
    SharedPtr<lSliderWithTextAndButtons> AddSlider(char *text, int min, int max, int step, int x = -1, int y = -1);
    SharedPtr<lLabel> AddLabel(char *text);

protected:
    lWindow& operator=(const lWindow&)
    {};

    HashMap<Button*, uint> mapButtonsActions;
    SharedPtr<lLineTranslator2D> translator;
};