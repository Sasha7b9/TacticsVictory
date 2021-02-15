/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/_GameObject.h"



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

    DEFAULT_MEMBERS(UnitObject);
};
