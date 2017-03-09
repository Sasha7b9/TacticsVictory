#include <stdafx.h>
#include "Console.h"
#include "GlobalFunctions.h"
#include "TacticsVictory.h"
#include "GUI/Windows/WindowVariables.h"
#include "GUI/Menu/MenuRTS.h"
#include "Network/Client.h"
#include "Network/Server.h"
#include "Network/NetworkMessages.h"
#include "Network/VectorBufferRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HashMap<String, ConsoleParser::ParserStruct> ConsoleParser::commands;

#define TAB "    "


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleParser::ConsoleParser(Context *context) : Object(context)
{

}

bool ConsoleParser::FuncHelp(Vector<String> &)
{
    gConsole->Write(String(TAB) + L"Справка по командам");

    // Находим максимальную длину слова
    uint len = 0;
    for(HashMap<String, ConsoleParser::ParserStruct>::KeyValue key : ConsoleParser::commands)
    {
        if(key.first_.Length() > len)
        {
            len = key.first_.Length();
        }
    }

    for(HashMap<String, ConsoleParser::ParserStruct>::KeyValue key : ConsoleParser::commands)
    {
        if(key.first_ != "?")
        {
            String message;
            message += key.first_;

            for(uint i = 0; i < len - key.first_.Length() + 1; i++)
            {
                message += " ";
            }

            gConsole->Write(message + key.second_.help);
        }
    }

    gConsole->Write(String(TAB) + L"Для получения подробной информации наберите \"vars ?\"");

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void ShowFullInfo(Vector<String> &strings)
{
    ConsoleParser::ParserStruct parserStruct = ConsoleParser::commands[strings[0]];

    gConsole->Write(strings[0] + " " + parserStruct.fullHelp[0]);
    gConsole->Write(TAB + parserStruct.help);

    String* help = &parserStruct.fullHelp[1];
    while(!help->Empty())
    {
        gConsole->Write(TAB + *help);
        help++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncExit(Vector<String> &)
{
    gClient->Disconnect();
    gServer->Disconnect();
    gEngine->Exit();
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncVars(Vector<String> &words)
{
    uint size = words.Size();

    String word0 = size > 0 ? words[0] : "";
    String word1 = size > 1 ? words[1] : "";

    if(size == 1)
    {
        gWindowVars->SetVisible(!gWindowVars->IsVisible());
    }
    else if(size == 2)
    {
        if(word1 == "open")
        {
            gWindowVars->SetVisible(true);
        }
        else if(word1 == "close")
        {
            gWindowVars->SetVisible(false);
        }
        else
        {
            return false;
        }
    }

    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClear(Vector<String> &)
{
    gConsole->Clear();
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClose(Vector<String> &)
{
    gConsole->Toggle();
    return true;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncStart(Vector<String> &words)
{
    String address = SERVER_ADDRESS;
    uint16 port = SERVER_PORT;

    if(words.Size() < 2 || !GetAddressPort(words, address, port))
    {
        return false;
    }

    if (words.Contains("-server"))
    {
        if (gServer->IsRunning())
        {
            gConsole->Write("Server already running");
        }
        else
        {
            static Vector<String> arguments;
            arguments.Push(ToString("-port:%d", port));
            gFileSystem->SystemRunAsync(GetFileName("TVserver.exe"), arguments);
        }
        return true;
    }

    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncServer(Vector<String> &words)
{
    if(words.Size() < 2)
    {
        return false;
    }

    if(words[1] == "-start")
    {
        String address = "";
        uint16 port = 0;

        if(!GetAddressPort(words, address, port) || port == 0)
        {
            return false; 
        }

        static Vector<String> arguments;
        arguments.Push(ToString("-port:%d", port));
        gFileSystem->SystemRunAsync(GetFileName("TVserver.exe"), arguments);
        serverRunning = true;
        SubscribeToEvent(E_ASYNCLOADFINISHED, URHO3D_HANDLER(ConsoleParser, HandleAsyncExecFinished));
        
        return true;
    }
    else if(words[1] == "-stop")
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
    else if(BeginFrom(words[1], "-latency:"))
    {
        int latency = 0;
        ReadIntFromString(words[1], &latency);
        gClient->Send(MSG_SET_NETWORK_LATENCY, VectorBufferRTS(latency));
        gConsole->Write(ToString("latency %d", latency));
        return true;
    }
    else if(BeginFrom(words[1], "-packetloss:"))
    {
        float loss = 0.0f;
        ReadFloatFromString(words[1], &loss);
        gClient->Send(MSG_SET_NETWORK_LOSS, VectorBufferRTS(loss));
        gConsole->Write(ToString("loss %f", loss));
        return true;
    }
    else if(words[1] == "-connections")
    {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleParser::HandleAsyncExecFinished(StringHash, VariantMap& data)
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
void OnServerConnected()
{
    gClient->Send(MSG_REQUEST_LANDSCAPE, VectorBufferRTS());
    gConsole->Write(L"Запрашиваю ландшафт");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleParser::FuncClient(Vector<String> &words)
{
    if(words.Size() < 2)
    {
        return false;
    }

    if(words[1] == "-start")
    {
        String address = SERVER_ADDRESS;
        uint16 port = SERVER_PORT;
        if(!GetAddressPort(words, address, port))
        {
            return false;
        }

        if(gClient->IsConnected())
        {
            gConsole->Write("Commnad forbidden. The client already running");
        }
        else
        {
            gMenu->Hide();
            gClient->StartConnecting(SERVER_ADDRESS, SERVER_PORT, OnServerConnected);
            gConsole->Write(L"Соединяюсь с удалённым сервером...");
        }
        return true;
    }
    else if(words[1] == "-stop")
    {
        return false;
    }

    return false;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConsoleParser::Init()
{
    ParserStruct structs[100] =
    {
        {"?",           &FuncHelp,          L"Вывод справки"},
        {"clear",       &FuncClear,         L"Очистить консоль"},
        {"close",       &FuncClose,         L"Закрыть консоль"},
        {"exit",        &FuncExit,          L"Выход"},
        {"start",       &FuncStart,         L"Запуск игры в режиме сервера или клиента",
                                            {"[-server] [-client] [-address:xx.xx.xx.xx] [-port:xx]",
                                            L"server - создать сервер на порту port. По умолчанию 1000",
                                            L"client - приконнектиться с серверу с адресом address:port. По умолчанию 127.0.0.1:1000"}},
        {"client",      &FuncClient,        L"Запуск клиента",
                                            {L"[-start|-stop] [-address:xx.xx.xx.xx -port:xx]"}},
        {"server",      &FuncServer,        L"Запуск сервера",
                                            {L"[-start|-stop|-connections] [-port:xx]",
                                            L"-start -port:42 : создать сервер на порт 42",
                                            L"-latency:100    : установить задержку сети 100мс",
                                            L"-packetloss:0.1 : установить потери пакетов 10%",
                                            L"-stop           : остановить сервер. При этом приложение-сервер выгружается из памяти",
                                            L"-connections    : вывести информацию об имеющихся подключениях сервера"}},
        {"vars",        &FuncVars,          L"Управление окном переменных",
                                            {"[open|close]", L"open - показать", L"close - скрыть"}
        },
    };

    ParserStruct *parserStruct = structs;

    while(parserStruct->func)
    {
        ConsoleParser::commands.Insert({parserStruct->command, *parserStruct});
        parserStruct++;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleParser::Execute(const String &string)
{
    Vector<String> words = string.ToLower().Split(' ');

    uint numWords = words.Size();

    if(commands.Contains(words[0]))
    {
        if(numWords > 1 && (words[1] == "?" || words[1] == "-?"))
        {
            ShowFullInfo(words);
            return;
        }

        pFuncMember func = commands[words[0]].func;

        if(func)
        {
            if(!(this->*func)(words))
            {
                gConsole->Write(ToString("Invalid command syntax. For more information, type \"%s -?\"", words[0].CString()));
            }
            return;
        }
    }

    gConsole->Write(L"Неизвестная команда");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConsoleRTS::ConsoleRTS(Context *context) :
    WindowRTS(context)
{
    ConsoleParser::Init();

    SetVisible(false);
    SetResizable(true);

    SetSize(gGraphics->GetWidth(), 300);
    SetResizable(true);

    lineEdit = gUIRoot->CreateChild<LineEdit>();
    lineEdit->SetStyle("LineEdit");

    AddChild(lineEdit);

    /*
    scrollBar = gUIRoot->CreateChild<ScrollBar>();
    scrollBar->SetFixedSize(10, GetHeight() - 15);
    scrollBar->SetPosition(GetWidth() - 10, 0);
    scrollBar->SetStyleAuto();
    scrollBar->SetOrientation(O_VERTICAL);
    scrollBar->SetRange(0.0f);
    AddChild(scrollBar);
    */

    text = gUIRoot->CreateChild<Text>();
    text->SetStyle("WindowMenu");
    text->SetWordwrap(true);
    AddChild(text);

    SubscribeToEvent(lineEdit, E_TEXTFINISHED, URHO3D_HANDLER(ConsoleRTS, HandleFinishedText));
    SubscribeToEvent(lineEdit, E_UNHANDLEDKEY, URHO3D_HANDLER(ConsoleRTS, HandleUnhandledKey));
    SubscribeToEvent(text, E_CLICK, URHO3D_HANDLER(ConsoleRTS, HandleClick));
    SubscribeToEvent(this, E_CLICK, URHO3D_HANDLER(ConsoleRTS, HandleClick));
    SubscribeToEvent(this, E_RESIZED, URHO3D_HANDLER(ConsoleRTS, HandleResize));

    VariantMap map;
    HandleResize("", map);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::Toggle()
{
   SetVisible(!IsVisible());
   if(IsVisible())
   {
       this->BringToFront();
       gUI->SetFocusElement(lineEdit);
   }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
bool ConsoleRTS::IsActive()
{
    return lineEdit->HasFocus();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::HandleFinishedText(StringHash, VariantMap&)
{
    String command = lineEdit->GetText();
    if(command.Empty())
    {
        return;
    }
    history.AddString(command);

    String message;

    Write(message + "> " + command);

    parser.Execute(command);

    lineEdit->SetText("");
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::HandleUnhandledKey(StringHash, VariantMap& eventData)
{
    using namespace UnhandledKey;
    int key = eventData[P_KEY].GetInt();

    if(KEY_IS_UP)
    {
        lineEdit->SetText(history.GetPrev());
    }
    else if(KEY_IS_DOWN)
    {
        lineEdit->SetText(history.GetNext());
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::HandleClick(StringHash, VariantMap&)
{
    lineEdit->SetFocus(true);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::HandleResize(StringHash, VariantMap&)
{
    lineEdit->SetSize(GetWidth() - 20, 15);
    lineEdit->SetPosition(2, GetHeight() - 15);

    text->SetFixedSize(GetWidth(), GetHeight() - 20);
    text->SetPosition(2, 0);

    // Теперь ограничим количество строк
#define MAX_STRING 100
    while (text->GetNumRows() > MAX_STRING)
    {
        uint pos = text->GetText().Find("\n");
        text->SetText(text->GetText().Substring(pos + 2));
    }

    int height = GetHeight();
    int heightText = text->GetHeight() + 15;

    if (heightText > height)
    {
        IntVector2 pos = text->GetPosition();
        pos.y_ = -(heightText - height);
        text->SetPosition(pos);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef CLIENT
void ConsoleRTS::Write(const String &message)
{
    if(message[0] == '>')
    {
        text->SetText(text->GetText() + "\n");
    }

    String str;

#ifdef _WINDOWS

    SYSTEMTIME st;
    GetLocalTime(&st);
    str = IntToString(st.wHour, 2) + ":" + IntToString(st.wMinute, 2) + ":" + IntToString(st.wSecond, 2) + ":" + IntToString(st.wMilliseconds, 3) + " ";

#endif

    if(message[0] != '>')
    {
        str.Append("< ");
    }

    str += message + "\n";

    text->SetText(text->GetText() + str);

    VariantMap map;
    HandleResize("", map);
}
#else
void ConsoleRTS::Write(const String &) {}
#endif


//----------------------------------------------------------------------------------------------------------------------------------------------------
void ConsoleRTS::Clear()
{
    text->SetText("");
    text->SetPosition(2, 0);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
History::History()
{
    SharedPtr<File> fileRead;
    fileRead = new File(gContext);
    if (fileRead->Open(GetNameFile("history.txt"), FILE_READ))
    {
        while (!fileRead->IsEof())
        {
            strings.Push(fileRead->ReadString());
        }
        fileRead->Close();
    }
    position = (int)strings.Size();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
History::~History()
{
    SharedPtr<File> file;
    file = new File(gContext);
    String name = GetNameFile("history.txt");
    if (file->Open(name, FILE_READ))
    {
        file->Close();
        file->Open(name, FILE_WRITE);
        while (strings.Size() > 100)
        {
            strings.Erase(0);
        }
        for (uint i = 0; i < strings.Size(); i++)
        {
            file->WriteString(strings[i]);
        }
        file->Close();
    }
}

void History::AddString(String &string)
{
    if(strings.Contains(string))
    {
        strings.Remove(string);
    }
    strings.Push(string);
    position = (int)strings.Size();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
String History::GetPrev()
{
    if(strings.Size() == 0)
    {
        return String::EMPTY;
    }

    position--;
    if(position < 0)
    {
        position = 0;
    }

    return strings[(uint)position];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
String History::GetNext()
{
    if(strings.Size() == 0)
    {
        return String::EMPTY;
    }

    position++;
    if(position > (int)strings.Size() - 1)
    {
        position = (int)strings.Size() - 1;
    }

    return strings[(uint)position];
}
