// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "FileSystem/FileSystem_.h"


#define CHECK_ON_VALID_STRING   if (!isValid) { LOGERROR("Configuration file is not valid"); return nullptr; }
#define CHECK_ON_VALID_INT      if (!isValid) { LOGERROR("Configuration file is not valid"); return -1; }


#define ERROR_FUNCTION
//#define ERROR_FUNCTION      LOGERRORF("%s has not realisation", __FUNCTION__);


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


int ConfigurationFile::GetIntValue(pchar key)
{
    CHECK_ON_VALID_INT;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key);

    if (it != document->MemberEnd() && it->value.IsInt())
    {
        return it->value.GetInt();
    }

    LOGERRORF("Can't find value for \"%s\"", key);

    return -1;
}


int ConfigurationFile::GetIntValue(pchar key1, pchar key2)
{
    CHECK_ON_VALID_INT;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key1);

    if ((&*it) && (it->value.GetType() == rapidjson::Type::kObjectType))
    {
        if (it->value.HasMember(key2))
        {
            it = it->value.FindMember(key2);

            if (it->value.IsInt())
            {
                return it->value.GetInt();
            }
        }
    }

    LOGERRORF("Can't find value for \"%s\" \"%s\"", key1, key2);

    return -1;
}


int ConfigurationFile::GetIntValue(pchar key1, pchar key2, pchar key3)
{
    CHECK_ON_VALID_INT;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key1);

    if (it->value.GetType() == rapidjson::Type::kObjectType)
    {
        if (it->value.HasMember(key2))
        {
            it = it->value.FindMember(key2);

            if (it->value.HasMember(key3))
            {
                it = it->value.FindMember(key3);

                if (it->value.IsInt())
                {
                    return it->value.GetInt();
                }
            }
        }
    }

    LOGERRORF("Can't find value for \"%s\" \"%s\" \"%s\"", key1, key2, key3);

    return -1;
}


int ConfigurationFile::GetIntValue(pchar key1, pchar key2, pchar key3, pchar key4)
{
    CHECK_ON_VALID_INT;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key1);

    if (it->value.GetType() == rapidjson::Type::kObjectType)
    {
        if (it->value.HasMember(key2))
        {
            it = it->value.FindMember(key2);

            if (it->value.HasMember(key3))
            {
                it = it->value.FindMember(key3);

                if (it->value.HasMember(key4))
                {
                    it = it->value.FindMember(key4);

                    if (it->value.IsInt())
                    {
                        return it->value.GetInt();
                    }
                }
            }
        }
    }

    LOGERRORF("Can't find value for \"%s\" \"%s\" \"%s\" \"%s\"", key1, key2, key3, key4);

    return -1;
}


pchar ConfigurationFile::GetStringValue(pchar key)
{
    CHECK_ON_VALID_STRING;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key);

    if (it != document->MemberEnd() && it->value.IsString())
    {
        return it->value.GetString();
    }

    LOGERRORF("Can't find value for \"%s\" key", key);

    return nullptr;
}


pchar ConfigurationFile::GetStringValue(pchar key1, pchar key2)
{
    CHECK_ON_VALID_STRING;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key1);

    if (it->value.GetType() == rapidjson::Type::kObjectType)
    {
        if (it->value.HasMember(key2))
        {
            it = it->value.FindMember(key2);

            if (it->value.IsString())
            {
                return it->value.GetString();
            }
        }
    }

    LOGERRORF("Can't find value for \"%s\" \"%s\"", key1, key2);

    return nullptr;
}


pchar ConfigurationFile::GetStringValue(pchar key1, pchar key2, pchar key3)
{
    CHECK_ON_VALID_STRING;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key1);

    if (it->value.GetType() == rapidjson::Type::kObjectType)
    {
        it = it->value.FindMember(key2);

        if (it->value.GetType() == rapidjson::Type::kObjectType)
        {
            if (it->value.HasMember(key3))
            {
                it = it->value.FindMember(key3);

                if (it->value.IsString())
                {
                    return it->value.GetString();
                }
            }
        }
    }

    LOGERRORF("Can't find value for \"%s\" \"%s\" \"%s\"", key1, key2, key3);

    return nullptr;
}


pchar ConfigurationFile::GetStringValue(pchar key1, pchar key2, pchar key3, pchar key4)
{
    CHECK_ON_VALID_STRING;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key1);

    if (it->value.GetType() == rapidjson::Type::kObjectType)
    {
        it = it->value.FindMember(key2);

        if (it->value.GetType() == rapidjson::Type::kObjectType)
        {
            if (it->value.HasMember(key3))
            {
                it = it->value.FindMember(key3);

                if (it->value.HasMember(key4))
                {
                    it = it->value.FindMember(key4);

                    if (it->value.IsString())
                    {
                        return it->value.GetString();
                    }
                }
            }
        }
    }

    LOGERRORF("Can't find value for \"%s\" \"%s\" \"%s\" \"%s\"", key1, key2, key3, key4);

    return nullptr;
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


IntVector2 ConfigurationFile::GetIntVector2(pchar /*key1*/, pchar /*key2*/, pchar /*key3*/)
{
    LOGERRORF("%s has not realisation", __FUNCTION__);

    return { 50, 50 };
}


IntVector2 ConfigurationFile::GetIntVector2(pchar /*key1*/, pchar /*key2*/, pchar /*key3*/, pchar /*key4*/)
{
//    LOGERRORF("%s has not realisation", __FUNCTION__);

    ERROR_FUNCTION

    return { 50, 50 };
}


float ConfigurationFile::GetFloat(pchar /*key1*/, pchar /*key2*/)
{
    LOGERRORF("%s has not realisation", __FUNCTION__);

    return 50.0f;
}


void ConfigurationFile::SetInt(pchar /*key*/, int /*value*/)
{
    LOGERRORF("%s has not realisation", __FUNCTION__);
}


void ConfigurationFile::SetInt(pchar /*key1*/, pchar /*key2*/, int /*value*/)
{
    LOGERRORF("%s has not realisation", __FUNCTION__);
}
