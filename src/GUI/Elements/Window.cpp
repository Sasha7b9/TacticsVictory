#include <stdafx.h>


#include "Window.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/Label.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Elements/SliderWithTextAndButtons.h"


lWindow::lWindow(Context *context) :
    Window(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}

void lWindow::RegisterObject(Context *context)
{
    context->RegisterFactory<lWindow>("UI");

    COPY_BASE_ATTRIBUTES(Window);
}

bool lWindow::IsChildOfParent()
{
    return gUIRoot->FindChild(this) != Urho3D::M_MAX_UNSIGNED;
}

void lWindow::Toggle()
{
    if(translator)
    {
        translator->Toggle();
    }
}

SharedPtr<lLineTranslator2D> lWindow::GetTranslator()
{
    return translator;
}

bool lWindow::IsInside(IntVector2 position, bool isScreen)
{
    return Window::IsInside(position, isScreen) && IsVisible() && parent_;
}

SharedPtr<lButton> lWindow::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<lButton> retButton(new lButton(this, text, width, height));
    if (x != -1 && y != -1)
    {
        retButton->SetPosition(x, y);
    }
    AddChild(retButton);
    return retButton;
}

SharedPtr<lButtonToggled> lWindow::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<lButtonToggled> retButton(new lButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    AddChild(retButton);
    return retButton;
}

SharedPtr<lSliderWithTextAndButtons> lWindow::AddSlider(char *text, int min, int max, int step, int x, int y)
{
    SharedPtr<lSliderWithTextAndButtons> slider(new lSliderWithTextAndButtons(this, text, min, max, step));
    AddChild(slider);
    if (x != -1 && y != -1)
    {
        slider->SetPosition(x, y);
    }
    return slider;
}

SharedPtr<lLabel> lWindow::AddLabel(char *text)
{
    SharedPtr<lLabel> label(lLabel::Create(text));
    AddChild(label);
    return label;
}