// 2021/04/13 19:09:39 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Hangar.h"


void Hangar::HandlerPostRenderUpdate(StringHash, VariantMap &)
{

}


void Hangar::HandlerKeyDown(StringHash, VariantMap &eventData)
{
    int key = eventData[KeyDown::P_KEY].GetInt();

    TheUIRoot->RemoveChild(TheHint);

    if (KEY_IS_F1)
    {
        if (TheConsole)
        {
            TheConsole->Toggle();
        }
        return;
    }

    if (KEY_IS_F10)
    {
        TheDebugHud->ToggleAll();
    }

    if (KEY_IS_F11)
    {
        if (TheEngineConsole)
        {
            TheEngineConsole->Toggle();
        }
        return;
    }

    if (KEY_IS_ESC)
    {
        if (TheEngineConsole && TheEngineConsole->IsVisible())
        {
            TheEngineConsole->SetVisible(false);
        }
        else if (TheConsole && TheConsole->IsVisible())
        {
            TheConsole->Toggle();
        }
    }

    if (!TheConsole->IsActive())
    {
        if (TheMenu->ProcessingKey(key))             // ≈сли меню обработало нажатие
        {
            return;                                 // следовательно, оно активно, поэтому после обработки выходим
        }
    }

    if (!TheUI->GetFocusElement())
    {
        if (KEY_IS_9)
        {
            Image screenshot(context_);
            TheGraphics->TakeScreenShot(screenshot);
            screenshot.SavePNG(TheFileSystem->GetProgramDir() + "Data/Screenshot_" +
                Time::GetTimeStamp().Replaced(':', '_').Replaced('.', '_').Replaced(' ', '_') + ".png");
        }
        if (KEY_IS_SPACE)
        {
            drawDebug = !drawDebug;
        }
    }
}


void Hangar::HandlerMenuEvent(StringHash, VariantMap &)
{

}
