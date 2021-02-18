// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


#ifdef CLIENT

class ContextMenuUnit;

#endif

class Translator;
struct Coord;


class GameObject : public LogicComponent
{
public:

    struct Type { enum E {
        None,
        Unit
    }; };

    GameObject(Context *context = TheContext);
    virtual ~GameObject();

    void SetAutoReloaded(int time) { timeForReload = time; };
    virtual void Update(float timeStep);
    char *GetName();
    Type::E GetGameObjectType();
    virtual void SetSelected(bool selected);
    bool IsSelected();
    Vector3 GetPosition();
    Node *GetNode();
    void SetCoord(const Coord& coord);
    uint GetID();

protected:
    uint id = 0;
    int timeForReload = 0;
    int timeLastReload = 0;
    unsigned timeLastModified = 0;
    Vector3 deltaPos = Vector3::ZERO;
    bool selected = false;
    float deltaRotate = 0.0f;
    float speed = 0.0f;
    SharedPtr<Translator> translator;
    char* name = nullptr;
    Type::E type = Type::None;
    SharedPtr<StaticModel> modelObject;

    void SetPosition(const Vector3& pos);
    void Normalize(float k = 1.0f);

#ifdef CLIENT

public:
    void EnableContextMenu();

protected:
    void HandleOnMouseDown(StringHash, VariantMap &);

    SharedPtr<ContextMenuUnit> contextMenu;

#endif
};
