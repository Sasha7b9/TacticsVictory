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

    pchar GetString(pchar key);
    pchar GetString(pchar key1, pchar key2);
    pchar GetString(pchar key1, pchar key2, pchar key3);
    pchar GetString(pchar key1, pchar key2, pchar key3, pchar key4);

    bool GetVectorStrings(pchar key, std::vector<std::string> &strings);

    int GetInt(pchar key);
    int GetInt(pchar key1, pchar key2);
    int GetInt(pchar key1, pchar key2, pchar key3);
    int GetInt(pchar key1, pchar key2, pchar key3, pchar key4);

    IntVector2 GetIntVector2(pchar key1, pchar key2, pchar key3);
    IntVector2 GetIntVector2(pchar key1, pchar key2, pchar key3, pchar key4);

    float GetFloat(pchar key1, pchar key2);

    void SetInt(pchar key, int value);
    void SetInt(pchar key1, pchar key2, int value);

    bool IsValid() const { return isValid; }

private:

    bool isValid = false;

    rapidjson::Document *document = nullptr;

    rapidjson::Value::ConstMemberIterator FindMember(pchar key1, pchar key2, pchar key3, pchar key4);
};
