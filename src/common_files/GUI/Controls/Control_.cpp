// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor_.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Controls/Buttons/ButtonToggled_.h"
#include "GUI/Controls/Sliders/SliderWithTextAndButtons_.h"
#include "GUI/Logic/LineTranslator2D_.h"
#include "GUI/Controls/Label_.h"
#include "GUI/Controls/Control_.h"


Control::Control(Context *context) :
    Window(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}


void Control::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<Control>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Window);
}


bool Control::IsChildOfParent()
{
    return TheUIRoot->FindChild(this) != M_MAX_UNSIGNED;
}


void Control::Toggle()
{
    if(translator)
    {
        translator->Toggle();
    }
}


SharedPtr<LineTranslator2D> Control::GetTranslator()
{
    return translator;
}


bool Control::UnderCursor()
{
    return Window::IsInside(TheCursor->GetCursor()->GetPosition(), true);
}


SharedPtr<ButtonT> Control::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonT> retButton(new ButtonT(this, text, width, height));
    if (x != -1 && y != -1)
    {
        retButton->SetPosition(x, y);
    }
    AddChild(retButton);
    return retButton;
}


SharedPtr<Label> Control::AddLabel(char *text, int x, int y, int width, int height)
{
    SharedPtr<Label> label(Label::Create(text, 20, width, height));

    if (x != -1 && y != -1)
    {
        label->SetPosition(x, y);
    }

    AddChild(label);

    return label;
}


SharedPtr<ButtonToggled> Control::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonToggled> retButton(new ButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    AddChild(retButton);
    return retButton;
}


SharedPtr<SliderWithTextAndButtons> Control::AddSlider(char *text, int min, int max, int step, int x, int y,
    int widthText, int widthRoller)
{
    SharedPtr<SliderWithTextAndButtons> slider(new SliderWithTextAndButtons(this, text, min, max, step, widthText,
        widthRoller));

    AddChild(slider);

    if (x != -1 && y != -1)
    {
        slider->SetPosition(x, y);
    }

    return slider;
}


SharedPtr<DropDownListWithTextAndButton> Control::AddDDList(char *text, int widthText, int widthDDList, int numItems,
    char *items[], int x, int y)
{
    SharedPtr<DropDownListWithTextAndButton> ddList(DropDownListWithTextAndButton::Create(this, text, widthText,
        widthDDList, numItems, items));

    if (x != -1 && y != -1)
    {
        ddList->SetPosition(x, y);
    }

    return ddList;
}


void Control::SetEnabled()
{
    SetVisible(true);
}


void Control::SetDisabled()
{
    SetVisible(false);
}
