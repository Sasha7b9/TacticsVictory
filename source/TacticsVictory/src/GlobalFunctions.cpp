#include <stdafx.h>


#include "GlobalFunctions.h"


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
String GetNameFile(char *name)
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
        }
    }
    else
    {

    }

    return fullName;
}
