#pragma once
#include "GUI/Elements/Window.h"
#include "GUI/Elements/Label.h"


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
    GameObject *object = nullptr;

    void CreateForUnit();
    void HandleToggledFiedView(StringHash, VariantMap&);

    CONSTRUCTORS(ContextMenuUnit, WindowRTS);
};
