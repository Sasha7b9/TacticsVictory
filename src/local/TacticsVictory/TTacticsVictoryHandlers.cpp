// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


void TacticsVictory::HandlePostRenderUpdate(StringHash, VariantMap&)
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


void TacticsVictory::HandleKeyDown(StringHash, VariantMap& eventData) //-V2009
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


void TacticsVictory::HandleMenuEvent(StringHash, VariantMap& eventData) //-V2009
{
    int typeEvent = eventData[MenuEvent::P_TYPE].GetInt();

    if (typeEvent == MenuEvent_StartServer)
    {
    }
    else if (typeEvent == MenuEvent_StartClient)
    {
    }
    else if (typeEvent == MenuEvent_OpenEditor)
    {
        CreateEditorSession();
    }
}


void TacticsVictory::HandleUpdate(StringHash, VariantMap& eventData) //-V2009
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    //LOGINFOF("time frame %f, time from begin %f, fps %f", time, TheTime->GetElapsedTime(), TheTime->GetFrameNumber() / TheTime->GetElapsedTime());

    TheCamera->Move(time);

    if (TheCursor)
    {
        TheCursor->Update(time);
    }

    if (scene)
    {
        scene->Update(time);
    }

    if (TheScene)
    {
        /*
        PODVector<Component*> components;
        TheScene->GetComponents(components, ParticleEmitter::GetTypeStatic(), true);
        URHO3D_LOGINFOF("%d components", components.Size());
        */
    }
}


void TacticsVictory::HandlePostUpdate(StringHash, VariantMap& eventData) //-V2009
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    Rocket::UpdateAll(time);
}
