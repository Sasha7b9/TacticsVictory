#include <stdafx.h>


#include "UnitObject.h"
#include "Game/Objects/GameObjectEvents.h"


bool UnitObject::viewTargetView = false;


UnitObject::UnitObject(Context *context) :
    GameObject(context)
{
    Node* nodeCameraTarget = gScene->CreateChild("CameraTarget");
    nodeCameraTarget->Pitch(180.0f);
    cameraTarget = nodeCameraTarget->CreateComponent<Camera>();
    cameraTarget->SetNearClip(0.5f);
    cameraTarget->SetFarClip(100.0f);

    renderTexture = new Texture2D(gContext);
    renderTexture->SetSize(WIDTH_WINDOW_TARGET, HEIGHT_WINDOW_TARGET, Graphics::GetRGBFormat(), Urho3D::TEXTURE_RENDERTARGET);
    renderTexture->SetFilterMode(Urho3D::FILTER_DEFAULT);

    renderSurface = renderTexture->GetRenderSurface();
    SharedPtr<Viewport> viewport(new Viewport(gContext, gScene, cameraTarget));
    renderSurface->SetViewport(0, viewport);
}

void UnitObject::SetViewTargetView(bool view)
{
    viewTargetView = view;
}

void UnitObject::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    cameraTarget->GetNode()->SetPosition(GetNode()->GetPosition() + Vector3(0.0f, 0.2f, 0.0f));
    cameraTarget->GetNode()->SetRotation(GetNode()->GetRotation());

    VariantMap eventData = GetEventDataMap();
    eventData[GameObjectEvent::P_TEXTURE] = renderTexture;
    SendEvent(E_SETTEXTURE, eventData);
}

void UnitObject::SetSelected(bool selected)
{
    GameObject::SetSelected(selected);

    if(selected && viewTargetView)
    {
        renderSurface->SetUpdateMode(Urho3D::SURFACE_UPDATEALWAYS);
        SubscribeToEvent(Urho3D::E_POSTRENDERUPDATE, URHO3D_HANDLER(UnitObject, HandlePostRenderUpdate));
    }
    else
    {
        renderSurface->SetUpdateMode(Urho3D::SURFACE_MANUALUPDATE);
        UnsubscribeFromEvent(Urho3D::E_POSTRENDERUPDATE);
    }
}
