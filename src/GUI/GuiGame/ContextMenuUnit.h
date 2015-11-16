#pragma once


#include "GUI/Elements/Window.h"


class GameObject;


class ContextMenuUnit : public lWindow
{
    URHO3D_OBJECT(ContextMenuUnit, lWindow);

public:
    ContextMenuUnit(Context *context = gContext);

    void Create(GameObject *object);

private:
    SharedPtr<Label> title;
    GameObject *object = nullptr;

    void CreateForUnit();

    void HandleToggledFiedView(StringHash, VariantMap&);
};