/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/_TGameObject.h"


class UnitObject : public GameObject
{
public:
    UnitObject(Context *context = TheContext);
    virtual ~UnitObject();
    static void SetViewTargetView(bool view);
    virtual void SetSelected(bool selected);

protected:
    static bool viewTargetView;

private:
    Camera *cameraTarget = nullptr;                         // Камера для вида юнита от первого лица //-V122
    SharedPtr<Texture2D> renderTexture;
    SharedPtr<RenderSurface> renderSurface;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
};


#include "Scene/Objects/Units/_TAirplane.h"
#include "Scene/Objects/Units/_TBomber.h"
#include "Scene/Objects/Units/_TBuilder.h"
#include "Scene/Objects/Units/_THelicopter.h"
#include "Scene/Objects/Units/_TRobot.h"
#include "Scene/Objects/Units/_TSupplierAmmo.h"
#include "Scene/Objects/Units/_TTank.h"
