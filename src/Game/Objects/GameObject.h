#pragma once


#include "Game/Objects/Units/Tank/Translator.h"
#include "GUI/GuiGame/ContextMenuUnit.h"


class GameObject : public LogicComponent
{
public:

    enum Type
    {
        Unit
    };

    GameObject(Context *context = gContext);

    void SetAutoReloaded(int time) { timeForReload = time; };

    virtual void Update(float timeStep);

    void EnableContextMenu();
    char *GetName();

    Type GetGameObjectType();

    virtual void SetSelected(bool selected);
    bool IsSelected();

protected:
    int timeForReload = 0;
    int timeLastReload = 0;
    unsigned timeLastModified = 0;

    Vector3 deltaPos;
    bool selected = false;
    float deltaRotate = 0.0f;
    float speed = 0.0f;
    Translator translator;
    char* name;
    Type type;
    SharedPtr<ContextMenuUnit> contextMenu;

    void HandleOnMouseDown(StringHash, VariantMap&);

private:
    GameObject& operator=(const GameObject&) {};
};
