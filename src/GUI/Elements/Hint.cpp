#include <stdafx.h>


#include "Hint.h"
#include "GUI/Elements/Label.h"


Hint::Hint(char *text_) : lWindow(), text(text_)
{
    label = Label::Create(text, 20);
    AddChild(label);

    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);

    SetMovable(false);

    SubscribeToEvent(Urho3D::E_CHANGELANGUAGE, HANDLER(Hint, HandleChangeLanguage));
}

void Hint::HandleChangeLanguage(StringHash, VariantMap&)
{
    label->SetText(text);
    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);
}
