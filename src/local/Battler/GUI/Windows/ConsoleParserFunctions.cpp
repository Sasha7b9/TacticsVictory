// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Console.h"
#include "GlobalFunctions.h"
#include "Network/Client.h"
#include "Network/Server.h"
#include "Network/NetworkMessages.h"
#include "Network/VectorBufferRTS.h"
#include "GUI/Menu/MenuRTS.h"
#include "GUI/Windows/WindowVariables.h"



bool ConsoleParser::FuncClient(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"start",   None,   &ConsoleParser::FuncClientStart,    "запуск клиента. Формат команды - client -start -address:XX.XX.XX.XX -port:XX"},
        {"stop",    None,   &ConsoleParser::FuncClientStop,     "останов клиента"}
    };

    return Run(structs, words, showInfo);
}


static void OnServerConnected()
{
    TheClient->Send(MSG_REQUEST_LANDSCAPE, VectorBufferRTS());
    TheConsole->Write("Запрашиваю ландшафт");
}


bool ConsoleParser::FuncClientStart(Vector<String> &words, bool) //-V2009
{
    String address = SERVER_ADDRESS;
    uint16 port = SERVER_PORT;
    if(!GetAddressPort(words, address, port))
    {
        return false;
    }

    if(TheClient->IsConnected())
    {
        TheConsole->Write("Command forbidden. The client already running");
    }
    else
    {
        gMenu->Hide();
        TheClient->StartConnecting(SERVER_ADDRESS, SERVER_PORT, OnServerConnected);
        TheConsole->Write("Соединяюсь с удалённым сервером...");
    }

    return true;
}


bool ConsoleParser::FuncClientStop(Vector<String> &, bool)
{
    return false;
}


bool ConsoleParser::FuncServer(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"start",       Int,    &ConsoleParser::FuncServerStart,        "cоздать сервер на порт XX"},
        {"stop",        None,   &ConsoleParser::FuncServerStop,         "остановить сервер"},
        {"latency",     Int,    &ConsoleParser::FuncServerLatency,      "эмулировать задержку сети длительностью XX миллисекунд"},
        {"packetloss",  Float,  &ConsoleParser::FuncServerPacketLoss,   "эмулировать потерю X.X пакетров"}
    };

    return Run(structs, words, showInfo);
}


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
    TheFileSystem->SystemRunAsync(GetFileName("TVserver.exe"), arguments);
    serverRunning = true;

    return true;
}


void ConsoleParser::HandleAsyncExecFinished(StringHash, VariantMap& data) //-V2009
{
    using namespace AsyncExecFinished;

    int exitCode = data[P_EXITCODE].GetInt();

    if(exitCode)
    {
        TheConsole->Write("Сервер завершил работу с кодом ошибки");
    }
    else
    {
        TheConsole->Write("Сервер завершил работу");
    }

    UnsubscribeFromEvent(E_ASYNCLOADFINISHED);
}


bool ConsoleParser::FuncServerStop(Vector<String> &, bool)
{
    if(serverRunning)
    {
        TheClient->Send(MSG_DELETE_SERVER, VectorBufferRTS());
    }
    else
    {
        TheConsole->Write("Forbidden");
    }
    return true;
}


bool ConsoleParser::FuncServerLatency(Vector<String> &words, bool) //-V2009
{
    int latency = 0;

    if(ExtractInt(words[0], &latency))
    {
        TheClient->Send(MSG_SET_NETWORK_LATENCY, VectorBufferRTS(latency));
        return true;
    }

    return false;
}


bool ConsoleParser::FuncServerPacketLoss(Vector<String> &words, bool) //-V2009
{
    float loss = 0.0f;

    if(ExtractFloat(words[0], &loss))
    {
        TheClient->Send(MSG_SET_NETWORK_LOSS, VectorBufferRTS(loss));
        return true;
    }

    return false;
}


bool ConsoleParser::FuncVars(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"open",    None,   &ConsoleParser::FuncVarsOpen,   "открыть окно переменных"},
        {"close",   None,   &ConsoleParser::FuncVarsClose,  "закрыть окно переменных"}
    };

    if(words.Size() || showInfo)
    {
        return Run(structs, words, showInfo);
    }
    else
    {
        TheWindowVars->SetVisible(!TheWindowVars->IsVisible());
        return true;
    }

    return true;
}


bool ConsoleParser::FuncVarsOpen(Vector<String> &, bool)
{
    TheWindowVars->SetVisible(true);
    return true;
}


bool ConsoleParser::FuncVarsClose(Vector<String> &, bool)
{
    TheWindowVars->SetVisible(false);
    return true;
}


bool ConsoleParser::FuncClear(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        TheConsole->Clear();
    }
    return true;
}


bool ConsoleParser::FuncClose(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        TheConsole->Toggle();
    }
    return true;
}


bool ConsoleParser::FuncExit(Vector<String> &, bool showInfo)
{
    if(!showInfo)
    {
        TheClient->Disconnect();
        TheServer->Disconnect();
        TheEngine->Exit();
    }
    return true;
}


bool ConsoleParser::FuncUnit(Vector<String> &words, bool showInfo)
{
    const ParserStruct structs[100] =
    {
        {"camera",  None,   &ConsoleParser::FuncUnitCamera,     "функции управления видом от первого лица"}
    };

    return Run(structs, words, showInfo);
}


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
                TheScene->GetChildren(childrens);
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
                TheScene->GetChildren(childrens);
                for(Node *node : childrens)
                {
                    if(node->GetName() == NODE_CAMERA_TARGET)
                    {
                        TheConsole->Write(ToString("%f", node->GetComponent<Camera>()->GetFov()));
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
                TheConsole->Write("position set");
                return true;
            }
            else if(BeginFrom(words[1], "get"))
            {
                TheConsole->Write("position get");
                return true;
            }
        }
    }

    return false;
}
