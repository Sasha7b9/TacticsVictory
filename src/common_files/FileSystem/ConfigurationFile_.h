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

    pchar GetStringValue(pchar key);

    pchar GetStringValue(pchar key1, pchar key2);

    pchar GetStringValue(pchar key1, pchar key2, pchar key3);

    bool GetVectorStrings(pchar key, std::vector<std::string> &strings);

    int GetIntValue(pchar key);

    int GetIntValue(pchar key1, pchar key2);

    bool IsValid() const { return isValid; }

private:

    bool isValid = false;

    rapidjson::Document *document = nullptr; //-V122
};
