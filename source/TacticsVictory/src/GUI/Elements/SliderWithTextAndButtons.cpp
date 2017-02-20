#include <stdafx.h>


#include "SliderWithTextAndButtons.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/Hint.h"


SliderWithTextAndButtons::SliderWithTextAndButtons(Context *context) :
    UIElement(context)
{

}


SliderWithTextAndButtons::SliderWithTextAndButtons(UIElement *uielement, char *text_, int min, int max, int step, int widthText, int widthRoller) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);
 
    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<Label> text(Label::Create(text_, 15, widthText == -1 ? SET::MENU::TEXT::WIDTH : widthText, -1));
    window->AddChild(text);
    
    IntVector2 sizeSlider = SET::MENU::SLIDER::SIZE;
    if (widthRoller != -1)
    {
        sizeSlider.x_ = widthRoller;
    }
    slider = SliderInt::Create(window, sizeSlider);
    SubscribeToEvent(slider, E_SLIDERINTCHANGED, URHO3D_HANDLER(SliderWithTextAndButtons, HandleSliderIntChanged));
    SubscribeToEvent(slider, Urho3D::E_HOVERBEGIN, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(slider, Urho3D::E_HOVEREND, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverEnd));

    buttonLeft = new Urho3D::Button(gContext);
    buttonLeft->SetRepeat(0.25f, 20.0f);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, Urho3D::E_PRESSED, URHO3D_HANDLER(SliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonLeft, Urho3D::E_HOVERBEGIN, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, Urho3D::E_HOVEREND, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverEnd));

    buttonRight = new Urho3D::Button(gContext);
    buttonRight->SetRepeat(0.25f, 20.0f);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, Urho3D::E_PRESSED, URHO3D_HANDLER(SliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonRight, Urho3D::E_HOVERBEGIN, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonRight, Urho3D::E_HOVEREND, URHO3D_HANDLER(SliderWithTextAndButtons, HandleHoverEnd));

    textValue = new Urho3D::Text(gContext);
    textValue->SetFixedWidth(35);
    textValue->SetFont(gFont, 15);
    textValue->SetText(String(slider->GetValue()));
    window->AddChild(textValue);

    SetMinSize(window->GetWidth(), window->GetHeight());
    
    SetRange(min, max, step);

    if(uielement)
    {
        uielement->AddChild(this);
    }

    SubscribeToEvent(Urho3D::E_UIMOUSECLICK, URHO3D_HANDLER(SliderWithTextAndButtons, HandleMouseClick));
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

void SliderWithTextAndButtons::HandleSliderIntChanged(StringHash, VariantMap& eventData_)
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
    Urho3D::Button *button = (Urho3D::Button*)eventData[Urho3D::Pressed::P_ELEMENT].GetPtr();

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
    gCursor->SetSelected();
}

void SliderWithTextAndButtons::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
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
    UIElement *pointer = (UIElement*)eventData[Urho3D::UIMouseClick::P_ELEMENT].GetPtr();

    PODVector<UIElement*> childrens;

    GetChildren(childrens, true);

    if (childrens.Contains(pointer))
    {
        int buttons = (int)eventData[Urho3D::UIMouseClick::P_BUTTONS].GetInt();

        if (buttons == Urho3D::MOUSEB_RIGHT)
        {
            if (hint)
            {
                if (gHint)
                {
                    gUIRoot->RemoveChild(gHint);
                }
                int x = (int)eventData[Urho3D::UIMouseClick::P_X].GetInt();
                int y = (int)eventData[Urho3D::UIMouseClick::P_Y].GetInt();
                hint->SetPosition(x, y - hint->GetHeight());
                gUIRoot->AddChild(hint);
                hint->BringToFront();
                gHint = hint;
                gCounterHint = 0;
            }
        }
    }
}
