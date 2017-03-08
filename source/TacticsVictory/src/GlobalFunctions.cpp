﻿#include <stdafx.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetWindowInCenterScreen(Window *window)
{
    window->SetPosition(gGraphics->GetWidth() / 2 - window->GetWidth() / 2, gGraphics->GetHeight() / 2 - window->GetHeight() / 2);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void OpenFileSelector(char *title, char *textOk, char *textCancel, Vector<String> &filters)
{
    SAFE_DELETE(gFileSelector);
    gFileSelector = new FileSelector(gContext);
    XMLFile *style = gCache->GetResource<XMLFile>("UI/DefaultStyle.xml");
    gFileSelector->SetDefaultStyle(style);

    gFileSelector->GetWindow()->SetResizable(false);
    SetWindowInCenterScreen(gFileSelector->GetWindow());
    gFileSelector->GetWindow()->SetVisible(false);
    gFileSelector->GetWindow()->SetModal(false);

    gFileSelector->SetTitle(title);
    gFileSelector->SetButtonTexts(textOk, textCancel);
    gFileSelector->GetWindow()->SetVisible(true);
    gFileSelector->GetWindow()->BringToFront();
    gFileSelector->SetFilters(filters, 0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
unsigned GetLastModifiedTime(char* name)
{
    String fullName = gFileSystem->GetProgramDir();
    fullName.Erase(fullName.Length() - 1);
    fullName.Erase(fullName.FindLast('/'), 6);
    fullName += String("/TVData/") + String(name);
    return gFileSystem->GetLastModifiedTime(fullName);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
String GetNameFile(const char *name)
{
    String fullName;

    if(gCache)
    {
        Vector<String> dirs = gCache->GetResourceDirs();

        for(String &dir : dirs)
        {
            fullName = dir + name;
            if(gFileSystem->FileExists(fullName))
            {
                break;
            }
            fullName = "";
        }
    }

    if(fullName.Empty())
    {
        fullName = RESOURCES_DIR + String(name);
        if(!gFileSystem->FileExists(fullName))
        {
            fullName = "../out/" + fullName;
            if(!gFileSystem->FileExists(fullName))
            {
                fullName = "../" + fullName;
                if(!gFileSystem->FileExists(fullName))
                {
                    fullName = "";
                }
            }
        }
    }

    return fullName;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
String IntToString(int value, uint length)
{
    String str(value);
    while(str.Length() < length)
    {
        str.Insert(0, '0');
    }
    return str;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool GetAddressPort(const Vector<String> &words, String &address, uint16 &port)
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
            port = (uint16)ToUInt(word.Substring(5));
        }
    }

    return true;
}
