// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "SliderInt.h"



SliderInt::SliderInt(Context *context) :
    Slider(context)
{

}


void SliderInt::SetRange(int min_, int max_, int step_)
{
    step = step_;
    min = min_ / step;
    max = max_ / step;

    delta = static_cast<float>(min);

    Slider::SetRange(max - delta);
}


void SliderInt::OnDragMove(const IntVector2 &position, const IntVector2 &screenPosition, const IntVector2 &deltaPos,
    MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor *cursor)
{
    Slider::OnDragMove(position, screenPosition, deltaPos, (Urho3D::MouseButtonFlags)buttons, (Urho3D::QualifierFlags)qualifiers, cursor);

    int newValue = static_cast<int>(value_ + delta + 0.5f);

    if(newValue != value)
    {
        value = newValue;
        VariantMap& eventData = GetEventDataMap();
        eventData[SliderIntChanged::P_ELEMENT] = this;
        eventData[SliderIntChanged::P_VALUE] = value * step;
        SendEvent(E_SLIDERINTCHANGED, eventData);
    }
}


int SliderInt::GetValueInt()
{
    return value * step;
}


int SliderInt::GetValueMax()
{
    return max * step;
}


int SliderInt::GetValueMin()
{
    return min * step;
}


void SliderInt::SetValueInt(int newValue)
{
    newValue = newValue / step;

    if(newValue >= min && newValue <= max)
    {
        value = newValue;
        Slider::SetValue(static_cast<float>(newValue) - delta);
        VariantMap& eventData = GetEventDataMap();
        eventData[SliderIntChanged::P_ELEMENT] = this;
        eventData[SliderIntChanged::P_VALUE] = value * step;
        SendEvent(E_SLIDERINTCHANGED, eventData);
    }
}


void SliderInt::Increase()
{
    SetValueInt(GetValueInt() + step);
}


void SliderInt::Decrease()
{
    SetValueInt(GetValueInt() - step);
}


void SliderInt::RegisterObject(Context* context)
{
    context->RegisterFactory<SliderInt>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Slider);
}


SharedPtr<SliderInt> SliderInt::Create(UIElement *uielement, const IntVector2 &size)
{
    SharedPtr<SliderInt> slider(gUIRoot->CreateChild<SliderInt>());
    slider->SetFixedSize(size);
    slider->SetStyle("Slider");

    if(uielement)
    {
        uielement->AddChild(slider);
    }

    return slider;
}
