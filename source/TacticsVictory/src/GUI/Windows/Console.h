#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleParser
{
public:
    struct ParserStruct
    {
        String command;
        pFuncBvS func;
        String help;
        String fullHelp[10];     // Здесь хранится подробная информация о команде.
    };

    static HashMap<String, ParserStruct> commands;

    static void Init();
    static bool Execute(const String &string);
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

    void HandleFinishedText(StringHash, VariantMap&);
    void HandleUnhandledKey(StringHash, VariantMap&);
    void HandleClick(StringHash, VariantMap&);
    void HandleResize(StringHash, VariantMap&);
};
