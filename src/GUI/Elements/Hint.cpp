#include <stdafx.h>


#include "Hint.h"
#include "GUI/Elements/Label.h"


lHint::lHint(char *text_) : lWindow(), text(text_)
{
    SharedPtr<lLabel> label(lLabel::Create(text, 20));
    AddChild(label);

    SetFixedSize(label->GetWidth() + 10, label->GetHeight() + 10);

    SetMovable(false);
}