#include <stdafx.h>


#include "Window.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/ButtonToggled.h"


vWindow::vWindow(Context *context) :
    Window(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}

void vWindow::RegisterObject(Context *context)
{
    context->RegisterFactory<vWindow>("UI");

    COPY_BASE_ATTRIBUTES(Window);
}

void vWindow::SetInCenterRect(const IntRect& rect)
{
    int x = (rect.right_ + rect.left_) / 2 - GetWidth() / 2;
    int y = (rect.bottom_ + rect.top_) / 2 - GetHeight() / 2;
    SetPosition(x, y);
}

bool vWindow::IsChildOfParent()
{
    return gUIRoot->FindChild(this) != Urho3D::M_MAX_UNSIGNED;
}

void vWindow::Toggle()
{
    SetVisible(!IsVisible());
}

SharedPtr<vButton> vWindow::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<vButton> retButton(new vButton(this, text, width, height));
    retButton->SetPosition(x, y);
    return retButton;
}

SharedPtr<vButtonToggled> vWindow::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<vButtonToggled> retButton(new vButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    return retButton;
}