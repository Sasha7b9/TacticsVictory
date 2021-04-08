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


bool GFU3D::GetAddressPort(const Vector<String> &words, String &address, uint16 &port)
{
    for(String word : words)
    {
        if(word[0] == '-')
        {
            word.Erase(0, 1);
        }

        if(word.Substring(0, 7) == "address")
        {
            if(word[7] != ':')
            {
                return false;
            }
            address = word.Substring(8);
        }
        else if(word.Substring(0, 4) == "port")
        {
            if(word[4] != ':')
            {
                return false;
            }
            port = static_cast<uint16>(ToUInt(word.Substring(5)));
        }
    }

    if (port == 0)
    {
        address = String::EMPTY;
        return false;
    }

    return true;
}


void GFU3D::DelayMS(uint delay)
{
    using namespace std::chrono;
    using namespace std::this_thread;

    sleep_until(system_clock::now() + milliseconds(delay));
}
