// 2021/04/12 22:58:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


GUI::GUI(GUI **self) : GUIT((GUIT **)self)
{
    RegistrationObjects();
    Create();

    *self = this;
}


void GUI::RegistrationObjects()
{

}


void GUI::Create()
{
    TheChat = new Chat();
    TheUIRoot->AddChild(TheChat);

    TheLocalization->SetLanguage("en");

    TheCursor = TheUIRoot->CreateChild<CursorT>("CursorT");

    TheLocalization->SetLanguage(TheSettings.GetInt("language") == 0 ? "en" : "ru");
}
