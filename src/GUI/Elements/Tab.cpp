#include <stdafx.h>


#include "Tab.h"
#include "GUI/Elements/ButtonToggled.h"


vTab::vTab(Context *context) : 
    vWindow(context)
{
    buttonTitle = new vButtonToggled(gContext);
    //SetMovable(false);
}

void vTab::RegisterObject(Context *context)
{
    context->RegisterFactory<vTab>("UI");

    COPY_BASE_ATTRIBUTES(vWindow);
}

SharedPtr<vTab> vTab::Create(UIElement *uilelemnt, char *title)
{
    SharedPtr<vTab> tab(uilelemnt->CreateChild<vTab>());

    tab->buttonTitle = uilelemnt->CreateChild<vButtonToggled>();
    tab->buttonTitle->SetText(title);

    return tab;
}