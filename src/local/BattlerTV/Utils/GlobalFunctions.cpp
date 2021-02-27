// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/GlobalFunctions.h"


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
    SetWindowInCenterScreen(window);
    window->SetVisible(false);
    window->SetModal(false);

    TheFileSelector->SetTitle(title);
    TheFileSelector->SetButtonTexts(textOk, textCancel);
    window->SetVisible(true);
    window->BringToFront();
    TheFileSelector->SetFilters(filters, 0);
}


unsigned GF::GetLastModifiedTime(char* name)
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

    if(TheCache)
    {
        Vector<String> dirs = TheCache->GetResourceDirs();

        for(String &dir : dirs)
        {
            fullName = dir + name;
            if(TheFileSystem->FileExists(fullName))
            {
                break;
            }
            fullName = "";
        }
    }

    if(fullName.Empty())
    {
        fullName = RESOURCES_DIR + String(name);
        if(!TheFileSystem->FileExists(fullName))
        {
            fullName = "../out/" + fullName;
            if(!TheFileSystem->FileExists(fullName))
            {
                fullName = "../" + fullName;
                if(!TheFileSystem->FileExists(fullName))
                {
                    fullName = "";
                }
            }
        }
    }

    return fullName;
}


String GF::IntToString(int value, uint length)
{
    String str(value);
    while(str.Length() < length)
    {
        str.Insert(0, '0');
    }
    return str;
}


bool GF::GetAddressPort(const Vector<String> &words, String &address, uint16 &port)
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
        else if(word.Substring(0, 4) == "port") //-V112
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
