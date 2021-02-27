// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class ConsoleParser : public Object
{
    URHO3D_OBJECT(ConsoleParser, Object);

    typedef bool (ConsoleParser::*pFuncMember)(Vector<String>&, bool);  // Если второй параметр == true, то выводим информацию о команде, иначе - выполняем

public:
    ConsoleParser(Context *context = TheContext);

    enum Parameter
    {
        None,
        Int,
        Float
    };

    struct ParserStruct
    {
        char* command; //-V122
        Parameter typeParameter;
        pFuncMember func; //-V122
        String help;
    };

    void Execute(const String &string);

private:
    bool serverRunning = false;     // При запуске сервера это значение устанавливается в truе, потому что остановить сервер может только тот 
                                    // экземпляр, который его запустил

    bool FuncClient(Vector<String> &, bool);
    bool FuncClientStart(Vector<String> &, bool);
    bool FuncClientStop(Vector<String> &, bool);

    bool FuncServer(Vector<String> &, bool);
    bool FuncServerStart(Vector<String> &, bool);
    bool FuncServerStop(Vector<String> &, bool);
    bool FuncServerLatency(Vector<String> &, bool);
    bool FuncServerPacketLoss(Vector<String> &, bool);

    bool FuncVars(Vector<String> &, bool);
    bool FuncVarsOpen(Vector<String> &, bool);
    bool FuncVarsClose(Vector<String> &, bool);

    bool FuncUnit(Vector<String> &, bool);
    bool FuncUnitCamera(Vector<String> &, bool);

    bool FuncClear(Vector<String> &, bool);
    bool FuncClose(Vector<String> &, bool);
    bool FuncExit(Vector<String> &, bool);

    bool ShowBriefHelp(const ParserStruct *structs, const Vector<String> &words);
    bool ShowFullHelp(const ParserStruct *structs, Vector<String> &words);
    bool ExecuteCommand(const ParserStruct *structs, Vector<String> &words);
    bool Run(const ParserStruct *str, Vector<String> &words, bool showInfo);
    bool BeginFrom(const String &str, const char *begin);
    bool ExtractInt(const String &str, int *value);           // Считывает целое значение после первого символа ':'
    bool ExtractFloat(const String &str, float *value);       // Считывает значение типа float после первого символа ':'

    void HandleAsyncExecFinished(StringHash, VariantMap&);
};



class History
{
public:
    History();
    ~History();
    void AddString(const String &string);
    String GetPrev();
    String GetNext();
private:
    Vector<String> strings;
    int position = 0;
};



class ConsoleT : public WindowT
{
    URHO3D_OBJECT(ConsoleT, WindowT);

public:
    ConsoleT(Context *context = TheContext);
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
};
