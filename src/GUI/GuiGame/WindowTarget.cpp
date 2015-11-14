#include <stdafx.h>


#include "WindowTarget.h"
#include "Game/Objects/GameObjectEvents.h"


WindowTarget::WindowTarget(Context *context) :
    lWindow(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetFixedSize(SIZE_WINDOW_TARGET * 4, SIZE_WINDOW_TARGET * 4);

    SubscribeToEvent(E_SETTEXTURE, URHO3D_HANDLER(WindowTarget, HandleSetTexture));
}

void WindowTarget::HandleSetTexture(StringHash, VariantMap& eventData)
{
    Texture2D *texture = (Texture2D*)eventData[GameObjectEvent::P_TEXTURE].GetPtr();

    SetTexture(texture);
    SetFullImageRect();
}
