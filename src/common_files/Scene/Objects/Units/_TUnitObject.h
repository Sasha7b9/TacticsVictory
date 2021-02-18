/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/_TGameObject.h"


struct SelectorComponentUnitObject : public SelectorComponentGameObject
{
    virtual void SetSelected(bool selected);
};


class UnitObject : public GameObject
{
friend struct SelectorComponentUnitObject;

    URHO3D_OBJECT(UnitObject, GameObject);

public:

    UnitObject(Context *context = TheContext);
    virtual ~UnitObject();
    static void SetViewTargetView(bool view);

protected:
    static bool viewTargetView;

private:
    Camera *cameraTarget = nullptr;                         // Камера для вида юнита от первого лица //-V122
    SharedPtr<Texture2D> renderTexture;
    SharedPtr<RenderSurface> renderSurface;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
};


#include "Scene/Objects/Units/_TAirplane.h"
#include "Scene/Objects/Units/_TTank.h"
