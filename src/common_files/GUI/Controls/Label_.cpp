// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Logic/Mutator_.h"


Label::Label(Context *context) :
    Text(context)
{
    mutator = Mutator::Empty();

    SubscribeToEvent(E_CHANGELANGUAGE, URHO3D_HANDLER(Label, HandleChangeLanguage));
}


void Label::RegisterObject()
{
    TheContext->RegisterFactory<Label>("UI");

    Context *context = TheContext;

    URHO3D_COPY_BASE_ATTRIBUTES(Text);
}


SharedPtr<Label> Label::Create(pchar text_, int sizeFont, int width, int height, bool auto_translate)
{
    SharedPtr<Label> text(new Label(TheContext));

    if (!auto_translate)
    {
        text->SetVar(VAR_GUI_NO_TRANSLATE, true);
    }

    text->SetText(text_);

    text->SetFont(TheFont, (float)sizeFont);

    if(width == -1 && height == -1)
    {

    }
    else if(height == -1)
    {
        text->SetFixedWidth(width);
    }
    else if(width == -1)
    {
        text->SetFixedHeight(height);
    }
    else
    {
        text->SetFixedSize(width, height);
    }

    return text;
}


void Label::SetText(pchar t)
{
    text = t;

    Text::SetText(text);

    VariantMap variant;

    HandleChangeLanguage("", variant);
}


void Label::HandleChangeLanguage(StringHash, VariantMap&)
{
    const Variant &var = GetVar(VAR_GUI_NO_TRANSLATE);

    if (var.IsEmpty() || !var.GetBool())
    {
        Text::SetText((char *)TheLocalization->Get(text).CString());
    }
}


void Label::Update(float dT)
{
    Text::Update(dT);

    if (mutator)
    {
        mutator->Update(dT);
    }
}
