// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "WindowTarget.h"
#include "Game/Objects/GameObjectEvents.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowTarget::WindowTarget(Context *context) :
    WindowRTS(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetFixedSize(WIDTH_WINDOW_TARGET, HEIGHT_WINDOW_TARGET);

    SubscribeToEvent(E_SETTEXTURE, URHO3D_HANDLER(WindowTarget, HandleSetTexture));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void WindowTarget::HandleSetTexture(StringHash, VariantMap& eventData)
{
    Texture2D *texture = (Texture2D*)eventData[GameObjectEvent::P_TEXTURE].GetPtr();

    SetTexture(texture);
    SetFullImageRect();
}
