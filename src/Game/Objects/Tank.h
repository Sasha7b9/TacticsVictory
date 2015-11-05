#pragma once


#include "Game/Path/WaveAlgorithm.h"
#include "Game/Logic/Translator.h"


class Tank : public LogicComponent
{
    OBJECT(Tank);

public:
    enum Type
    {
        Small,
        T_34_76
    };

    Tank(Context *context = gContext);

    static void RegisterObject(Context* context = gContext);

    virtual void Update(float timeStep);

    void Init(Type type);
    void SetPosition(const Vector3& pos);
    Vector3 GetPosition();

    void SetSelected(bool selected);
    bool IsSelected();

    void SetPath(PODVector<Coord> path);

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

    static UHashMap<Key, TankStruct> parameters;

    SharedPtr<StaticModel> modelObject;
    Vector3 deltaPos;
    bool selected = false;
    PODVector<Coord> path;

    bool inMovingState = false;
    float speed = 50.0f;
    Translator translator;
};
