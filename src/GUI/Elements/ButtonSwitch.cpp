#include <stdafx.h>


#include "ButtonSwitch.h"


lButtonSwitch::lButtonSwitch(Context *context) :
    lButton(context)
{

}

lButtonSwitch::lButtonSwitch(UIElement *uielement, char *text, int width, int height) :
    lButton(uielement, text, width, height)
{
    items.Push(text);

    SubscribeToEvent(this, Urho3D::E_RELEASED, HANDLER(lButtonSwitch, HandleButtonRelease));
}

void lButtonSwitch::RegisterObject(Context *context)
{
    context->RegisterFactory<lButtonSwitch>("UI");

    COPY_BASE_ATTRIBUTES(lButton);
}

void lButtonSwitch::AddState(char *item)
{
    items.Push(item);
}

void lButtonSwitch::HandleButtonRelease(StringHash, VariantMap&)
{
    state++;
    if (state == items.Size())
    {
        state = 0;
    }

    SetText(items[state]);
}

uint lButtonSwitch::GetState()
{
    return state;
}

void lButtonSwitch::SetState(uint state_)
{
    state = state_;
    SetText(items[state]);
}
