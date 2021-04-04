// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
    Файлы конфигурации читают информацию из json-файлов
*/


class ConfigurationFile
{
public:

    virtual ~ConfigurationFile() { Unload(); }

    bool Load(pchar name);

    void Unload();

    int        GetInt(pchar key1, pchar key2 = nullptr, pchar key3 = nullptr, pchar key4 = nullptr);
    pchar      GetString(pchar key1, pchar key2 = nullptr, pchar key3 = nullptr, pchar key4 = nullptr);
    bool       GetVectorStrings(pchar key, std::vector<std::string> &strings);
    IntVector2 GetIntVector2(pchar key1, pchar key2 = nullptr, pchar key3 = nullptr, pchar key4 = nullptr);
    float      GetFloat(pchar key1, pchar key2 = nullptr);

    void SetInt(pchar key, int value);
    void SetInt(pchar key1, pchar key2, int value);

    bool IsValid() const { return isValid; }

private:

    bool isValid = false;

    rapidjson::Document *document = nullptr;

    rapidjson::Value::ConstMemberIterator FindMember(pchar key1, pchar key2 = nullptr, pchar key3 = nullptr,
        pchar key4 = nullptr);
};
