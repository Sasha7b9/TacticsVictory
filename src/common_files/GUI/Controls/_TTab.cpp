// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


Tab::Tab(Context *) : 
    WindowTV()
{
    buttonTitle = new ButtonToggled();
    SetMovable(false);
}


void Tab::RegisterObject(Context *context)
{
    context->RegisterFactory<Tab>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowTV);
}


SharedPtr<Tab> Tab::Create(char *title)
{
    SharedPtr<Tab> tab(new Tab());
    tab->buttonTitle = new ButtonToggled(nullptr, title, 125, 17);
    return tab;
}
