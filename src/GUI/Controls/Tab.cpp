// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Tab.h"
#include "ButtonToggled.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Tab::Tab(Context *) : 
    WindowRTS()
{
    buttonTitle = new ButtonToggled(gContext);
    SetMovable(false);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Tab::RegisterObject(Context *context)
{
    context->RegisterFactory<Tab>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowRTS);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
SharedPtr<Tab> Tab::Create(char *title)
{
    SharedPtr<Tab> tab(new Tab(gContext));
    tab->buttonTitle = new ButtonToggled(nullptr, title, 125, 17);
    return tab;
}
