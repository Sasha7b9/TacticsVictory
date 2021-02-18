/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#ifdef CLIENT
#include "Game/Path/TWaveAlgorithm.h"
#endif
#include "GUI/GuiGame/TContextMenuUnit.h"
#include "Scene/Objects/Units/Logic/_TTranslator.h"
#include "Scene/Objects/Units/_TUnitObject.h"
#include "Scene/Objects/Weapons/_TWeaponObject.h"


struct ReloaderComponentTank : public ReloaderComponentGameObject
{
    virtual void Init(int time) { ReloaderComponentGameObject::Init(time); }
    virtual void Execute(GameObject &object) override;
};


struct GUIComponentTank : public GUIComponentGameObject
{
    GUIComponentTank(GameObject *object) : GUIComponentGameObject()
    {
        keeper = object;
    }

    virtual void EnableContextMenu() override;

    void HandleOnMouseDown(StringHash, VariantMap &);

    SharedPtr<ContextMenuUnit> contextMenu;
};


class Tank : public UnitObject
{
friend struct ReloaderComponentTank;

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

    void SetPath(const PODVector<Coord> &path);
    // rotation = [0...359.999999f]
    void SetRotation(float rotation);
    float GetRotation();
    Vector3 GetSpeed() { return physics->translator->speed; }
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
