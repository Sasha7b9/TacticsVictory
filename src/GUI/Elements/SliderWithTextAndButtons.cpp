#include <stdafx.h>


tvSliderWithTextAndButtons::tvSliderWithTextAndButtons(UIElement *uielement, char *text_, int min, int max) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);
 
    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<tvLabel> text(tvLabel::Create(text_, 15, SET::MENU::TEXT::WIDTH));
    window->AddChild(text);
    
    slider = tvSliderInt::Create(window, SET::MENU::SLIDER::SIZE);
    SubscribeToEvent(slider, E_SLIDERINTCHANGED, HANDLER(tvSliderWithTextAndButtons, HandleSliderIntChanged));
    SubscribeToEvent(slider, E_HOVERBEGIN, HANDLER(tvSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(slider, E_HOVEREND, HANDLER(tvSliderWithTextAndButtons, HandleHoverEnd));

    buttonLeft = new Button(gContext);
    buttonLeft->SetRepeat(0.25f, 20.0f);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, E_PRESSED, HANDLER(tvSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, HANDLER(tvSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, HANDLER(tvSliderWithTextAndButtons, HandleHoverEnd));

    buttonRight = new Button(gContext);
    buttonRight->SetRepeat(0.25f, 20.0f);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, E_PRESSED, HANDLER(tvSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, HANDLER(tvSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, HANDLER(tvSliderWithTextAndButtons, HandleHoverEnd));

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

void tvSliderWithTextAndButtons::SetRange(int min, int max)
{
    slider->SetRange(min, max);
}

void tvSliderWithTextAndButtons::SetValue(int value)
{
    slider->SetValueInt(value);
}

void tvSliderWithTextAndButtons::HandleSliderIntChanged(StringHash, VariantMap& eventData_)
{
    int value = slider->GetValueInt();
    textValue->SetText(String(value));

    VariantMap &eventData = GetEventDataMap();
    eventData[SliderIntChanged::P_ELEMENT] = this;
    eventData[SliderIntChanged::P_VALUE] = eventData_[SliderIntChanged::P_VALUE];
    SendEvent(E_SLIDERINTCHANGED, eventData);
}

void tvSliderWithTextAndButtons::HandleButtonDown(StringHash, VariantMap& eventData)
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

void tvSliderWithTextAndButtons::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void tvSliderWithTextAndButtons::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}