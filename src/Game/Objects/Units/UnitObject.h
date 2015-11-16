#pragma once


#include "Game/Objects/GameObject.h"


class UnitObject : public GameObject
{
public:
    UnitObject(Context *context = gContext);

    static void SetViewTargetView(bool view);

    virtual void SetSelected(bool selected);

protected:
    static bool viewTargetView;

private:
    UnitObject& operator=(const UnitObject&)
    {};

    Camera *cameraTarget = nullptr;         // Camera for determination of visibility of the target.
    SharedPtr<Texture2D> renderTexture;
    SharedPtr<RenderSurface> renderSurface;

    void HandlePostRenderUpdate(StringHash, VariantMap&);
};
