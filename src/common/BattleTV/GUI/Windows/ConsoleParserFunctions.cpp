// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


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
