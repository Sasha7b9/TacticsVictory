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
}
