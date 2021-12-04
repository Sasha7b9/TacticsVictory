// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Console.h"
#include "GUI/Mutators/MovementMutator.h"
#include "Settings.h"


using namespace Pi;


LineEdit* Console::lineEdit = nullptr;
static MovementMutator *mutator = nullptr;


Console::Console(const Vector2D &size) : 
    DrawingWidget(size), 
    Singleton<Console>(TheConsole) 
{
    keyboardEventHandler = new KeyboardEventHandler(&OnKeyboardEvent, this);
    TheEngine->InstallKeyboardEventHandler(keyboardEventHandler);

    DrawRectangle(0.0f, 0.0f, SET::GUI::CONSOLE::SIZE().x - 1.0f, SET::GUI::CONSOLE::SIZE().y - 1.0f);

    mutator = new MovementMutator(Point2D(0.0f, 0.0f), Point2D(0.0f, -SET::GUI::CONSOLE::SIZE().y), Vector2D(0.0f, -SET::GUI::PANEL::SPEED()));
    AddMutator(mutator);

    static const float delta = 4.0f;
    static const float heightLineEdit = 20.0f;
    lineEdit = new LineEdit(Vector2D(SET::GUI::CONSOLE::SIZE().x - delta * 2.0f, heightLineEdit));
    lineEdit->SetWidgetPosition(Point2D(delta, SET::GUI::CONSOLE::SIZE().y - heightLineEdit - delta));
    AppendNewSubnode(lineEdit);
    

    EndScene();
}

Console::~Console()
{
    SAFE_DELETE(keyboardEventHandler);
    SAFE_DELETE(lineEdit);
    RemoveMutator(mutator);
    SAFE_DELETE(mutator);
    
}

void Console::Toggle()
{
    Mutator *_mutator = GetFirstMutator();
    if (_mutator)
    {
        static_cast<MovementMutator*>(_mutator)->Toggle();
        isOpen = !isOpen;
    }

//    isOpen ? CaptureKeyboard() : ReleaseKeyboard();
}

void Console::ReleaseKeyboard()
{
    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Automatic);
 //   TheInputMgr->SetInputMode(InputMode::Inactive);
}

void Console::CaptureKeyboard()
{
    TheInterfaceMgr->SetInputManagementMode(InputManagementMode::Manual);
    TheInputMgr->SetInputMode(InputMode::MouseActive);
}

bool Console::OnKeyboardEvent(const KeyboardEventData *eventData, void*)
{
    lineEdit->HandleKeyboardEvent(eventData);
    return false;
}
