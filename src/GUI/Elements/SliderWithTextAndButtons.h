#pragma once


#include "GUI/Elements/SliderInt.h"


class SliderWithTextAndButtons : public UIElement
{
    OBJECT(SliderWithTextAndButtons);

public:
    SliderWithTextAndButtons(Context *context = gContext);

    SliderWithTextAndButtons(UIElement *uielement, char *text, int min, int max, int step, int widthText = -1, int widthRoller = -1);

    static void RegisterObject(Context* context = gContext);

    void SetRange(int min, int max, int step);
    void SetValue(int value);
    int GetValue();
    int GetValueMax();
    int GetValueMin();
    void SetHint(char *text);

private:
    SliderWithTextAndButtons& operator=(const SliderWithTextAndButtons&) {};

    SharedPtr<lSliderInt> slider;
    SharedPtr<Urho3D::Text> textValue;
    SharedPtr<Urho3D::Button> buttonLeft;
    SharedPtr<Urho3D::Button> buttonRight;
    SharedPtr<Hint> hint;

    void HandleSliderIntChanged(StringHash, VariantMap&);
    void HandleButtonDown(StringHash, VariantMap&);
    void HandleHoverBegin(StringHash, VariantMap&);
    void HandleHoverEnd(StringHash, VariantMap&);
    void HandleMouseClick(StringHash, VariantMap&);
};