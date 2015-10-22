#pragma once


#include "GUI/Elements/SliderInt.h"


class lSliderWithTextAndButtons : public UIElement
{
    OBJECT(lSliderWithTextAndButtons);

public:
    lSliderWithTextAndButtons(UIElement *uielement, char *text, int min, int max);

    void SetRange(int min, int max);
    void SetValue(int value);
    int GetValue();

private:
    lSliderWithTextAndButtons& operator=(const lSliderWithTextAndButtons&) {};

    void HandleSliderIntChanged(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    SharedPtr<lSliderInt> slider;
    SharedPtr<Text> textValue;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
};