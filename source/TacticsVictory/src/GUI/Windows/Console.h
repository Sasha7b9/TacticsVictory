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
        char* command;
        Parameter typeParameter;
        pFuncMember func;
        String help;
    };

    struct ParserStructStart
    {
        String command;
        pFuncMember func;
    };

    static HashMap<String, ParserStructStart> commands;

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
    bool FuncClientStart(Vector<String> &);
    bool FuncClientStop(Vector<String> &);
    bool FuncServer(Vector<String> &);
    bool FuncServerStart(Vector<String> &);
    bool FuncServerStop(Vector<String> &);
    bool FuncServerLatency(Vector<String> &);
    bool FuncServerPacketLoss(Vector<String> &);
    bool FuncVars(Vector<String> &);

    bool Run(const ParserStruct *str, Vector<String> &words);
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
