﻿// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Console.h"
#include "GlobalFunctions.h"
#include "Network/Client.h"
#include "Network/Server.h"
#include "Network/NetworkMessages.h"
#include "Network/VectorBufferRTS.h"
#include "GUI/Menu/MenuRTS.h"
#include "GUI/Windows/WindowVariables.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ConsoleParser::FuncClient(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"start",   None,   &ConsoleParser::FuncClientStart,    L"запуск клиента. Формат команды - client -start -address:XX.XX.XX.XX -port:XX"},
        {"stop",    None,   &ConsoleParser::FuncClientStop,     L"останов клиента"}
    };

    return Run(structs, words, showInfo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void OnServerConnected()
{
    gClient->Send(MSG_REQUEST_LANDSCAPE, VectorBufferRTS());
    gConsole->Write(L"Запрашиваю ландшафт");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClientStart(Vector<String> &words, bool) //-V2009
{
    String address = SERVER_ADDRESS;
    uint16 port = SERVER_PORT;
    if(!GetAddressPort(words, address, port))
    {
        return false;
    }

    if(gClient->IsConnected())
    {
        gConsole->Write("Command forbidden. The client already running");
    }
    else
    {
        gMenu->Hide();
        gClient->StartConnecting(SERVER_ADDRESS, SERVER_PORT, OnServerConnected);
        gConsole->Write(L"Соединяюсь с удалённым сервером...");
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClientStop(Vector<String> &, bool)
{
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServer(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"start",       Int,    &ConsoleParser::FuncServerStart,        L"cоздать сервер на порт XX"},
        {"stop",        None,   &ConsoleParser::FuncServerStop,         L"остановить сервер"},
        {"latency",     Int,    &ConsoleParser::FuncServerLatency,      L"эмулировать задержку сети длительностью XX миллисекунд"},
        {"packetloss",  Float,  &ConsoleParser::FuncServerPacketLoss,   L"эмулировать потерю X.X пакетров"}
    };

    return Run(structs, words, showInfo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerStart(Vector<String> &words, bool) //-V2009
{
    int port = 0;

    if(!ExtractInt(words[0], &port))
    {
        return false;
    }

    static Vector<String> arguments;
    arguments.Push(ToString("-server:%d", port));
    // Подключаем обработчик кода, возвращаемого сервером при завершении работы
    SubscribeToEvent(E_ASYNCLOADFINISHED, URHO3D_HANDLER(ConsoleParser, HandleAsyncExecFinished));
    gFileSystem->SystemRunAsync(GetFileName("TVserver.exe"), arguments);
    serverRunning = true;

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleParser::HandleAsyncExecFinished(StringHash, VariantMap& data) //-V2009
{
    using namespace AsyncExecFinished;

    int exitCode = data[P_EXITCODE].GetInt();

    if(exitCode)
    {
        gConsole->Write(L"Сервер завершил работу с кодом ошибки");
    }
    else
    {
        gConsole->Write(L"Сервер завершил работу");
    }

    UnsubscribeFromEvent(E_ASYNCLOADFINISHED);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerStop(Vector<String> &, bool)
{
    if(serverRunning)
    {
        gClient->Send(MSG_DELETE_SERVER, VectorBufferRTS());
    }
    else
    {
        gConsole->Write("Forbidden");
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerLatency(Vector<String> &words, bool) //-V2009
{
    int latency = 0;

    if(ExtractInt(words[0], &latency))
    {
        gClient->Send(MSG_SET_NETWORK_LATENCY, VectorBufferRTS(latency));
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServerPacketLoss(Vector<String> &words, bool) //-V2009
{
    float loss = 0.0f;

    if(ExtractFloat(words[0], &loss))
    {
        gClient->Send(MSG_SET_NETWORK_LOSS, VectorBufferRTS(loss));
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncVars(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"open",    None,   &ConsoleParser::FuncVarsOpen,   L"открыть окно переменных"},
        {"close",   None,   &ConsoleParser::FuncVarsClose,  L"закрыть окно переменных"}
    };

    if(words.Size() || showInfo)
    {
        return Run(structs, words, showInfo);
    }
    else
    {
        gWindowVars->SetVisible(!gWindowVars->IsVisible());
        return true;
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncVarsOpen(Vector<String> &, bool)
{
    gWindowVars->SetVisible(true);
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncVarsClose(Vector<String> &, bool)
{
    gWindowVars->SetVisible(false);
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClear(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        gConsole->Clear();
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClose(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        gConsole->Toggle();
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncExit(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        gClient->Disconnect();
        gServer->Disconnect();
        gEngine->Exit();
    }
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncUnit(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"camera",  None,   &ConsoleParser::FuncUnitCamera,     L"функции управления видом от первого лица"}
    };

    return Run(structs, words, showInfo);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncUnitCamera(Vector<String> &words, bool)
{
    words.Erase(0, 1);

    if(words.Size() == 2)
    {
        if(BeginFrom(words[0], "fov"))
        {
            if(BeginFrom(words[1], "set"))
            {
                float fov = 0.0f;
                ExtractFloat(words[1], &fov);

                PODVector<Node*> childrens;
                gScene->GetChildren(childrens);
                for(Node *node : childrens)
                {
                    if(node->GetName() == NODE_CAMERA_TARGET)
                    {
                        node->GetComponent<Camera>()->SetFov(fov);
                    }
                }

                return true;
            }
            else if(BeginFrom(words[1], "get"))
            {
                PODVector<Node*> childrens;
                gScene->GetChildren(childrens);
                for(Node *node : childrens)
                {
                    if(node->GetName() == NODE_CAMERA_TARGET)
                    {
                        gConsole->Write(ToString("%f", node->GetComponent<Camera>()->GetFov()));
                        break;
                    }
                }
                return true;
            }
            
        }
        else if(BeginFrom(words[0], "position"))
        {
            if(BeginFrom(words[1], "set"))
            {
                gConsole->Write("position set");
                return true;
            }
            else if(BeginFrom(words[1], "get"))
            {
                gConsole->Write("position get");
                return true;
            }
        }
    }

    return false;
}
