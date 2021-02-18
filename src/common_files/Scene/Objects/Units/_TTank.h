/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/Units/Logic/_TTranslator.h"
#include "Scene/Objects/Units/_TUnitObject.h"

class RocketLauncher;

#ifdef CLIENT

class WaveAlgorithm;

#endif

class Tank : public UnitObject
{
    URHO3D_OBJECT(Tank, UnitObject);

    friend class Translator;

public:

    struct Type { enum E {
        Small,
        T_34_76
    }; };
  
    Tank(Context *context = TheContext);
    virtual ~Tank() {};

    static void RegisterObject(Context* context = TheContext);

    static SharedPtr<Tank> Create(Type::E type, uint row, uint col, uint _id_ = 0);

    virtual void Update(float timeStep);

    void SetCoord(const Coord& coord);
    void SetPath(const PODVector<Coord> &path);
    // rotation = [0...359.999999f]
    void SetRotation(float rotation);
    float GetRotation();
    Vector3 GetSpeed() { return translator->speed; }
    Node* GetNode();
    static PODVector<Tank*>& GetAll();
    static Tank* GetByID(uint id);

private:
    bool inProcessFindPath = false;
    Type::E typeTank;
    static PODVector<Tank*> allTanks;

    void LoadFromFile();
    void Init(Type::E typeTank, uint _id_);
    static void RegisterInAS();

    struct TankStruct
    {
        TankStruct(Type::E type_ = Type::Small, char* fileName_ = 0) : type(type_), fileName(fileName_) {};
        Type::E type;
        char *fileName; //-V122
    };

    struct Key
    {
        Key(Type::E type_ = Type::Small) : type(type_) {};
        Type::E type;

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
