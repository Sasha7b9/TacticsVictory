#pragma once


#include "GUI/Elements/Window.h"


class GameObject;


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
};