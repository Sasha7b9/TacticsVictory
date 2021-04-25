// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"


ButtonSwitch::ButtonSwitch(Context *context) :
    ButtonT(context)
{

}


ButtonSwitch::ButtonSwitch(UIElement *uielement, pchar text, int width, int height) :
    ButtonT(uielement, text, width, height)
{
    items.Push(text);

    SubscribeToEvent(this, E_RELEASED, URHO3D_HANDLER(ButtonSwitch, HandlerButtonRelease));
}


void ButtonSwitch::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<ButtonSwitch>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(ButtonT);
}


void ButtonSwitch::AddState(char *item)
{
    items.Push(item);
}


void ButtonSwitch::HandlerButtonRelease(StringHash, VariantMap&)
{
    state++;
    if (state == items.Size())
    {
        state = 0;
    }

    SetText(items[state]);
}


uint ButtonSwitch::GetState()
{
    return state;
}


void ButtonSwitch::SetState(uint state_)
{
    state = state_;
    SetText(items[state]);
}
