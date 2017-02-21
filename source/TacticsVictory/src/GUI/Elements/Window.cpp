#include <stdafx.h>


#include "Window.h"
#include "GUI/Elements/ButtonMain.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Elements/SliderWithTextAndButtons.h"
#include "GUI/Elements/DropDownListWithTextAndButton.h"
#include "GUI/Elements/Cursor.h"


WindowRTS::WindowRTS(Context *context) :
    Window(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}

void WindowRTS::RegisterObject(Context *context)
{
    context->RegisterFactory<WindowRTS>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Window);
}

bool WindowRTS::IsChildOfParent()
{
    return gUIRoot->FindChild(this) != M_MAX_UNSIGNED;
}

void WindowRTS::Toggle()
{
    if(translator)
    {
        translator->Toggle();
    }
}

SharedPtr<LineTranslator2D> WindowRTS::GetTranslator()
{
    return translator;
}

bool WindowRTS::UnderCursor()
{
    return Window::IsInside(gCursor->GetCursor()->GetPosition(), true);
}

SharedPtr<ButtonMain> WindowRTS::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonMain> retButton(new ButtonMain(this, text, width, height));
    if (x != -1 && y != -1)
    {
        retButton->SetPosition(x, y);
    }
    AddChild(retButton);
    return retButton;
}

SharedPtr<ButtonToggled> WindowRTS::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonToggled> retButton(new ButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    AddChild(retButton);
    return retButton;
}

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

SharedPtr<DropDownListWithTextAndButton> WindowRTS::AddDDList(char *text, int widthText, int widthDDList, int numItems, char *items[], int x, int y)
{
    SharedPtr<DropDownListWithTextAndButton> ddList(DropDownListWithTextAndButton::Create(this, text, widthText, widthDDList, numItems, items));
    if (x != -1 && y != -1)
    {
        ddList->SetPosition(x, y);
    }
    return ddList;
}

SharedPtr<Label> WindowRTS::AddLabel(char *text)
{
    SharedPtr<Label> label(Label::Create(text));
    AddChild(label);
    return label;
}