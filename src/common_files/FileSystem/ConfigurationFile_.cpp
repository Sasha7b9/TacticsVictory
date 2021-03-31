// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


#define CHECK_ON_VALID_STRING   if (!isValid) { LOGERROR("Configuration file is not valid"); return nullptr; }
#define CHECK_ON_VALID_INT      if (!isValid) { LOGERROR("Configuration file is not valid"); return -1; }


bool ConfigurationFile::Load(pchar name) //-V2506
{
    document = new rapidjson::Document(); //-V2511

    FS::File file;
    file.Open((std::string("conf") + FS::delimiter + name).c_str(), __FILE__, __LINE__);

    if (!file.IsOpened())
    {
        LOGERROR("Can't load configuration file %s", name);

        return false;
    }

    std::string buffer;

    file.Read(buffer, file.Size());

    document->Parse(buffer.c_str());

    if (document->HasParseError())
    {
        LOGERROR("Can't parse configuration file %s. Error %d", name, document->GetParseError());

        isValid = false;

        return false;
    }
    
    LOGWRITE("Configuration file %s is parsed", name);

    isValid = true;

    return true;
}


void ConfigurationFile::Unload()
{
    SAFE_DELETE(document);
}


int ConfigurationFile::GetIntValue(pchar key) //-V2506
{
    CHECK_ON_VALID_INT;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key);

    if (it != document->MemberEnd() && it->value.IsInt())
    {
        return it->value.GetInt();
    }

    LOGERROR("Can't find value for \"%s\"", key);

    return -1;
}


int ConfigurationFile::GetIntValue(pchar key1, pchar key2) //-V2506
{
    CHECK_ON_VALID_INT;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key1);

    if (it->value.GetType() == rapidjson::Type::kObjectType)
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

    LOGERROR("Can't find value for \"%s\" \"%s\"", key1, key2);

    return -1;
}


pchar ConfigurationFile::GetStringValue(pchar key) //-V2506
{
    CHECK_ON_VALID_STRING;

    rapidjson::Value::ConstMemberIterator it = document->FindMember(key);

    if (it != document->MemberEnd() && it->value.IsString())
    {
        return it->value.GetString();
    }

    LOGERROR("Can't find value for \"%s\" key", key);

    return nullptr;
}


pchar ConfigurationFile::GetStringValue(pchar key1, pchar key2) //-V2506
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

    LOGERROR("Can't find value for \"%s\" \"%s\"", key1, key2);

    return nullptr;
}


pchar ConfigurationFile::GetStringValue(pchar key1, pchar key2, pchar key3) //-V2506
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

    LOGERROR("Can't find value for \"%s\" \"%s\" \"%s\"", key1, key2, key3);

    return nullptr;
}


bool ConfigurationFile::GetVectorStrings(pchar key, std::vector<std::string> &strings) //-V2506
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
        LOGERROR("Can't load array from key %s", key);
    }

    return strings.size() != 0;
}
