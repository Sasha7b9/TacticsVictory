#pragma once


#include "GUI/Elements/SliderInt.h"


class lSliderWithTextAndButtons : public UIElement
{
    OBJECT(lSliderWithTextAndButtons);

public:
    lSliderWithTextAndButtons(UIElement *uielement, char *text, int min, int max, int step, int widthText = -1, int widthRoller = -1);

    static void RegisterObject(Context* context);

    void SetRange(int min, int max, int step);
    void SetValue(int value);
    int GetValue();
    int GetValueMax();
    int GetValueMin();
    void SetHint(char *text);

private:
    lSliderWithTextAndButtons& operator=(const lSliderWithTextAndButtons&) {};

    SharedPtr<lSliderInt> slider;
    SharedPtr<Text> textValue;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
    SharedPtr<lHint> hint;

    void HandleSliderIntChanged(StringHash, VariantMap&);
    void HandleButtonDown(StringHash, VariantMap&);
    void HandleHoverBegin(StringHash, VariantMap&);
    void HandleHoverEnd(StringHash, VariantMap&);
    void HandleMouseClick(StringHash, VariantMap&);
};