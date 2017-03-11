#pragma once
#include "GUI/Controls/WindowRTS.h"
#include "GUI/Controls/Label.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameObject;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ContextMenuUnit : public WindowRTS
{
    URHO3D_OBJECT(ContextMenuUnit, WindowRTS);

public:
    ContextMenuUnit(Context *context = gContext);
    void Create(GameObject *object);

private:
    SharedPtr<Label> title;
    GameObject *object = nullptr; //-V122

    void CreateForUnit();
    void HandleToggledFiedView(StringHash, VariantMap&);

    DEFAULT_MEMBERS(ContextMenuUnit);
};
