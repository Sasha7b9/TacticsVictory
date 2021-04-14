// 2021/04/08 22:06:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/GlobalFunctions_.h"
#include <thread>


static std::chrono::system_clock::time_point time_start;



void GF::DelayMS(uint delay)
{
    using namespace std::chrono;
    using namespace std::this_thread;

    sleep_until(system_clock::now() + milliseconds(delay));
}


void GF::Timer::TimeStart()
{
    time_start = std::chrono::system_clock::now();
}


int64 GF::Timer::DeltaMS()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - time_start).count();
}


int64 GF::Timer::TimeMS()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


#ifdef U3D


String GF::IntToString(int value, uint length)
{
    String str(value);

    while (str.Length() < length)
    {
        str.Insert(0, '0');
    }
    return str;
}


bool GF::GetAddressPort(const Vector<String> &words, String &address, uint16 &port)
{
    for (String word : words)
    {
        if (word[0] == '-')
        {
            word.Erase(0, 1);
        }

        if (word.Substring(0, 7) == "address")
        {
            if (word[7] != ':')
            {
                return false;
            }
            address = word.Substring(8);
        }
        else if (word.Substring(0, 4) == "port")
        {
            if (word[4] != ':')
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


unsigned GF::GetLastModifiedTime(char *name)
{
    String fullName = TheFileSystem->GetProgramDir();
    fullName.Erase(fullName.Length() - 1);
    fullName.Erase(fullName.FindLast('/'), 6);
    fullName += String("/") + RESOURCES_DIR + "/" + name;
    return TheFileSystem->GetLastModifiedTime(fullName);
}


String GF::GetNameFile(const char *name)
{
    String fullName;

    if (TheCache)
    {
        Vector<String> dirs = TheCache->GetResourceDirs();

        for (String &dir : dirs)
        {
            fullName = dir + name;
            if (TheFileSystem->FileExists(fullName))
            {
                break;
            }
            fullName = "";
        }
    }

    if (fullName.Empty())
    {
        fullName = RESOURCES_DIR + String(name);
        if (!TheFileSystem->FileExists(fullName))
        {
            fullName = "../out/" + fullName;
            if (!TheFileSystem->FileExists(fullName))
            {
                fullName = "../" + fullName;
                if (!TheFileSystem->FileExists(fullName))
                {
                    fullName = "";
                }
            }
        }
    }

    return fullName;
}


#ifdef GRAPHICS

void GF::SetWindowInCenterScreen(Window *window)
{
    window->SetPosition(TheGraphics->GetWidth() / 2 - window->GetWidth() / 2,
        TheGraphics->GetHeight() / 2 - window->GetHeight() / 2);
}

void GF::OpenFileSelector(char *title, char *textOk, char *textCancel, const Vector<String> &filters)
{
    delete TheFileSelector;
    TheFileSelector = new FileSelector(TheContext);
    XMLFile *style = TheCache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    TheFileSelector->SetDefaultStyle(style);

    Window *window = TheFileSelector->GetWindow();
    window->SetResizable(false);
    GF::SetWindowInCenterScreen(window);
    window->SetVisible(false);
    window->SetModal(false);

    TheFileSelector->SetTitle(title);
    TheFileSelector->SetButtonTexts(textOk, textCancel);
    window->SetVisible(true);
    window->BringToFront();
    TheFileSelector->SetFilters(filters, 0);
}

#endif

#endif
