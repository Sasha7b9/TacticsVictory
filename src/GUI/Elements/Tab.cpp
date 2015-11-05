#include <stdafx.h>


#include "Tab.h"
#include "GUI/Elements/ButtonToggled.h"


Tab::Tab(Context *) : 
    lWindow()
{
    buttonTitle = new ButtonToggled(gContext);
    SetMovable(false);
}

void Tab::RegisterObject(Context *context)
{
    context->RegisterFactory<Tab>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}

SharedPtr<Tab> Tab::Create(char *title)
{
    SharedPtr<Tab> tab(new Tab(gContext));
    tab->buttonTitle = new ButtonToggled(gContext);
    tab->buttonTitle->SetText(title);
    return tab;
}