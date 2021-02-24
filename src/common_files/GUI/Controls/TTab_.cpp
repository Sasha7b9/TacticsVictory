// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/TButtonToggled_.h"
#include "GUI/Controls/TTab_.h"


Tab::Tab(Context *) : 
    TWindow()
{
    buttonTitle = new ButtonToggled();
    SetMovable(false);
}


void Tab::RegisterObject(Context *context)
{
    context->RegisterFactory<Tab>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(TWindow);
}


SharedPtr<Tab> Tab::Create(char *title)
{
    SharedPtr<Tab> tab(new Tab());
    tab->buttonTitle = new ButtonToggled(nullptr, title, 125, 17);
    return tab;
}
