// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/_WindowRTS.h"


class GameObject;
class Label;


class ContextMenuUnit : public WindowRTS
{
    URHO3D_OBJECT(ContextMenuUnit, WindowRTS);

public:
    ContextMenuUnit(Context *context = TheContext);
    void Create(GameObject *object);

private:
    SharedPtr<Label> title;
    GameObject *object = nullptr; //-V122

    void CreateForUnit();
    void HandleToggledFiedView(StringHash, VariantMap&);

    DEFAULT_MEMBERS(ContextMenuUnit);
};
