#pragma once


#include "Game/Path/WaveAlgorithm.h"
#include "Game/Objects/Units/Tank/Translator.h"
#include "Game/Objects/GameObject.h"


class Tank : public GameObject
{
    OBJECT(Tank);

    friend class Translator;

public:
    enum Type
    {
        Small,
        T_34_76
    };

    Tank(Context *context = gContext);

    static void RegisterObject(Context* context = gContext);

    virtual void Update(float timeStep);

    static SharedPtr<Tank> Create(Type type);

    Vector3 GetPosition();
    void SetCoord(const Coord& coord);

    void SetSelected(bool selected);
    bool IsSelected();

    void SetPath(PODVector<Coord> &path);

    // rotation = [0...359.999999f]
    void SetRotation(float rotation);
    float GetRotation();

private:
    Tank& operator=(const Tank&) {};

    void LoadFromFile();
    void Normalize();
    void SetPosition(const Vector3& pos);
    void Init(Type type);

    Type type;

    SharedPtr<StaticModel> modelObject;

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

    static HashMap<Key, TankStruct> parameters;

    WaveAlgorithm pathFinder;

    bool inProcessFindPath = false;

    float radiusDetect = 20.0f;

    float timeRechargeWeapon = 10.0f;  // In sec
    float timeElapsedAfterShoot = 11.0f;

    void HandleCollision(StringHash, VariantMap&);
};
