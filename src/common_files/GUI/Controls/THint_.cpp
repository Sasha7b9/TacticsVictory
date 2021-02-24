// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/THint_.h"


Hint::Hint(char *text_) : TWindow(), text(text_)
{
    label = Label::Create(text, true, 20);
    AddChild(label);

    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);

    SetMovable(false);

    SubscribeToEvent(E_CHANGELANGUAGE, URHO3D_HANDLER(Hint, HandleChangeLanguage));
}


void Hint::HandleChangeLanguage(StringHash, VariantMap&)
{
    label->SetText(text);
    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);
}
