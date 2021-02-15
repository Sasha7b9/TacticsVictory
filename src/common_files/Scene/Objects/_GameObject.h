#pragma once
#include "Scene/Objects/Units/Tank/_Translator.h"
#include "GUI/GuiGame/ContextMenuUnit.h"



class GameObject : public LogicComponent
{
public:

    enum Type
    {
        None,
        Unit
    };

    GameObject(Context *context = TheContext);
    virtual ~GameObject();
    void SetAutoReloaded(int time) { timeForReload = time; };
    virtual void Update(float timeStep);
    void EnableContextMenu();
    char *GetName();
    Type GetGameObjectType();
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
    char* name = nullptr; //-V122
    Type type = None;
    SharedPtr<ContextMenuUnit> contextMenu;
    SharedPtr<StaticModel> modelObject;

    void SetPosition(const Vector3& pos);
    void Normalize(float k = 1.0f);
    void HandleOnMouseDown(StringHash, VariantMap&);

private:

    DEFAULT_MEMBERS(GameObject);
};
