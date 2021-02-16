/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/Units/Tank/_Translator.h"
#include "Scene/Objects/Units/UnitObject.h"

class RocketLauncher;

#ifdef CLIENT

class WaveAlgorithm;

#endif

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
    
    Tank(Context *context = TheContext);
    virtual ~Tank();
    static void RegisterObject(Context* context = TheContext);
    static void RegisterInAS();
    virtual void Update(float timeStep);
    static SharedPtr<Tank> Create(TypeTank type, uint _id_ = 0);
    void SetCoord(const Coord& coord);
    void SetPath(const PODVector<Coord> &path);
    // rotation = [0...359.999999f]
    void SetRotation(float rotation);
    float GetRotation();
    Vector3 GetSpeed() { return translator->speed; }
    Node* GetNode();
    static PODVector<Tank*>& GetAll();
    static Tank* GetByID(uint id);
    void DrawMessage();

private:
    bool inProcessFindPath = false;
    TypeTank typeTank;
    static PODVector<Tank*> allTanks;

    void LoadFromFile();
    void Init(TypeTank typeTank, uint _id_);

    struct TankStruct
    {
        TankStruct(TypeTank type_ = Small, char* fileName_ = 0) : type(type_), fileName(fileName_) {};
        TypeTank type;
        char *fileName; //-V122
    };

    struct Key
    {
        Key(TypeTank type_ = Small) : type(type_) {};
        TypeTank type;

        unsigned ToHash() const { return static_cast<uint>(type); };

        bool operator==(const Key& rhs) const
        {
            return type == rhs.type;
        }
    };
    static HashMap<Key, TankStruct> parameters;
    SharedPtr<RocketLauncher> rocketLauncher;

    void HandleAmmoHit(StringHash, VariantMap&);

#ifdef CLIENT

    SharedPtr<WaveAlgorithm> pathFinder;

#endif
};
