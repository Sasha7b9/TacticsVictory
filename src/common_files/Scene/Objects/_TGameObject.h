// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#ifdef CLIENT

class ContextMenuUnit;

#endif

class GameObject;
class Translator;
struct Coord;


struct ReloaderComponentGameObject
{
    virtual ~ReloaderComponentGameObject() {}
    virtual void Init(int time) { timeForReload = time; }
    virtual void Execute(GameObject &object) = 0;
    int timeForReload = 0;
    int timeLastReload = 0;
    uint timeLastModified = 0;
};

struct SelectorComponentGameObject
{
    virtual ~SelectorComponentGameObject() { }

    virtual void Init(GameObject *object) { keeper = object; }

    virtual void Execute(GameObject &object) { UNUSED(object); }

    virtual void SetSelected(bool _selected) { selected = _selected; }

    bool IsSelected() { return selected; };

    bool selected = false;

    GameObject *keeper = nullptr;
};


struct PhysicsComponentGameObject
{
    virtual ~PhysicsComponentGameObject() {}

    virtual void Init(GameObject *object) { keeper = object; };

    Vector3 GetPosition();

    void SetPosition(const Vector3 &pos);

    GameObject *keeper = nullptr;

    Vector3 deltaPos = Vector3::ZERO;

    float deltaRotate = 0.0f;

    void SetCoord(const Coord &coord);
};


class GameObject : public LogicComponent
{
friend struct PhysicsComponentGameObject;

public:

    struct Type { enum E {
        None,
        Unit
    }; };

    GameObject(Context *context = TheContext);
    virtual ~GameObject();

    virtual void Update(float timeStep) = 0;

    char *GetName();

    Type::E GetGameObjectType();

    SelectorComponentGameObject *selector = nullptr;

    PhysicsComponentGameObject *physics = nullptr;

protected:

    ReloaderComponentGameObject *reloader = nullptr;

    uint id = 0;

    float speed = 0.0f;
    SharedPtr<Translator> translator;
    char* name = nullptr;
    Type::E type = Type::None;
    SharedPtr<StaticModel> modelObject;

    void Normalize(float k = 1.0f);

    void SetAutoReloaded(int time) { reloader->Init(time); };

private:

#ifdef CLIENT

public:
    void EnableContextMenu();

protected:
    void HandleOnMouseDown(StringHash, VariantMap &);

    SharedPtr<ContextMenuUnit> contextMenu;

#endif
};
