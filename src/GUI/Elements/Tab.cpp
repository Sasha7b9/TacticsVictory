#include <stdafx.h>


#include "Tab.h"


tvTab::tvTab(Context *context) : 
    tvWindow(context)
{
    buttonTitle = new tvButtonToggled(gContext);
    //SetMovable(false);
}

void tvTab::RegisterObject(Context *context)
{
    context->RegisterFactory<tvTab>("UI");

    COPY_BASE_ATTRIBUTES(tvWindow);
}

SharedPtr<tvTab> tvTab::Create(UIElement *uilelemnt, char *title)
{
    SharedPtr<tvTab> tab(uilelemnt->CreateChild<tvTab>());

    tab->buttonTitle = uilelemnt->CreateChild<tvButtonToggled>();
    tab->buttonTitle->SetText(title);

    return tab;
}