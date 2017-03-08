#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleParser
{
    typedef bool (ConsoleParser::*pFuncMember)(Vector<String>&);

public:
    struct ParserStruct
    {
        String command;
        pFuncMember func;
        String help;
        String fullHelp[10];     // Здесь хранится подробная информация о команде.
    };

    static HashMap<String, ParserStruct> commands;

    static void Init();
    bool Execute(const String &string);

    bool FuncHelp(Vector<String> &);
    bool FuncClear(Vector<String> &);
    bool FuncClose(Vector<String> &);
    bool FuncExit(Vector<String> &);
    bool FuncStart(Vector<String> &);
    bool FuncClient(Vector<String> &);
    bool FuncServer(Vector<String> &);
    bool FuncVars(Vector<String> &);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class History
{
public:
    History();
    ~History();
    void AddString(String &string);
    String GetPrev();
    String GetNext();
private:
    Vector<String> strings;
    int position = 0;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleRTS : public WindowRTS
{
    URHO3D_OBJECT(ConsoleRTS, WindowRTS);

public:
    ConsoleRTS(Context *context);
    void Toggle();
    bool IsActive();                            // Возвращает true, если активна строка ввода
    void Write(const String &message);
    void Clear();

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;
    History history;
    ConsoleParser parser;

    void HandleFinishedText(StringHash, VariantMap&);
    void HandleUnhandledKey(StringHash, VariantMap&);
    void HandleClick(StringHash, VariantMap&);
    void HandleResize(StringHash, VariantMap&);
    void HandleAsyncExecFinished(StringHash, VariantMap&);
};
