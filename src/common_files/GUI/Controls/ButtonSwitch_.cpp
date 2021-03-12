// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/ButtonSwitch_.h"


ButtonSwitch::ButtonSwitch(Context *context) :
    TButton(context)
{

}


ButtonSwitch::ButtonSwitch(UIElement *uielement, char *text, int width, int height) :
    TButton(uielement, text, width, height)
{
    items.Push(text);

    SubscribeToEvent(this, E_RELEASED, URHO3D_HANDLER(ButtonSwitch, HandleButtonRelease));
}


void ButtonSwitch::RegisterComponent()
{
    TheContext->RegisterFactory<ButtonSwitch>("UI");

    Context *context = TheContext;

    URHO3D_COPY_BASE_ATTRIBUTES(TButton);
}


void ButtonSwitch::AddState(char *item)
{
    items.Push(item);
}


void ButtonSwitch::HandleButtonRelease(StringHash, VariantMap&)
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
