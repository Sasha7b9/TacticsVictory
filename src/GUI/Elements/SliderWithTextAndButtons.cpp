#include <stdafx.h>


#include "SliderWithTextAndButtons.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/Hint.h"


lSliderWithTextAndButtons::lSliderWithTextAndButtons(UIElement *uielement, char *text_, int min, int max, int step, int widthText, int widthRoller) :
    UIElement(gContext)
{
    SharedPtr<Window> window(new Window(gContext));
    window->SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    window->SetStyle(SET::MENU::ELEM::WINDOW::STYLE);
    AddChild(window);
 
    window->SetLayout(Urho3D::LM_HORIZONTAL, 3, IntRect(3, 3, 3, 3));

    SharedPtr<lLabel> text(lLabel::Create(text_, 15, widthText == -1 ? SET::MENU::TEXT::WIDTH : widthText));
    window->AddChild(text);
    
    IntVector2 sizeSlider = SET::MENU::SLIDER::SIZE;
    if (widthRoller != -1)
    {
        sizeSlider.x_ = widthRoller;
    }
    slider = lSliderInt::Create(window, sizeSlider);
    SubscribeToEvent(slider, E_SLIDERINTCHANGED, HANDLER(lSliderWithTextAndButtons, HandleSliderIntChanged));
    SubscribeToEvent(slider, Urho3D::E_HOVERBEGIN, HANDLER(lSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(slider, Urho3D::E_HOVEREND, HANDLER(lSliderWithTextAndButtons, HandleHoverEnd));

    buttonLeft = new Button(gContext);
    buttonLeft->SetRepeat(0.25f, 20.0f);
    buttonLeft->SetStyle("SliderButtonLeft");
    window->AddChild(buttonLeft);
    SubscribeToEvent(buttonLeft, Urho3D::E_PRESSED, HANDLER(lSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonLeft, Urho3D::E_HOVERBEGIN, HANDLER(lSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonLeft, Urho3D::E_HOVEREND, HANDLER(lSliderWithTextAndButtons, HandleHoverEnd));

    buttonRight = new Button(gContext);
    buttonRight->SetRepeat(0.25f, 20.0f);
    buttonRight->SetStyle("SliderButtonRight");
    window->AddChild(buttonRight);
    SubscribeToEvent(buttonRight, Urho3D::E_PRESSED, HANDLER(lSliderWithTextAndButtons, HandleButtonDown));
    SubscribeToEvent(buttonRight, Urho3D::E_HOVERBEGIN, HANDLER(lSliderWithTextAndButtons, HandleHoverBegin));
    SubscribeToEvent(buttonRight, Urho3D::E_HOVEREND, HANDLER(lSliderWithTextAndButtons, HandleHoverEnd));

    textValue = new Text(gContext);
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

    SubscribeToEvent(Urho3D::E_UIMOUSECLICK, HANDLER(lSliderWithTextAndButtons, HandleMouseClick));
}

void lSliderWithTextAndButtons::RegisterObject(Context* context)
{
    context->RegisterFactory<lWindow>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void lSliderWithTextAndButtons::SetHint(char *text)
{
    hint = new lHint(text);
}

void lSliderWithTextAndButtons::SetRange(int min, int max, int step)
{
    slider->SetRange(min, max, step);
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

    if(button == buttonLeft)
    {
        slider->Decrease();
    }
    else if(button == buttonRight)
    {
        slider->Increase();
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

int lSliderWithTextAndButtons::GetValue()
{
    return slider->GetValueInt();
}

int lSliderWithTextAndButtons::GetValueMin()
{
    return slider->GetValueMin();
}

int lSliderWithTextAndButtons::GetValueMax()
{
    return slider->GetValueMax();
}

void lSliderWithTextAndButtons::HandleMouseClick(StringHash, VariantMap& eventData)
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
