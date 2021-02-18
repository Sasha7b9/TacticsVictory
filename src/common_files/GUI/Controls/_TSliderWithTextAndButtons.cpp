// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/TCursor.h"
#include "GUI/Controls/_THint.h"


SliderWithTextAndButtons::SliderWithTextAndButtons(Context *context) :
    UIElement(context)
{

}


SliderWithTextAndButtons::SliderWithTextAndButtons(UIElement *uielement, char *text_, int min, int max, int step, int widthText, int widthRoller) :
    UIElement(TheContext)
{
    SharedPtr<Window> window(new Window(TheContext));
    window->SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);
 
    window->SetLayout(LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> text(Label::Create(text_, true, 15, widthText == -1 ? SET::MENU::TEXT::WIDTH : widthText, -1));
    window->AddChild(text);
    
    IntVector2 sizeSlider = SET::MENU::SLIDER::SIZE;
    if (widthRoller != -1)
    {
        sizeSlider.x_ = widthRoller;
    }
    slider = SliderInt::Create(window, sizeSlider);
    SubscribeToEvent(slider, E_SLIDERINTCHANGED, URHO3D_HANDLER(SliderWithTextAndButtons, HandleSliderIntChanged));
    SubscribeToEvent(slider, E_HOVERBEGIN, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(slider, E_HOVEREND, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverEnd));

    buttonLeft = new Button(TheContext);
    buttonLeft->SetRepeat(0.25f, 20.0f);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, E_PRESSED, URHO3D_HANDLER(SliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonLeft, E_HOVERBEGIN, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, E_HOVEREND, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverEnd));

    buttonRight = new Button(TheContext);
    buttonRight->SetRepeat(0.25f, 20.0f);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, E_PRESSED, URHO3D_HANDLER(SliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonRight, E_HOVERBEGIN, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonRight, E_HOVEREND, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverEnd));

    textValue = new Text(TheContext);
    textValue->SetFixedWidth(35);
    textValue->SetFont(TheFont, 15);
    textValue->SetText(String(slider->GetValue()));
    window->AddChild(textValue);

    SetMinSize(window->GetWidth(), window->GetHeight());
    
    SetRange(min, max, step);

    if(uielement)
    {
        uielement->AddChild(this);
    }

    SubscribeToEvent(E_UIMOUSECLICK, URHO3D_HANDLER(SliderWithTextAndButtons, HandleMouseClick));
}


void SliderWithTextAndButtons::RegisterObject(Context* context)
{
    context->RegisterFactory<SliderWithTextAndButtons>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(UIElement);
}


void SliderWithTextAndButtons::SetHint(char *text)
{
    hint = new Hint(text);
}


void SliderWithTextAndButtons::SetRange(int min, int max, int step)
{
    slider->SetRange(min, max, step);
}


void SliderWithTextAndButtons::SetValue(int value)
{
    slider->SetValueInt(value);
}


void SliderWithTextAndButtons::HandleSliderIntChanged(StringHash, VariantMap& eventData_) //-V2009
{
    int value = slider->GetValueInt();
    textValue->SetText(String(value));

    VariantMap &eventData = GetEventDataMap();
    eventData[SliderIntChanged::P_ELEMENT] = this;
    eventData[SliderIntChanged::P_VALUE] = eventData_[SliderIntChanged::P_VALUE];
    SendEvent(E_SLIDERINTCHANGED, eventData);
}


void SliderWithTextAndButtons::HandleButtonDown(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Pressed::P_ELEMENT].GetPtr();

    if(button == buttonLeft)
    {
        slider->Decrease();
    }
    else if(button == buttonRight)
    {
        slider->Increase();
    }
}


void SliderWithTextAndButtons::HandleHoverBegin(StringHash, VariantMap&)
{
    TheCursor->SetSelected();
}


void SliderWithTextAndButtons::HandleHoverEnd(StringHash, VariantMap&)
{
    TheCursor->SetNormal();
}


int SliderWithTextAndButtons::GetValue()
{
    return slider->GetValueInt();
}


int SliderWithTextAndButtons::GetValueMin()
{
    return slider->GetValueMin();
}


int SliderWithTextAndButtons::GetValueMax()
{
    return slider->GetValueMax();
}


void SliderWithTextAndButtons::HandleMouseClick(StringHash, VariantMap& eventData)
{
    UIElement *pointer = (UIElement*)eventData[UIMouseClick::P_ELEMENT].GetPtr();

    PODVector<UIElement*> childrens;

    GetChildren(childrens, true);

    if (childrens.Contains(pointer))
    {
        int buttons = (int)eventData[UIMouseClick::P_BUTTONS].GetInt();

        if (buttons == MOUSEB_RIGHT)
        {
            if (hint)
            {
                if (TheHint)
                {
                    TheUIRoot->RemoveChild(TheHint);
                }
                int x = (int)eventData[UIMouseClick::P_X].GetInt();
                int y = (int)eventData[UIMouseClick::P_Y].GetInt();
                hint->SetPosition(x, y - hint->GetHeight());
                TheUIRoot->AddChild(hint);
                hint->BringToFront();
                TheHint = hint;
                TheCounterHint = 0;
            }
        }
    }
}
