#pragma once


#include "GUI/Elements/SliderInt.h"


class vSliderWithTextAndButtons : public UIElement
{
    OBJECT(vSliderWithTextAndButtons);

public:
    vSliderWithTextAndButtons(UIElement *uielement, char *text, int min, int max);

    void SetRange(int min, int max);
    void SetValue(int value);

private:
    vSliderWithTextAndButtons& operator=(const vSliderWithTextAndButtons&) {};

    void HandleSliderIntChanged(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    SharedPtr<vSliderInt> slider;
    SharedPtr<Text> textValue;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
};