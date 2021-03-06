// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Battler.h"
#include "GUI/Cursor.h"
#include "GUI/Controls/Hint_.h"
#include "GUI/Menu/MenuEvents.h"
#include "GUI/Menu/Menu.h"
#include "GUI/Windows/Console.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"
#include "Scene/Objects/ObjectC.h"


void Battler::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    if(drawDebug)
    {
        ThePhysicsWorld->DrawDebugGeometry(true);
        TheDebugRenderer->AddLine(Vector3::ZERO, {1000.0f, 0.0f, 0.0f}, Color::RED);
        TheDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 1000.0f, 0.0f}, Color::GREEN);
        TheDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 0.0f, 1000.0f}, Color::BLUE);
    }

    auto key = ObjectSpecificC::remoteStorage.Begin();

    while (key->second_)
    {
        (key++)->second_->OnPostRenderUpdate();
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

    if (typeEvent == ME_StartServer)
    {
    }
    else if (typeEvent == ME_StartClient)
    {
    }
    else if (typeEvent == ME_OpenEditor)
    {
        CreateEditorSession();
    }
}
