#include <stdafx.h>


#include "SliderWithTextAndButtons.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"


lSliderWithTextAndButtons::lSliderWithTextAndButtons(UIElement *uielement, char *text_, int min, int max) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);
 
    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<lLabel> text(lLabel::Create(text_, 15, SET::MENU::TEXT::WIDTH));
    window->AddChild(text);
    
    slider = vSliderInt::Create(window, SET::MENU::SLIDER::SIZE);
    SubscribeToEvent(slider, E_SLIDERINTCHANGED, HANDLER(lSliderWithTextAndButtons, HandleSliderIntChanged));
    SubscribeToEvent(slider, E_HOVERBEGIN, HANDLER(lSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(slider, E_HOVEREND, HANDLER(lSliderWithTextAndButtons, HandleHoverEnd));

    buttonLeft = new Button(gContext);
    buttonLeft->SetRepeat(0.25f, 20.0f);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, Urho3D::E_PRESSED, HANDLER(lSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, HANDLER(lSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, HANDLER(lSliderWithTextAndButtons, HandleHoverEnd));

    buttonRight = new Button(gContext);
    buttonRight->SetRepeat(0.25f, 20.0f);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, Urho3D::E_PRESSED, HANDLER(lSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, HANDLER(lSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, HANDLER(lSliderWithTextAndButtons, HandleHoverEnd));

    textValue = new Text(gContext);
    textValue->SetFixedWidth(35);
    textValue->SetFont(gFont, 15);
    textValue->SetText(String(slider->GetValue()));
    window->AddChild(textValue);

    SetMinSize(window->GetWidth(), window->GetHeight());

    SetRange(min, max);

    if(uielement)
    {
        uielement->AddChild(this);
    }
}

void lSliderWithTextAndButtons::SetRange(int min, int max)
{
    slider->SetRange(min, max);
}

void lSliderWithTextAndButtons::SetValue(int value)
{
    slider->SetValueInt(value);
}

void lSliderWithTextAndButtons::HandleSliderIntChanged(StringHash, VariantMap& eventData_)
{
    int value = slider->GetValueInt();
    textValue->SetText(String(value));

    VariantMap &eventData = GetEventDataMap();
    eventData[SliderIntChanged::P_ELEMENT] = this;
    eventData[SliderIntChanged::P_VALUE] = eventData_[SliderIntChanged::P_VALUE];
    SendEvent(E_SLIDERINTCHANGED, eventData);
}

void lSliderWithTextAndButtons::HandleButtonDown(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Urho3D::Pressed::P_ELEMENT].GetPtr();
    int value = slider->GetValueInt();

    if(button == buttonLeft)
    {
        slider->SetValueInt(value - 1);
    }
    else if(button == buttonRight)
    {
        slider->SetValueInt(value + 1);
    }
}

void lSliderWithTextAndButtons::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void lSliderWithTextAndButtons::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}