// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/TButtonToggled_.h"
#include "GUI/Controls/TTab_.h"
#include "GUI/Panels/TPanelMain.h"
#include "Utils/Settings.h"


PanelMain::PanelMain(Context *context) :
    TWindow(context)
{
    SetName("PanelMain");

    SetFixedSize(SET::PANEL::MAIN::SIZE);

    SetMovable(false);

    IntVector2 posStart = {SET::PANEL::MAP::WIDTH - 1, TheGraphics->GetHeight() - SET::PANEL::BOTTOM::HEIGHT - SET::PANEL::MAIN::HEIGHT + 1};
    IntVector2 posFinish = {SET::PANEL::MAP::WIDTH - 1, TheGraphics->GetHeight()};

    translator = new LineTranslator2D(posStart, posFinish, TheSet->GetFloat(TV_PANEL_SPEED), LineTranslator2D::State_PointStart);
}


void PanelMain::RegisterObject(Context *context)
{
    context->RegisterFactory<PanelMain>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(TWindow);
}


void PanelMain::Update(float dT)
{
    SetPosition(translator->Update(dT));
}


void PanelMain::AddTab(SharedPtr<Tab> tab)
{
    static const int x0 = 10;
    static const int y0 = 4; //-V112

    int x = x0;

    for(uint i = 0; i < tabs.Size(); i++)
    {
        x += tabs[i]->buttonTitle->GetWidth();
    }

    ButtonToggled *btnTitle = tab->buttonTitle;
    AddChild(btnTitle);
    btnTitle->SetPosition(x, y0);

    if(tabs.Empty())
    {
        btnTitle->SetChecked(true);
        currentTab = tab;
        AddChild(tab);
    }

    tabs.Push(tab);

    SubscribeToEvent(btnTitle, E_TOGGLED, URHO3D_HANDLER(PanelMain, HandleToggedTitle));

    tab->SetPosition(0, y0 + btnTitle->GetHeight() - 1);
    tab->SetFixedSize(GetWidth(), GetHeight() - y0 - btnTitle->GetHeight() + 1);
}


void PanelMain::HandleToggedTitle(StringHash, VariantMap &eventData)
{
    ButtonToggled *button = dynamic_cast<ButtonToggled*>(eventData[Toggled::P_ELEMENT].GetPtr());
    bool state = eventData[Toggled::P_STATE].GetBool();

    if(state)
    {
        for(Tab *tab : tabs)
        {
            if(tab->buttonTitle->IsChecked() && button != tab->buttonTitle)
            {
                UnsubscribeFromEvent(tab->buttonTitle, E_TOGGLED);
                tab->buttonTitle->SetChecked(false);
                SubscribeToEvent(tab->buttonTitle, E_TOGGLED, URHO3D_HANDLER(PanelMain, HandleToggedTitle));
            }
            else
            {
                RemoveChild(currentTab);
                for (Tab *pTab : tabs)
                {
                    if (pTab->buttonTitle == button)
                    {
                        AddChild(pTab);
                        currentTab = pTab;
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
