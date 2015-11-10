#include <stdafx.h>


#include "PanelMain.h"
#include "GUI/Elements/Tab.h"
#include "GUI/Elements/ButtonToggled.h"
#include "GUI/Logic/LineTranslator2D.h"


PanelMain::PanelMain(Context *context) :
    lWindow(context)
{
    SetName("PanelMain");

    SetFixedSize(SET::PANEL::MAIN::SIZE);

    SetMovable(false);

    IntVector2 posStart = {SET::PANEL::MAP::WIDTH - 1, gGraphics->GetHeight() - SET::PANEL::BOTTOM::HEIGHT - SET::PANEL::MAIN::HEIGHT + 1};
    IntVector2 posFinish = {SET::PANEL::MAP::WIDTH - 1, gGraphics->GetHeight()};

    translator = new LineTranslator2D(posStart, posFinish, gSet->GetFloat(TV_PANEL_SPEED), LineTranslator2D::State_PointStart);
}

void PanelMain::RegisterObject(Context *context)
{
    context->RegisterFactory<PanelMain>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(lWindow);
}

void PanelMain::Update(float dT)
{
    SetPosition(translator->Update(dT));
}

void PanelMain::AddTab(SharedPtr<Tab> tab)
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
        currentTab = tab;
        AddChild(tab);
    }

    tabs.Push(tab);

    SubscribeToEvent(tab->buttonTitle, Urho3D::E_TOGGLED, URHO3D_HANDLER(PanelMain, HandleToggedTitle));

    tab->SetPosition(0, y0 + tab->buttonTitle->GetHeight() - 1);
    tab->SetFixedSize(GetWidth(), GetHeight() - y0 - tab->buttonTitle->GetHeight() + 1);
}

void PanelMain::HandleToggedTitle(StringHash, VariantMap &eventData)
{
    ButtonToggled *button = (ButtonToggled*)eventData[Urho3D::Toggled::P_ELEMENT].GetPtr();
    bool state = (bool)eventData[Urho3D::Toggled::P_STATE].GetBool();

    if(state)
    {
        for(auto tab : tabs)
        {
            if(tab->buttonTitle->IsChecked() && button != tab->buttonTitle)
            {
                UnsubscribeFromEvent(tab->buttonTitle, Urho3D::E_TOGGLED);
                tab->buttonTitle->SetChecked(false);
                SubscribeToEvent(tab->buttonTitle, Urho3D::E_TOGGLED, URHO3D_HANDLER(PanelMain, HandleToggedTitle));
            }
            else
            {
                RemoveChild(currentTab);
                for (auto tab : tabs)
                {
                    if (tab->buttonTitle == button)
                    {
                        AddChild(tab);
                        currentTab = tab;
                    }
                }
            }
        }
    }
    else
    {
        button->SetChecked(true);
    }
}