// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/GuiGame/TWindowTarget.h"
#include "Scene/Objects/_TGameObjectEvents.h"


WindowTarget::WindowTarget(Context *context) :
    TWindow(context)
{
    SetDefaultStyle(TheCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetFixedSize(WIDTH_WINDOW_TARGET, HEIGHT_WINDOW_TARGET);

    SubscribeToEvent(E_SETTEXTURE, URHO3D_HANDLER(WindowTarget, HandleSetTexture));
}


void WindowTarget::HandleSetTexture(StringHash, VariantMap& eventData)
{
    Texture2D *texture = (Texture2D*)eventData[GameObjectEvent::P_TEXTURE].GetPtr();

    SetTexture(texture);
    SetFullImageRect();
}
