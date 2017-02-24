#include <stdafx.h>
#include "Hint.h"
#include "GUI/Elements/Label.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Hint::Hint(char *text_) : WindowRTS(), text(text_)
{
    label = Label::Create(text, 20);
    AddChild(label);

    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);

    SetMovable(false);

    SubscribeToEvent(E_CHANGELANGUAGE, URHO3D_HANDLER(Hint, HandleChangeLanguage));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Hint::HandleChangeLanguage(StringHash, VariantMap&)
{
    label->SetText(text);
    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);
}
