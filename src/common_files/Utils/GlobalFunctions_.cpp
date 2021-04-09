// 2021/04/08 22:06:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/GlobalFunctions_.h"


void GF::DelayMS(uint delay)
{
    using namespace std::chrono;
    using namespace std::this_thread;

    sleep_until(system_clock::now() + milliseconds(delay));
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


unsigned GF::GetLastModifiedTime(char *name)
{
    String fullName = TheFileSystem->GetProgramDir();
    fullName.Erase(fullName.Length() - 1);
    fullName.Erase(fullName.FindLast('/'), 6);
    fullName += String("/") + RESOURCES_DIR + "/" + name;
    return TheFileSystem->GetLastModifiedTime(fullName);
}


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


#ifdef GRAPHICS

void GF::SetWindowInCenterScreen(Window *window)
{
    window->SetPosition(TheGraphics->GetWidth() / 2 - window->GetWidth() / 2,
        TheGraphics->GetHeight() / 2 - window->GetHeight() / 2);
}

#endif
