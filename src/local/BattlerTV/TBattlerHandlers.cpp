// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "TBattler.h"
#include "GUI/TCursor.h"
#include "GUI/Windows/TConsole.h"
#include "GUI/Menu/TMenu.h"
#include "GUI/Menu/TMenuEvents.h"
#include "Scene/_TScene.h"
#include "Scene/Cameras/TCamera.h"


void Battler::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    if(drawDebug)
    {
        ThePhysicsWorld->DrawDebugGeometry(true);
        TheDebugRenderer->AddLine(Vector3::ZERO, {100.0f, 0.0f, 0.0f}, Color::RED);
        TheDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 100.0f, 0.0f}, Color::GREEN);
        TheDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 0.0f, 100.0f}, Color::BLUE);
        //TheRenderer->DrawDebugGeometry(false);
    }
}


void Battler::HandleKeyDown(StringHash, VariantMap& eventData)
{
    int key = eventData[KeyDown::P_KEY].GetInt();

    TheUIRoot->RemoveChild(TheHint);

    if(KEY_IS_F1)
    {
        if(TheConsole)
        {
            TheConsole->Toggle();
        }
        return;
    }
    else if(KEY_IS_F10)
    {
        TheDebugHud->ToggleAll();
        return;
    }
    else if(KEY_IS_F11)
    {
        if(TheEngineConsole)
        {
            TheEngineConsole->Toggle();
        }
        return;
    }
    
    if(KEY_IS_ESC)
    {
        if(TheEngineConsole && TheEngineConsole->IsVisible())
        {
            TheEngineConsole->SetVisible(false);
        }
        else if(TheConsole && TheConsole->IsVisible())
        {
            TheConsole->Toggle();
        }
    }
    
    if(!TheConsole->IsActive())
    {
        if(TheMenu->ProcessingKey(key))                       // Если меню обработало нажатие
        {
            return;                                         // следовательно, оно активно, поэтому после обработки выходим
        }
    }
    
    if(!TheUI->GetFocusElement())
    {
        if(KEY_IS_9)
        {
            Image screenshot(context_);
            TheGraphics->TakeScreenShot(screenshot);
            screenshot.SavePNG(TheFileSystem->GetProgramDir() + "Data/Screenshot_" +
                               Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
        if(KEY_IS_SPACE)
        {
            drawDebug = !drawDebug;
        }
    }
}


void Battler::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    int typeEvent = eventData[MenuEvent::P_TYPE].GetInt();

    if (typeEvent == MenuEvent_StartServer)
    {
        uint port_ = eventData[MenuEvent::P_PORT].GetUInt();
        StartServer(static_cast<uint16>(port_));
    }
    else if (typeEvent == MenuEvent_StartClient)
    {
        //StartClient();
    }
    else if (typeEvent == MenuEvent_OpenEditor)
    {
        CreateEditorSession();
    }
}


void Battler::HandleUpdate(StringHash, VariantMap& eventData)
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    TheCamera->Move(time);
}


void Battler::HandlePostUpdate(StringHash, VariantMap& /*eventData*/)
{
}
