#include <stdafx.h>


tvWindow::tvWindow(Context *context) :
    Window(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("Window");
    SetMovable(true);
}

void tvWindow::RegisterObject(Context *context)
{
    context->RegisterFactory<tvWindow>("UI");

    COPY_BASE_ATTRIBUTES(Window);
}

void tvWindow::SetInCenterRect(const IntRect& rect)
{
    int x = (rect.right_ + rect.left_) / 2 - GetWidth() / 2;
    int y = (rect.bottom_ + rect.top_) / 2 - GetHeight() / 2;
    SetPosition(x, y);
}

bool tvWindow::IsChildOfParent()
{
    return gUIRoot->FindChild(this) != Urho3D::M_MAX_UNSIGNED;
}

void tvWindow::Toggle()
{
    SetVisible(!IsVisible());
}

SharedPtr<tvButton> tvWindow::AddButton(char *text, int x, int y, int width, int height)
{
    SharedPtr<tvButton> retButton(new tvButton(this, text, width, height));
    retButton->SetPosition(x, y);
    return retButton;
}

SharedPtr<tvButtonToggled> tvWindow::AddButtonToggled(char *text, int x, int y, int width, int height)
{
    SharedPtr<tvButtonToggled> retButton(new tvButtonToggled(this, text, width, height));
    retButton->SetPosition(x, y);
    return retButton;
}