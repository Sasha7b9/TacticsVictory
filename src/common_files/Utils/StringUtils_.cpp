#include "stdafx.h"
#include "Utils/StringUtils_.h"


char *SU::Strcat(char *dest, pchar source)
{
#ifdef WIN32
#pragma warning(push, 2)
#endif
    return strcat(dest, source);
#ifdef WIN32
#pragma warning(pop)
#endif
}


void SU::SplitToWords(pchar symbols, uint number, std::vector<std::string> &out)
{
    out.clear();
    std::string token;
    std::string input;

    for (uint i = 0; i < number; i++)
    {
        input.push_back(*symbols++);
    }

    input.push_back(' ');

    std::istringstream tokenStream(input);

    while (std::getline(tokenStream, token, ' '))
    {
        out.push_back(token);
    }
}


int SU::Length(pchar str)
{
    return (int)std::strlen(str);
}


int SU::Compare(pchar str1, pchar str2)
{
    return std::strcmp(str1, str2);
}


void SU::ReplaceSymbols(std::string &string, char old, char young)
{
    char symbol[2] = { young, '\0' };

    auto pos = string.find(old);

    while (pos != std::string::npos)
    {
        pos = string.replace(pos, 1, symbol).find(old);
    }
}


bool SU::BeginWith(pchar string, pchar symbols)
{
    if (std::strlen(symbols) > std::strlen(string))
    {
        return false;
    }

    return std::memcmp(string, symbols, std::strlen(symbols)) == 0;
}


bool SU::VerifyOnMask(pchar s, pchar mask)
{
    const   char *cp = 0;
    const   char *mp = 0;

    for (; *s && *mask != '*'; mask++, s++)
    {
        if (*mask != *s && *mask != '?')
        {
            return false;
        }
    }

    for (;;)
    {
        if (!*s)
        {
            while (*mask == '*')
            {
                mask++;
            }
            return !*mask;
        }

        if (*mask == '*')
        {
            if (!*++mask)
            {
                return true;
            }
            mp = mask;
            cp = s + 1;
            continue;
        }

        if (*mask == *s || *mask == '?')
        {
            mask++, s++;
            continue;
        }

        mask = mp;
        s = cp++;
    }
}
