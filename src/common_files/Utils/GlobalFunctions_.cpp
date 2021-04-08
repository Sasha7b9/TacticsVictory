// 2021/04/08 22:06:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/GlobalFunctions_.h"


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


unsigned GF::GetLastModifiedTime(char *name)
{
    String fullName = TheFileSystem->GetProgramDir();
    fullName.Erase(fullName.Length() - 1);
    fullName.Erase(fullName.FindLast('/'), 6);
    fullName += String("/") + RESOURCES_DIR + "/" + name;
    return TheFileSystem->GetLastModifiedTime(fullName);
}
