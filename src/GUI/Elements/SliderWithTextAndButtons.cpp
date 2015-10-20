#include <stdafx.h>


#include "SliderWithTextAndButtons.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"


vSliderWithTextAndButtons::vSliderWithTextAndButtons(UIElement *uielement, char *text_, int min, int max) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);
 
    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<vLabel> text(vLabel::Create(text_, 15, SET::MENU::TEXT::WIDTH));
    window->AddChild(text);
    
    slider = vSliderInt::Create(window, SET::MENU::SLIDER::SIZE);
    SubscribeToEvent(slider, E_SLIDERINTCHANGED, HANDLER(vSliderWithTextAndButtons, HandleSliderIntChanged));
    SubscribeToEvent(slider, E_HOVERBEGIN, HANDLER(vSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(slider, E_HOVEREND, HANDLER(vSliderWithTextAndButtons, HandleHoverEnd));

    buttonLeft = new Button(gContext);
    buttonLeft->SetRepeat(0.25f, 20.0f);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, E_PRESSED, HANDLER(vSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, HANDLER(vSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, HANDLER(vSliderWithTextAndButtons, HandleHoverEnd));

    buttonRight = new Button(gContext);
    buttonRight->SetRepeat(0.25f, 20.0f);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, E_PRESSED, HANDLER(vSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, HANDLER(vSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, HANDLER(vSliderWithTextAndButtons, HandleHoverEnd));

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

void vSliderWithTextAndButtons::SetRange(int min, int max)
{
    slider->SetRange(min, max);
}

void vSliderWithTextAndButtons::SetValue(int value)
{
    slider->SetValueInt(value);
}

void vSliderWithTextAndButtons::HandleSliderIntChanged(StringHash, VariantMap& eventData_)
{
    int value = slider->GetValueInt();
    textValue->SetText(String(value));

    VariantMap &eventData = GetEventDataMap();
    eventData[SliderIntChanged::P_ELEMENT] = this;
    eventData[SliderIntChanged::P_VALUE] = eventData_[SliderIntChanged::P_VALUE];
    SendEvent(E_SLIDERINTCHANGED, eventData);
}

void vSliderWithTextAndButtons::HandleButtonDown(StringHash, VariantMap& eventData)
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

void vSliderWithTextAndButtons::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void vSliderWithTextAndButtons::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}