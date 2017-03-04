#pragma once
#include "GUI/Controls/WindowRTS.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleParser
{
    class ParserStruct
    {
    public:
        ParserStruct(pFuncBvS func_ = nullptr) : func(func_) {};
        pFuncBvS func;
    };

public:
    static HashMap<String, ParserStruct> commands;

    static void Init();
    static bool Execute(const String &string);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConsoleRTS : public WindowRTS
{
    URHO3D_OBJECT(ConsoleRTS, WindowRTS);

public:
    ConsoleRTS(Context *context);
    void Toggle();
    bool IsActive();                            // Возвращает true, если активна строка ввода

private:
    SharedPtr<LineEdit> lineEdit;
    SharedPtr<Text> text;
    SharedPtr<ScrollBar> scrollBar;

    void HandleFinishedText(StringHash, VariantMap&);
};
