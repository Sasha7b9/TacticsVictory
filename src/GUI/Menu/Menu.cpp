#include <stdafx.h>


tvMenu::tvMenu(Context *context) :
    UIElement(context)
{
    XMLFile *style = gCache->GetResource<XMLFile>("UI/MainStyle.xml");
    SetDefaultStyle(style);

    SetFixedSize(SET::WINDOW::SIZE);

    menuMain = this->CreateChild<tvMenuMain>();
    menuMain->SetInCenterRect({0, 0, gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT)});

    menuOptions = new tvMenuOptions(gContext);
    menuOptions->SetInCenterRect({0, 0, gSet->GetInt(TV_SCREEN_WIDTH), gSet->GetInt(TV_SCREEN_HEIGHT)});

    SubscribeToEvent(menuOptions, E_MENU, HANDLER(tvMenu, HandleMenuEvent));
    SubscribeToEvent(menuMain, E_MENU, HANDLER(tvMenu, HandleMenuEvent));
}

void tvMenu::RegisterObject(Context* context)
{
    context->RegisterFactory<tvMenu>("UI");

    COPY_BASE_ATTRIBUTES(UIElement);
}

void tvMenu::Log()
{
    LOGINFOF("window x = %d, y = %d, width = %d, height = %d", menuMain->GetPosition().x_, menuMain->GetPosition().y_, menuMain->GetWidth(), menuMain->GetHeight());
    LOGINFOF("menu x = %d, y = %d, widht = %d, height = %d", GetPosition().x_, GetPosition().y_, GetWidth(), GetHeight());
}

void tvMenu::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    uint action = eventData[MenuEvent::P_TYPE].GetUInt();

    if (action == MenuEvent_ExitInOS)
    {
        gEngine->Exit();
    }
    else if(action == MenuEvent_MenuOptionsOpen)
    {
        if(gUIRoot->FindChild(menuOptions) == Urho3D::M_MAX_UNSIGNED)
        {
            gUIRoot->AddChild(menuOptions);
        }
        else
        {
            gUIRoot->RemoveChild(menuOptions);
        }
    }
    else if(action == MenuEvent_MenuOptionsClose)
    {
        gUIRoot->RemoveChild(menuOptions);
    }
}
