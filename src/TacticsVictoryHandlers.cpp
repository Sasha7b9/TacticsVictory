#include <stdafx.h>


void TacticsVictory::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    if(drawDebug)
    {
        gDebugRenderer->AddLine(Vector3::ZERO, {100.0f, 0.0f, 0.0f}, Color::RED);
        gDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 100.0f, 0.0f}, Color::GREEN);
        gDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 0.0f, 100.0f}, Color::BLUE);
        //gRenderer->DrawDebugGeometry(false);
    }
}

void TacticsVictory::HandleKeyDown(StringHash, VariantMap& eventData)
{
    int key = eventData[Urho3D::KeyDown::P_KEY].GetInt();

    if(key == Urho3D::KEY_F1)
    {
        gConsole->Toggle();
    } 
    else if(key == Urho3D::KEY_ESC)
    {
        if(gEngineConsole->IsVisible())
        {
            gEngineConsole->SetVisible(false);
        }
        else if(!gMenu->IsVisible())
        {
            gMenu->SetVisible(true);
            gCamera->SetEnabled(false);
        }
        else if(gMenu->IsVisible())
        {
            gMenu->SetVisible(false);
            gCamera->SetEnabled(true);
        }
    }
    else if(key == Urho3D::KEY_F11)
    {
        gEngineConsole->Toggle();
    }
    else if(key == Urho3D::KEY_F10)
    {
        gDebugHud->ToggleAll();
    }
    else if(!gUI->GetFocusElement())
    {
        if(key == '9')
        {
            Image screenshot(context_);
            gGraphics->TakeScreenShot(screenshot);
            screenshot.SavePNG(gFileSystem->GetProgramDir() + "Data/Screenshot_" +
                               Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
        if(key == Urho3D::KEY_SPACE)
        {
            drawDebug = !drawDebug;
        }
    }
}

void TacticsVictory::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    int typeEvent = eventData[MenuEvent::P_TYPE].GetInt();

    if (typeEvent == MenuEvent_NewGame)
    {
        CreateNewGame();
    }
    else if (typeEvent == MenuEvent_OpenEditor)
    {
        CreateEditorSession();
    }
}

void TacticsVictory::HandleUpdate(StringHash, VariantMap& eventData)
{
    float time = eventData[Urho3D::Update::P_TIMESTEP].GetFloat();
    gCamera->Move(time);

    gCursor->Update(time);

    LOGINFOF("%d", gUIRoot->IsHovering());
}
