// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Tab_.h"
#include "GUI/Controls/Buttons/ButtonToggled_.h"
#include "GUI/Logic/LineTranslator2D_.h"
#include "GUI/Panels/PanelMain.h"


PanelMain::PanelMain(Context *context) :
    WindowT(context)
{
    SetName("PanelMain");

    SetFixedSize(TheSettings.GetIntVector2("panel", "main", "size"));

    SetMovable(false);

    IntVector2 posStart = {TheSettings.GetInt("panel", "map", "width") - 1, 
        TheGraphics->GetHeight() - TheSettings.GetInt("panel", "bottom", "height") -
        TheSettings.GetInt("panel", "main", "height") + 1};

    IntVector2 posFinish = {TheSettings.GetInt("panel", "map", "width") - 1, TheGraphics->GetHeight()};

    translator = new LineTranslator2D(posStart, posFinish, TheSettings.GetFloat("panel", "speed"),
        LineTranslator2D::State_PointStart);
}


void PanelMain::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<PanelMain>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowT);
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
