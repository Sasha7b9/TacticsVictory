#include <stdafx.h>
#include "GUI/GUI.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Menu/StartMenu.h"
#include "GUI/Menu/Console.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/Menu/MenuMain.h"
#include "GUI/Menu/WindowConfirmExit.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUi/Elements/Hint.h"
#include "GUI/GuiGame/GuiGame.h"
#include "Core/Camera.h"
#include "TacticsVictory.h"
#include "Game/Scene.h"
#include "Game/Objects/Ammo/Rocket/Rocket.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TacticsVictory::HandlePostRenderUpdate(StringHash, VariantMap&)
{
    if(drawDebug)
    {
        gPhysicsWorld->DrawDebugGeometry(true);
        gDebugRenderer->AddLine(Vector3::ZERO, {100.0f, 0.0f, 0.0f}, Color::RED);
        gDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 100.0f, 0.0f}, Color::GREEN);
        gDebugRenderer->AddLine(Vector3::ZERO, {0.0f, 0.0f, 100.0f}, Color::BLUE);
        //gRenderer->DrawDebugGeometry(false);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleKeyDown(StringHash, VariantMap& eventData)
{
    int key = eventData[KeyDown::P_KEY].GetInt();

    gUIRoot->RemoveChild(gHint);

    if(key == KEY_F1)
    {
        gConsole->Toggle(); 
    }
    else if(key == KEY_ESCAPE)
    {
        if (gEngineConsole->IsVisible())            // Engine console is opened
        {
            gEngineConsole->SetVisible(false);
        }
        else if (gConsole->IsVisible())             // Console is opened
        {
            gConsole->Toggle();
        }
        else if (gGuiGame->IsVisible())             // We are in game
        {
            if (gGUI->MenuIsVisible())
            {
                gMenuMain->Close();
            }
            else
            {
                gMenuMain->Open();
            }
        }
        else if (gGuiEditor->IsVisible())           // We are in editor
        {
        }
        else if (gGUI->MenuIsVisible())             // We are int main screen
        {
            if (gMenuOptions->IsVisible())
            {
                gGUI->SetVisibleMenu(gMenuOptions, false);
            }
            else if (gMenuMain->IsVisible())
            {
                gMenuMain->SetDisabled();
                gWindowConfirmExit->SetVisible(true);
            }
            else if (gWindowConfirmExit->IsVisible())
            {
                gMenuMain->SetEnabled();
                gWindowConfirmExit->SetVisible(false);
            }
        }
    }
    else if(key == KEY_F11)
    {
        gEngineConsole->Toggle();
    }
    else if(key == KEY_F10)
    {
        gDebugHud->ToggleAll();
    }
    else if(!gUI->GetFocusElement() && !gStartMenu->Enabled())
    {
        if(key == '9')
        {
            Image screenshot(context_);
            gGraphics->TakeScreenShot(screenshot);
            screenshot.SavePNG(gFileSystem->GetProgramDir() + "Data/Screenshot_" +
                               Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
        if(key == KEY_SPACE)
        {
            drawDebug = !drawDebug;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    int typeEvent = eventData[MenuEvent::P_TYPE].GetInt();

    if (typeEvent == MenuEvent_NewGame)
    {
    }
    else if (typeEvent == MenuEvent_OpenEditor)
    {
        CreateEditorSession();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleUpdate(StringHash, VariantMap& eventData)
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    //LOGINFOF("time frame %f, time from begin %f, fps %f", time, gTime->GetElapsedTime(), gTime->GetFrameNumber() / gTime->GetElapsedTime());

    gCamera->Move(time);

    if (gCursor)
    {
        gCursor->Update(time);
    }

    if (scene)
    {
        scene->Update(time);
    }

    if (gScene)
    {
        /*
        PODVector<Component*> components;
        gScene->GetComponents(components, ParticleEmitter::GetTypeStatic(), true);
        URHO3D_LOGINFOF("%d components", components.Size());
        */
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandlePostUpdate(StringHash, VariantMap& eventData)
{
    float time = eventData[Update::P_TIMESTEP].GetFloat();

    Rocket::UpdateAll(time);
}
