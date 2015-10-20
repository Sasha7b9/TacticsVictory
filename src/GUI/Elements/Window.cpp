#include <stdafx.h>


#include "Window.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/ButtonToggled.h"


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

void lWindow::SetInCenterRect(const IntRect& rect)
{
    int x = (rect.right_ + rect.left_) / 2 - GetWidth() / 2;
    int y = (rect.bottom_ + rect.top_) / 2 - GetHeight() / 2;
    SetPosition(x, y);
}

bool lWindow::IsChildOfParent()
{
    return gUIRoot->FindChild(this) != Urho3D::M_MAX_UNSIGNED;
}

void lWindow::Toggle()
{
    SetVisible(!IsVisible());
}

SharedPtr<lButton> lWindow::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<lButton> retButton(new lButton(this, text, width, height));
    retButton->SetPosition(x, y);
    return retButton;
}

SharedPtr<lButtonToggled> lWindow::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<lButtonToggled> retButton(new lButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    return retButton;
}