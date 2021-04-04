// Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
    ����� ������������ ������ ���������� �� json-������
*/


class ConfigurationFile
{
public:

    virtual ~ConfigurationFile() { Unload(); }

    bool Load(pchar name);

    void Unload();

    int        GetInt(pchar key1, pchar key2 = "", pchar key3 = "", pchar key4 = "");
    pchar      GetString(pchar key1, pchar key2 = "", pchar key3 = "", pchar key4 = "");
    bool       GetVectorStrings(pchar key, std::vector<std::string> &strings);
    IntVector2 GetIntVector2(pchar key1, pchar key2 = "", pchar key3 = "", pchar key4 = "");
    float      GetFloat(pchar key1, pchar key2 = "");

    void SetInt(int value, pchar key);
    void SetInt(int value, pchar key1, pchar key2);

    bool IsValid() const { return isValid; }

private:

    bool isValid = false;

    rapidjson::Document *document = nullptr;

    std::string file_name;

    rapidjson::Value::ConstMemberIterator FindMember(pchar key1, pchar key2 = "", pchar key3 = "", pchar key4 = "");
};
