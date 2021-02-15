// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Tab.h"
#include "ButtonToggled.h"



Tab::Tab(Context *) : 
    WindowRTS()
{
    buttonTitle = new ButtonToggled(TheContext);
    SetMovable(false);
}


void Tab::RegisterObject(Context *context)
{
    context->RegisterFactory<Tab>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}


SharedPtr<Tab> Tab::Create(char *title)
{
    SharedPtr<Tab> tab(new Tab(TheContext));
    tab->buttonTitle = new ButtonToggled(nullptr, title, 125, 17);
    return tab;
}
