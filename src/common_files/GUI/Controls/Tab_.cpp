// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/ButtonToggled_.h"
#include "GUI/Controls/Tab_.h"


Tab::Tab(Context *) : 
    WindowT()
{
    buttonTitle = new ButtonToggled();
    SetMovable(false);
}


void Tab::RegisterObject(Context *context)
{
    context->RegisterFactory<Tab>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowT);
}


SharedPtr<Tab> Tab::Create(char *title)
{
    SharedPtr<Tab> tab(new Tab());
    tab->buttonTitle = new ButtonToggled(nullptr, title, 125, 17);
    return tab;
}
