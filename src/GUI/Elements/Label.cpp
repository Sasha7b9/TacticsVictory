#include <stdafx.h>


#include "Label.h"


Label::Label(Context *context) :
    Text(context)
{
    SubscribeToEvent(Urho3D::E_CHANGELANGUAGE, URHO3D_HANDLER(Label, HandleChangeLanguage));
}

void Label::RegisterObject(Context *context)
{
    context->RegisterFactory<Label>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(Text);
}

SharedPtr<Label> Label::Create(char *text_, int sizeFont, int width /* = -1 */, int height /* = -1 */)
{
    SharedPtr<Label> text(new Label(gContext));
    text->text = text_;
    text->SetFont(gFont, sizeFont);
    text->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);

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

    text->SetText(text_);

    return text;
}

void Label::SetText(char *text_)
{
    text = text_;

    Urho3D::Text::SetText(gLocalization->Get(text));
}

void Label::HandleChangeLanguage(StringHash, VariantMap&)
{
    Urho3D::Text::SetText((char*)gLocalization->Get(text).CString());
}
