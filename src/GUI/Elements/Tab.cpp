#include <stdafx.h>


#include "Tab.h"
#include "GUI/Elements/ButtonToggled.h"


lTab::lTab(Context *context) : 
    lWindow(context)
{
    buttonTitle = new lButtonToggled(gContext);
    //SetMovable(false);
}

void lTab::RegisterObject(Context *context)
{
    context->RegisterFactory<lTab>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}

SharedPtr<lTab> lTab::Create(UIElement *uilelemnt, char *title)
{
    SharedPtr<lTab> tab(uilelemnt->CreateChild<lTab>());

    tab->buttonTitle = uilelemnt->CreateChild<lButtonToggled>();
    tab->buttonTitle->SetText(title);

    return tab;
}