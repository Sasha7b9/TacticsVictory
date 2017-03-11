// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "TacticsVictory.h"
#include "Core/Camera.h"
#include "Game/Scene.h"
#include "LogRTS.h"
#include "Game/Objects/Ammo/Rocket/Rocket.h"
#include "GUI/GUI.h"
#include "GUI/Cursor.h"
#include "GUI/Menu/MenuRTS.h"
#include "GUI/Menu/MenuStart.h"
#include "GUI/Menu/MenuOptions.h"
#include "GUI/Menu/MenuGame.h"
#include "GUI/Menu/MenuConfirmExit.h"
#include "GUI/Windows/Console.h"
#include "GUI/GuiEditor/GuiEditor.h"
#include "GUi/Controls/Hint.h"
#include "GUI/GuiGame/GuiGame.h"
#include "Network/Client.h"
#include "Network/VectorBufferRTS.h"
#include "Network/NetworkMessages.h"


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

    if(KEY_IS_F1)
    {
        if(gConsole)
        {
            gConsole->Toggle();
        }
        return;
    }
    else if(KEY_IS_F10)
    {
        gDebugHud->ToggleAll();
        return;
    }
    else if(KEY_IS_F11)
    {
        if(gEngineConsole)
        {
            gEngineConsole->Toggle();
        }
        return;
    }
    
    if(KEY_IS_ESC)
    {
        if(gEngineConsole && gEngineConsole->IsVisible())
        {
            gEngineConsole->SetVisible(false);
        }
        else if(gConsole && gConsole->IsVisible())
        {
            gConsole->Toggle();
        }
    }
    
    if(!gConsole->IsActive())
    {
        if(gMenu->ProcessingKey(key))                       // Если меню обработало нажатие
        {
            return;                                         // следовательно, оно активно, поэтому после обработки выходим
        }
    }
    
    if(!gUI->GetFocusElement())
    {
        if(KEY_IS_9)
        {
            Image screenshot(context_);
            gGraphics->TakeScreenShot(screenshot);
            screenshot.SavePNG(gFileSystem->GetProgramDir() + "Data/Screenshot_" +
                               Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
        if(KEY_IS_SPACE)
        {
            drawDebug = !drawDebug;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void TacticsVictory::HandleMenuEvent(StringHash, VariantMap& eventData)
{
    int typeEvent = eventData[MenuEvent::P_TYPE].GetInt();

    if (typeEvent == MenuEvent_StartServer)
    {
        uint port = eventData[MenuEvent::P_PORT].GetUInt();
        StartServer((uint16)port);
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

    if(gClient->GetServerConnection())
    {
        VectorBufferRTS msg;

        static Vector3 prevPosition = Vector3::ZERO;
        Vector3 position = gCamera->GetNode()->GetPosition();

        static Quaternion prevRotation = Quaternion::IDENTITY;
        Quaternion rotation = gCamera->GetNode()->GetRotation();

        if(position != prevPosition || rotation != prevRotation)
        {
            msg.WriteVector3(position);
            msg.WriteQuaternion(rotation);

            prevPosition = position;
            prevRotation = rotation;

            gClient->Send(MSG_CAMERA_INFO, msg);
        }
    }
}
