#pragma once


class Tank : public LogicComponent
{
    OBJECT(Tank);

public:
    enum Type
    {
        Small,
        T_34_76
    };

    Tank(UContext *context = gContext);

    static void RegisterObject(UContext* context = gContext);

    void Init(Type type);
    void SetPosition(const Vector3& pos);
    Vector3 GetPosition();

private:
    Tank& operator=(const Tank&) {};

    void LoadFromFile();
    void Normalize();



    struct TankStruct
    {
        TankStruct(Type type_ = Small, char* fileName_ = 0) : type(type_), fileName(fileName_) {};
        Type type;
        char *fileName;
    };

    struct Key
    {
        Key(Type type_ = Small) : type(type_) {};
        Type type;

        unsigned ToHash() const { return (uint)type; };

        bool operator==(const Key& rhs) const
        {
            return type == rhs.type;
        }
    };

    Type type;

    static HashMap<Key, TankStruct> parameters;

    SharedPtr<StaticModel> modelObject;
    Vector3 deltaPos;
};
