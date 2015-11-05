#include <stdafx.h>


#include "SliderInt.h"


lSliderInt::lSliderInt(Context *context) :
    Slider(context)
{

}

void lSliderInt::SetRange(int min_, int max_, int step_)
{
    step = step_;
    min = min_ / step;
    max = max_ / step;

    delta = (float)min;

    Slider::SetRange(max - delta);
}

void lSliderInt::OnDragMove(const UIntVector2& position, const UIntVector2& screenPosition, const UIntVector2& deltaPos, int buttons, int qualifiers, UCursor* cursor)
{
    Slider::OnDragMove(position, screenPosition, deltaPos, buttons, qualifiers, cursor);

    int newValue = (int)(value_ + delta + 0.5f);

    if(newValue != value)
    {
        value = newValue;
        VariantMap& eventData = GetEventDataMap();
        eventData[SliderIntChanged::P_ELEMENT] = this;
        eventData[SliderIntChanged::P_VALUE] = value * step;
        SendEvent(E_SLIDERINTCHANGED, eventData);
    }
}

int lSliderInt::GetValueInt()
{
    return value * step;
}

int lSliderInt::GetValueMax()
{
    return max * step;
}

int lSliderInt::GetValueMin()
{
    return min * step;
}

void lSliderInt::SetValueInt(int newValue)
{
    newValue = newValue / step;

    if(newValue >= min && newValue <= max)
    {
        value = newValue;
        Slider::SetValue((float)newValue - delta);
        VariantMap& eventData = GetEventDataMap();
        eventData[SliderIntChanged::P_ELEMENT] = this;
        eventData[SliderIntChanged::P_VALUE] = value * step;
        SendEvent(E_SLIDERINTCHANGED, eventData);
    }
}

void lSliderInt::Increase()
{
    SetValueInt(GetValueInt() + step);
}

void lSliderInt::Decrease()
{
    SetValueInt(GetValueInt() - step);
}

void lSliderInt::RegisterObject(Context* context)
{
    context->RegisterFactory<lSliderInt>("UI");

    COPY_BASE_ATTRIBUTES(Slider);
}

SharedPtr<lSliderInt> lSliderInt::Create(UIElement *uielement, const UIntVector2 &size)
{
    SharedPtr<lSliderInt> slider(gUIRoot->CreateChild<lSliderInt>());
    slider->SetFixedSize(size);
    slider->SetStyle("Slider");

    if(uielement)
    {
        uielement->AddChild(slider);
    }

    return slider;
}