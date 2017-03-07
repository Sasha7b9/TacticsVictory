#pragma once
#include "Game/Path/WaveAlgorithm.h"
#include "Game/Objects/Units/Tank/Translator.h"
#include "Game/Objects/Units/UnitObject.h"
#include "Game/Objects/Weapons/RocketLauncher/RocketLauncher.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Tank : public UnitObject
{
    URHO3D_OBJECT(Tank, UnitObject);

    friend class Translator;

public:
    enum TypeTank
    {
        Small,
        T_34_76
    };

    Tank(Context *context = gContext);
    virtual ~Tank();
    static void RegisterObject(Context* context = gContext);
    virtual void Update(float timeStep);
    static SharedPtr<Tank> Create(TypeTank type, uint _id_ = 0);
    void SetCoord(const Coord& coord);
    void SetPath(PODVector<Coord> &path);
    // rotation = [0...359.999999f]
    void SetRotation(float rotation);
    float GetRotation();
    Vector3 GetSpeed() { return translator.speed; }
    Node* GetNode();

private:
    void LoadFromFile();
    void Init(TypeTank typeTank, uint _id_);

    TypeTank typeTank;

    struct TankStruct
    {
        TankStruct(TypeTank type_ = Small, char* fileName_ = 0) : type(type_), fileName(fileName_) {};
        TypeTank type;
        char *fileName;
    };

    struct Key
    {
        Key(TypeTank type_ = Small) : type(type_) {};
        TypeTank type;

        unsigned ToHash() const { return (uint)type; };

        bool operator==(const Key& rhs) const
        {
            return type == rhs.type;
        }
    };

    static HashMap<Key, TankStruct> parameters;

    WaveAlgorithm pathFinder;

    bool inProcessFindPath = false;

    void HandleAmmoHit(StringHash, VariantMap&);

    SharedPtr<RocketLauncher> rocketLauncher;

    DEFAULT_MEMBERS(Tank);
};
