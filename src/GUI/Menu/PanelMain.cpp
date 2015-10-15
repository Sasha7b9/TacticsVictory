#include <stdafx.h>


tvPanelMain::tvPanelMain(Context *context) :
    tvWindow(context)
{
    SetName("PanelMain");

    SetFixedSize(SET::PANEL::MAIN::SIZE);

    SetMovable(false);

    IntVector2 posStart = {SET::PANEL::MAP::WIDTH - 1, gGraphics->GetHeight() - SET::PANEL::BOTTOM::HEIGHT - SET::PANEL::MAIN::HEIGHT + 1};
    IntVector2 posFinish = {SET::PANEL::MAP::WIDTH - 1, gGraphics->GetHeight()};

    translator = new tvLineTranslator2D(posStart, posFinish, gSet->GetFloat(TV_PANEL_SPEED), tvLineTranslator2D::State_PointStart);
}

void tvPanelMain::RegisterObject(Context *context)
{
    context->RegisterFactory<tvPanelMain>("UI");

    COPY_BASE_ATTRIBUTES(tvWindow);
}

void tvPanelMain::Update(float dT)
{
    SetPosition(translator->Update(dT));
}

void tvPanelMain::Toggle()
{
    translator->Toggle();
}

void tvPanelMain::AddTab(SharedPtr<tvTab> tab)
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

    SubscribeToEvent(tab->buttonTitle, Urho3D::E_TOGGLED, HANDLER(tvPanelMain, HandleToggedTitle));

    AddChild(tab);

    tab->SetPosition(0, y0 + tab->buttonTitle->GetHeight() - 1);
    tab->SetFixedSize(GetWidth(), GetHeight() - y0 - tab->buttonTitle->GetHeight() + 1);
}

void tvPanelMain::HandleToggedTitle(StringHash, VariantMap &eventData)
{
    tvButtonToggled *button = (tvButtonToggled*)eventData[Urho3D::Toggled::P_ELEMENT].GetPtr();
    bool state = (bool)eventData[Urho3D::Toggled::P_STATE].GetBool();

    if(state)
    {
        for(auto tab : tabs)
        {
            if(tab->buttonTitle->IsChecked() && button != tab->buttonTitle)
            {
                UnsubscribeFromEvent(tab->buttonTitle, Urho3D::E_TOGGLED);
                tab->buttonTitle->SetChecked(false);
                SubscribeToEvent(tab->buttonTitle, Urho3D::E_TOGGLED, HANDLER(tvPanelMain, HandleToggedTitle));
            }
        }
    }
    else
    {
        button->SetChecked(true);
    }
}