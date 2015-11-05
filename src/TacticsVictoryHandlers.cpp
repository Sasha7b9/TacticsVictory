#include <stdafx.h>


#include "GUI/GUI.h"
#include "GUI/Elements/Cursor.h"
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

    gUIRoot->RemoveChild(gHint);

    if(key == Urho3D::KEY_F1)
    {
        gConsole->Toggle(); 
    }
    else if(key == Urho3D::KEY_ESC)
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
                gScene->SetTimeScale(1.0f);
                gGUI->RemoveFromScreen();
                gCamera->SetEnabled(true);
            }
            else
            {
                gScene->SetTimeScale(0.0f);
                gGUI->AddToScreen();
                gCamera->SetEnabled(false);
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
                gMenuMain->SetVisible(false);
                gWindowConfirmExit->SetVisible(true);
            }
            else if (gWindowConfirmExit->IsVisible())
            {
                gMenuMain->SetVisible(true);
                gWindowConfirmExit->SetVisible(false);
            }
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
            UImage screenshot(context_);
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

    //LOGINFOF("time frame %f, time from begin %f, fps %f", time, gTime->GetElapsedTime(), gTime->GetFrameNumber() / gTime->GetElapsedTime());

    gCamera->Move(time);

    if (gCursor)
    {
        gCursor->Update(time);
    }

    if (scene)
    {
        scene->Update();
    }
}
