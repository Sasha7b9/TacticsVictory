// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor.h"
#include "GUI/Controls/ButtonSwitch_.h"
#include "GUI/Controls/ButtonToggled_.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/SliderWithTextAndButtons_.h"


TWindow::TWindow(Context *context) :
    Window(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}


void TWindow::RegisterObject(Context *context)
{
    context->RegisterFactory<TWindow>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Window);
}


bool TWindow::IsChildOfParent()
{
    return TheUIRoot->FindChild(this) != M_MAX_UNSIGNED;
}


void TWindow::Toggle()
{
    if(translator)
    {
        translator->Toggle();
    }
}


SharedPtr<LineTranslator2D> TWindow::GetTranslator()
{
    return translator;
}


bool TWindow::UnderCursor()
{
    return Window::IsInside(TheCursor->GetCursor()->GetPosition(), true);
}


SharedPtr<TButton> TWindow::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<TButton> retButton(new TButton(this, text, width, height));
    if (x != -1 && y != -1)
    {
        retButton->SetPosition(x, y);
    }
    AddChild(retButton);
    return retButton;
}


SharedPtr<Label> TWindow::AddLabel(char *text, bool center, int x, int y, int width, int height)
{
    SharedPtr<Label> label(Label::Create(text, center, 20, width, height));
    if (x != -1 && y != -1)
    {
        label->SetPosition(x, y);
    }
    AddChild(label);
    return label;
}


SharedPtr<ButtonToggled> TWindow::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonToggled> retButton(new ButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    AddChild(retButton);
    return retButton;
}


SharedPtr<SliderWithTextAndButtons> TWindow::AddSlider(char *text, int min, int max, int step, int x, int y, int widthText, int widthRoller)
{
    SharedPtr<SliderWithTextAndButtons> slider(new SliderWithTextAndButtons(this, text, min, max, step, widthText, widthRoller));
    AddChild(slider);
    if (x != -1 && y != -1)
    {
        slider->SetPosition(x, y);
    }
    return slider;
}


SharedPtr<DropDownListWithTextAndButton> TWindow::AddDDList(char *text, int widthText, int widthDDList, int numItems, char *items[], int x, int y)
{
    SharedPtr<DropDownListWithTextAndButton> ddList(DropDownListWithTextAndButton::Create(this, text, widthText, widthDDList, numItems, items));
    if (x != -1 && y != -1)
    {
        ddList->SetPosition(x, y);
    }
    return ddList;
}


void TWindow::SetEnabled()
{
    SetVisible(true);
}


void TWindow::SetDisabled()
{
    SetVisible(false);
}
