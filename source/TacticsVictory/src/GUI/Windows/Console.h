#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleParser : public Object
{
    URHO3D_OBJECT(ConsoleParser, Object);

    typedef bool (ConsoleParser::*pFuncMember)(Vector<String>&);

public:
    ConsoleParser(Context *context = gContext);

    enum Parameter
    {
        None,
        Int,
        Float
    };

    struct ParserStruct
    {
        String command;
        pFuncMember func;
        String help;
        String fullHelp[10];        // Здесь хранится подробная информация о команде.
        Parameter typeParameter;
    };

    static HashMap<String, ParserStruct> commands;

    static void Init();
    void Execute(const String &string);

private:
    bool serverRunning = false;     // При запуске сервера это значение устанавливается в truе, потому что остановить сервер может только тот 
                                    // экземпляр, который его запустил

    bool FuncHelp(Vector<String> &);
    bool FuncClear(Vector<String> &);
    bool FuncClose(Vector<String> &);
    bool FuncExit(Vector<String> &);
    bool FuncStart(Vector<String> &);
    bool FuncClient(Vector<String> &);
    bool FuncServer(Vector<String> &);
    bool FuncServerStart(Vector<String> &);
    bool FuncVars(Vector<String> &);

    bool BeginFrom(String &str, char *begin);
    bool ExtractInt(String &str, int *value);           // Считывает целое значение после первого символа ':'
    bool ExtractFloat(String &str, float *value);       // Считывает значение типа float после первого символа ':'

    void HandleAsyncExecFinished(StringHash, VariantMap&);

    DEFAULT_MEMBERS(ConsoleParser);
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

    DEFAULT_MEMBERS(ConsoleRTS);
};
