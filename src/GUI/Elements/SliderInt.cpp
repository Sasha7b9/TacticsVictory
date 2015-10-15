#include <stdafx.h>


tvSliderInt::tvSliderInt(Context *context) :
    Slider(context)
{

}

void tvSliderInt::SetRange(int min_, int max_)
{
    min = min_;
    max = max_;

    delta = (float)min;

    Slider::SetRange(max - delta);
}

void tvSliderInt::OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor)
{
    Slider::OnDragMove(position, screenPosition, deltaPos, buttons, qualifiers, cursor);

    int newValue = (int)(value_ + delta + 0.5f);

    if(newValue != value)
    {
        value = newValue;
        VariantMap& eventData = GetEventDataMap();
        eventData[SliderIntChanged::P_ELEMENT] = this;
        eventData[SliderIntChanged::P_VALUE] = value;
        SendEvent(E_SLIDERINTCHANGED, eventData);
    }
}

int tvSliderInt::GetValueInt()
{
    return value;
}

void tvSliderInt::SetValueInt(int newValue)
{
    if(newValue >= min && newValue <= max && value != newValue)
    {
        value = newValue;
        Slider::SetValue((float)newValue + delta);
        VariantMap& eventData = GetEventDataMap();
        eventData[SliderIntChanged::P_ELEMENT] = this;
        eventData[SliderIntChanged::P_VALUE] = value;
        SendEvent(E_SLIDERINTCHANGED, eventData);
    }
}

void tvSliderInt::RegisterObject(Context* context)
{
    context->RegisterFactory<tvSliderInt>("UI");

    COPY_BASE_ATTRIBUTES(Slider);
}

SharedPtr<tvSliderInt> tvSliderInt::Create(UIElement *uielement, const IntVector2 &size)
{
    SharedPtr<tvSliderInt> slider(gUIRoot->CreateChild<tvSliderInt>());
    slider->SetFixedSize(size);
    slider->SetStyle("Slider");

    if(uielement)
    {
        uielement->AddChild(slider);
    }

    return slider;
}