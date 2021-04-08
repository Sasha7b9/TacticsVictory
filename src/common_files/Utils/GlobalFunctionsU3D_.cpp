// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/GlobalFunctionsU3D_.h"


void GFU3D::SetWindowInCenterScreen(Window *window)
{
    window->SetPosition(TheGraphics->GetWidth() / 2 - window->GetWidth() / 2,
        TheGraphics->GetHeight() / 2 - window->GetHeight() / 2);
}


void GFU3D::OpenFileSelector(char *title, char *textOk, char *textCancel, const Vector<String> &filters)
{
    delete TheFileSelector;
    TheFileSelector = new FileSelector(TheContext);
    XMLFile *style = TheCache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    TheFileSelector->SetDefaultStyle(style);

    Window *window = TheFileSelector->GetWindow();
    window->SetResizable(false);
    SetWindowInCenterScreen(window);
    window->SetVisible(false);
    window->SetModal(false);

    TheFileSelector->SetTitle(title);
    TheFileSelector->SetButtonTexts(textOk, textCancel);
    window->SetVisible(true);
    window->BringToFront();
    TheFileSelector->SetFilters(filters, 0);
}


void GFU3D::DelayMS(uint delay)
{
    using namespace std::chrono;
    using namespace std::this_thread;

    sleep_until(system_clock::now() + milliseconds(delay));
}
