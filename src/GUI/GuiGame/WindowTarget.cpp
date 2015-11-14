#include <stdafx.h>


#include "WindowTarget.h"
#include "Game/Objects/GameObjectEvents.h"


WindowTarget::WindowTarget(Context *context) :
    lWindow(context)
{
    SetDefaultStyle(gCache->GetResource<XMLFile>("UI/MainStyle.xml"));
    SetStyle("WindowNoBorder");

    SetFixedSize(SIZE_WINDOW_TARGET + 100, SIZE_WINDOW_TARGET + 100);

    SubscribeToEvent(E_SETTEXTURE, URHO3D_HANDLER(WindowTarget, HandleSetTexture));
}

void WindowTarget::HandleSetTexture(StringHash, VariantMap& eventData)
{
    /*
    Texture2D *texture = (Texture2D*)eventData[GameObjectEvent::P_TEXTURE].GetPtr();

    uint *buffer = new uint[SIZE_WINDOW_TARGET * SIZE_WINDOW_TARGET];

    texture->GetData(0, buffer);

    size_t size = sizeof(uint);

    uint data = buffer[0];

    uint width = texture->GetWidth();
    uint height = texture->GetHeight();

    for(uint i = 0; i < SIZE_WINDOW_TARGET * SIZE_WINDOW_TARGET; i++)
    {
        if(buffer[0] != data)
        {
            data = data;
        }
    }

    SetTexture(texture);
    SetFullImageRect();

    SetPosition(0, 0);

    

    SAFE_DELETE(buffer);
    */
}
