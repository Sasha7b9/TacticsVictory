#include <stdafx.h>


#include "Hint.h"
#include "GUI/Elements/Label.h"


lHint::lHint(char *text_) : lWindow(), text(text_)
{
    label = lLabel::Create(text, 20);
    AddChild(label);

    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);

    SetMovable(false);

    SubscribeToEvent(Urho3D::E_CHANGELANGUAGE, HANDLER(lHint, HandleChangeLanguage));
}

void lHint::HandleChangeLanguage(StringHash, VariantMap&)
{
    label->SetText(text);
    SetSize(label->GetWidth() + 10, label->GetHeight() + 10);
}
