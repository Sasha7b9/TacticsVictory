// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/GlobalFunctions.h"


unsigned GF::GetLastModifiedTime(char* name)
{
    String fullName = TheFileSystem->GetProgramDir();
    fullName.Erase(fullName.Length() - 1);
    fullName.Erase(fullName.FindLast('/'), 6);
    fullName += String("/") + String(RESOURCES_DIR) + "/" + String(name);
    return TheFileSystem->GetLastModifiedTime(fullName);
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
