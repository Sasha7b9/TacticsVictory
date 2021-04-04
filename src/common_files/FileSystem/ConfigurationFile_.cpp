// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "FileSystem/FileSystem_.h"


#define CHECK_ON_VALID_STRING   if (!isValid) { LOGERROR("Configuration file is not valid"); return nullptr; }
#define CHECK_ON_VALID_INT      if (!isValid) { LOGERROR("Configuration file is not valid"); return -1; }

//#define IS_VALID(x)             (&*(x) && (x)->value.IsObject())
#define IS_VALID(x)             (&*(x))


//#define ERROR_FUNCTION
#define ERROR_FUNCTION      LOGERRORF("%s has not realisation", __FUNCTION__);


bool ConfigurationFile::Load(pchar name)
{
    document = new rapidjson::Document(); //-V2511

    FS::File file;
    file.Open((std::string("conf") + FS::delimiter + name).c_str(), __FILE__, __LINE__);

    if (!file.IsOpened())
    {
        LOGERRORF("Can't load configuration file %s", name);

        return false;
    }

    std::string buffer;

    file.Read(buffer, file.Size());

    document->Parse(buffer.c_str());

    if (document->HasParseError())
    {
        LOGERRORF("Can't parse configuration file %s. Error %d", name, document->GetParseError());

        isValid = false;

        return false;
    }
    
    LOGWRITEF("Configuration file %s is parsed", name);

    isValid = true;

    return true;
}


void ConfigurationFile::Unload()
{
    SAFE_DELETE(document);
}


int ConfigurationFile::GetInt(pchar key1, pchar key2, pchar key3, pchar key4)
{
    auto it = FindMember(key1, key2, key3, key4);

    if (&*it && it->value.IsInt())
    {
        return it->value.GetInt();
    }

    return -1;
}


pchar ConfigurationFile::GetString(pchar key1, pchar key2, pchar key3, pchar key4)
{
    auto it = FindMember(key1, key2, key3, key4);

    if (&*it && it->value.IsString())
    {
        return it->value.GetString();
    }

    return "";
}


float ConfigurationFile::GetFloat(pchar key1, pchar key2)
{
    auto it = FindMember(key1, key2);

    if (&*it && it->value.IsFloat())
    {
        return it->value.GetFloat();
    }

    return 0.0f;
}


rapidjson::Value::ConstMemberIterator ConfigurationFile::FindMember(pchar key1, pchar key2, pchar key3, pchar key4)
{
    auto it = document->FindMember(key1);

    if (IS_VALID(it))
    {
        if (key2)
        {
            it = it->value.FindMember(key2);

            if (IS_VALID(it))
            {
                if (key3)
                {
                    it = it->value.FindMember(key3);

                    if (IS_VALID(it))
                    {
                        if (key4)
                        {
                            it = it->value.FindMember(key4);

                            if (IS_VALID(it))
                            {
                                return it;
                            }
                        }
                        else
                        {
                            return it;
                        }
                    }
                }
                else
                {
                    return it;
                }
            }
        }
        else
        {
            return it;
        }
    }

    LOGERRORF("Can not find value for \"%s\" \"%s\" \"%s\" \"%s\"", key1, key2, key3, key4);

    return it;
}


bool ConfigurationFile::GetVectorStrings(pchar key, std::vector<std::string> &strings)
{
    strings.clear();

    if (!isValid)
    {
        LOGERROR("Configuration file is not valid");
        return false;
    }

    if (document->HasMember(key))
    {
        rapidjson::Value::ConstMemberIterator it = document->FindMember(key);

        auto &value = it->value;

        if (value.IsArray() && value.Size() > 0)
        {
            for (rapidjson::Value::ConstValueIterator elem = value.Begin(); elem != value.End(); ++elem)
            {
                if (elem->IsString())
                {
                    strings.push_back(elem->GetString());
                }
            }
        }
    }

    if (strings.size() == 0)
    {
        LOGERRORF("Can't load array from key %s", key);
    }

    return strings.size() != 0;
}


IntVector2 ConfigurationFile::GetIntVector2(pchar key1, pchar key2, pchar key3, pchar key4)
{
    IntVector2 result(0, 0);

    auto it = FindMember(key1, key2, key3, key4);

    LOGERRORF("%s has not realisation", __FUNCTION__);

    return result;
}



void ConfigurationFile::SetInt(pchar /*key*/, int /*value*/)
{
    LOGERRORF("%s has not realisation", __FUNCTION__);
}


void ConfigurationFile::SetInt(pchar /*key1*/, pchar /*key2*/, int /*value*/)
{
    LOGERRORF("%s has not realisation", __FUNCTION__);
}
