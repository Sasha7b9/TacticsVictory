#pragma once


class tvSliderWithTextAndButtons : public UIElement
{
    OBJECT(tvSliderWithTextAndButtons);

public:
    tvSliderWithTextAndButtons(UIElement *uielement, char *text, int min, int max);

    void SetRange(int min, int max);
    void SetValue(int value);

private:
    tvSliderWithTextAndButtons& operator=(const tvSliderWithTextAndButtons&) {};

    void HandleSliderIntChanged(StringHash eventType, VariantMap& eventData);
    void HandleButtonDown(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    SharedPtr<tvSliderInt> slider;
    SharedPtr<Text> textValue;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
};