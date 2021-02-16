// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


WindowTV::WindowTV(Context *context) :
    Window(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}


void WindowTV::RegisterObject(Context *context)
{
    context->RegisterFactory<WindowTV>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Window);
}


bool WindowTV::IsChildOfParent()
{
    return TheUIRoot->FindChild(this) != M_MAX_UNSIGNED;
}


void WindowTV::Toggle()
{
    if(translator)
    {
        translator->Toggle();
    }
}


SharedPtr<LineTranslator2D> WindowTV::GetTranslator()
{
    return translator;
}


bool WindowTV::UnderCursor()
{
    return Window::IsInside(TheCursor->GetCursor()->GetPosition(), true);
}


SharedPtr<ButtonTV> WindowTV::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonTV> retButton(new ButtonTV(this, text, width, height));
    if (x != -1 && y != -1)
    {
        retButton->SetPosition(x, y);
    }
    AddChild(retButton);
    return retButton;
}


SharedPtr<Label> WindowTV::AddLabel(char *text, bool center, int x, int y, int width, int height)
{
    SharedPtr<Label> label(Label::Create(text, center, 20, width, height));
    if (x != -1 && y != -1)
    {
        label->SetPosition(x, y);
    }
    AddChild(label);
    return label;
}


SharedPtr<ButtonToggled> WindowTV::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<ButtonToggled> retButton(new ButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    AddChild(retButton);
    return retButton;
}


SharedPtr<SliderWithTextAndButtons> WindowTV::AddSlider(char *text, int min, int max, int step, int x, int y, int widthText, int widthRoller)
{
    SharedPtr<SliderWithTextAndButtons> slider(new SliderWithTextAndButtons(this, text, min, max, step, widthText, widthRoller));
    AddChild(slider);
    if (x != -1 && y != -1)
    {
        slider->SetPosition(x, y);
    }
    return slider;
}


SharedPtr<DropDownListWithTextAndButton> WindowTV::AddDDList(char *text, int widthText, int widthDDList, int numItems, char *items[], int x, int y)
{
    SharedPtr<DropDownListWithTextAndButton> ddList(DropDownListWithTextAndButton::Create(this, text, widthText, widthDDList, numItems, items));
    if (x != -1 && y != -1)
    {
        ddList->SetPosition(x, y);
    }
    return ddList;
}


void WindowTV::SetEnabled()
{
    SetVisible(true);
}


void WindowTV::SetDisabled()
{
    SetVisible(false);
}
