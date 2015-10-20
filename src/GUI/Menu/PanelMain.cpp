#include <stdafx.h>


#include "PanelMain.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Logic/LineTranslator2D.h"


vPanelMain::vPanelMain(Context *context) :
    vWindow(context)
{
    SetName("PanelMain");

    SetFixedSize(SET::PANEL::MAIN::SIZE);

    SetMovable(false);

    IntVector2 posStart = {SET::PANEL::MAP::WIDTH - 1, gGraphics->GetHeight() - SET::PANEL::BOTTOM::HEIGHT - SET::PANEL::MAIN::HEIGHT + 1};
    IntVector2 posFinish = {SET::PANEL::MAP::WIDTH - 1, gGraphics->GetHeight()};

    translator = new vLineTranslator2D(posStart, posFinish, gSet->GetFloat(TV_PANEL_SPEED), vLineTranslator2D::State_PointStart);
}

void vPanelMain::RegisterObject(Context *context)
{
    context->RegisterFactory<vPanelMain>("UI");

    COPY_BASE_ATTRIBUTES(vWindow);
}

void vPanelMain::Update(float dT)
{
    SetPosition(translator->Update(dT));
}

void vPanelMain::Toggle()
{
    translator->Toggle();
}

void vPanelMain::AddTab(SharedPtr<vTab> tab)
{
    static const int x0 = 10;
    static const int y0 = 4;

    int x = x0;

    for(uint i = 0; i < tabs.Size(); i++)
    {
        x += tabs[i]->buttonTitle->GetWidth();
    }

    AddChild(tab->buttonTitle);
    tab->buttonTitle->SetPosition(x, y0);

    if(tabs.Empty())
    {
        tab->buttonTitle->SetChecked(true);
    }

    tabs.Push(tab);

    SubscribeToEvent(tab->buttonTitle, Urho3D::E_TOGGLED, HANDLER(vPanelMain, HandleToggedTitle));

    AddChild(tab);

    tab->SetPosition(0, y0 + tab->buttonTitle->GetHeight() - 1);
    tab->SetFixedSize(GetWidth(), GetHeight() - y0 - tab->buttonTitle->GetHeight() + 1);
}

void vPanelMain::HandleToggedTitle(StringHash, VariantMap &eventData)
{
    vButtonToggled *button = (vButtonToggled*)eventData[Urho3D::Toggled::P_ELEMENT].GetPtr();
    bool state = (bool)eventData[Urho3D::Toggled::P_STATE].GetBool();

    if(state)
    {
        for(auto tab : tabs)
        {
            if(tab->buttonTitle->IsChecked() && button != tab->buttonTitle)
            {
                UnsubscribeFromEvent(tab->buttonTitle, Urho3D::E_TOGGLED);
                tab->buttonTitle->SetChecked(false);
                SubscribeToEvent(tab->buttonTitle, Urho3D::E_TOGGLED, HANDLER(vPanelMain, HandleToggedTitle));
            }
        }
    }
    else
    {
        button->SetChecked(true);
    }
}