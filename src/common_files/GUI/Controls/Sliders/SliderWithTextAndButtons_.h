// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Hint;
class SliderInt;


class SliderWithTextAndButtons : public UIElement
{
    URHO3D_OBJECT(SliderWithTextAndButtons, UIElement);

public:
    SliderWithTextAndButtons(Context *);
    SliderWithTextAndButtons(UIElement *uielement, pchar text, int min, int max, int step, int widthText = -1,
        int widthRoller = -1);
    static void RegisterObject();

    void SetRange(int min, int max, int step);
    void SetValue(int value);
    int GetValue();
    int GetValueMax();
    int GetValueMin();
    void SetHint(pchar text);

private:
    SharedPtr<SliderInt> slider;
    SharedPtr<Text> textValue;
    SharedPtr<Button> buttonLeft;
    SharedPtr<Button> buttonRight;
    SharedPtr<Hint> hint;

    void HandlerSliderIntChanged(StringHash, VariantMap&);
    void HandlerButtonDown(StringHash, VariantMap&);
    void HandlerHoverBegin(StringHash, VariantMap&);
    void HandlerHoverEnd(StringHash, VariantMap&);
    void HandlerMouseClick(StringHash, VariantMap&);
};
