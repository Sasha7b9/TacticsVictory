// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Tab_.h"
#include "GUI/Controls/Buttons/ButtonToggled_.h"


Tab::Tab(Context *context) : 
    WindowT(context)
{
    buttonTitle = new ButtonToggled(context);
    SetMovable(false);
}


void Tab::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<Tab>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowT);
}


SharedPtr<Tab> Tab::Create(char *title)
{
    SharedPtr<Tab> tab(new Tab(TheContext));
    tab->buttonTitle = new ButtonToggled(nullptr, title, 125, 17);
    return tab;
}
