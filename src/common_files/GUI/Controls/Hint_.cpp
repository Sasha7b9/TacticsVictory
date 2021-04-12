// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Hint_.h"
#include "GUI/Controls/Label_.h"


Hint::Hint(char *text_) : WindowT(TheContext), text(text_)
{
    label = Label::Create(text, 20);
    label->SetAlignment(HA_CENTER, VA_CENTER);
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
