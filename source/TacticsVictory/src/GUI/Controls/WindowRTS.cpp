// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "WindowRTS.h"
#include "Button.h"
#include "Label.h"
#include "ButtonToggled.h"
#include "SliderWithTextAndButtons.h"
#include "DropDownListWithTextAndButton.h"
#include "GUI/Cursor.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowRTS::WindowRTS(Context *context) :
    Window(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowRTS::RegisterObject(Context *context)
{
    context->RegisterFactory<WindowRTS>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Window);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool WindowRTS::IsChildOfParent()
{
    return gUIRoot->FindChild(this) != M_MAX_UNSIGNED;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowRTS::Toggle()
{
    if(translator)
    {
        translator->Toggle();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<LineTranslator2D> WindowRTS::GetTranslator()
{
    return translator;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool WindowRTS::UnderCursor()
{
    return Window::IsInside(gCursor->GetCursor()->GetPosition(), true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<ButtonRTS> WindowRTS::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonRTS> retButton(new ButtonRTS(this, text, width, height));
    if (x != -1 && y != -1)
    {
        retButton->SetPosition(x, y);
    }
    AddChild(retButton);
    return retButton;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<Label> WindowRTS::AddLabel(char *text, bool center, int x, int y, int width, int height)
{
    SharedPtr<Label> label(Label::Create(text, center, 20, width, height));
    if (x != -1 && y != -1)
    {
        label->SetPosition(x, y);
    }
    AddChild(label);
    return label;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<ButtonToggled> WindowRTS::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonToggled> retButton(new ButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    AddChild(retButton);
    return retButton;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<SliderWithTextAndButtons> WindowRTS::AddSlider(char *text, int min, int max, int step, int x, int y, int widthText, int widthRoller)
{
    SharedPtr<SliderWithTextAndButtons> slider(new SliderWithTextAndButtons(this, text, min, max, step, widthText, widthRoller));
    AddChild(slider);
    if (x != -1 && y != -1)
    {
        slider->SetPosition(x, y);
    }
    return slider;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<DropDownListWithTextAndButton> WindowRTS::AddDDList(char *text, int widthText, int widthDDList, int numItems, char *items[], int x, int y)
{
    SharedPtr<DropDownListWithTextAndButton> ddList(DropDownListWithTextAndButton::Create(this, text, widthText, widthDDList, numItems, items));
    if (x != -1 && y != -1)
    {
        ddList->SetPosition(x, y);
    }
    return ddList;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowRTS::SetEnabled()
{
    SetVisible(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowRTS::SetDisabled()
{
    SetVisible(false);
}
