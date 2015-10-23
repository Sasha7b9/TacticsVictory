#include <stdafx.h>


#include "Label.h"


lLabel::lLabel(Context *context) :
    Text(context)
{
    SubscribeToEvent(Urho3D::E_CHANGELANGUAGE, HANDLER(lLabel, HandleChangeLanguage));
}

void lLabel::RegisterObject(Context *context)
{
    context->RegisterFactory<lLabel>("UI");

    COPY_BASE_ATTRIBUTES(Text);
}

SharedPtr<lLabel> lLabel::Create(char *text_, int sizeFont, int width /* = -1 */, int height /* = -1 */)
{
    SharedPtr<lLabel> text(new lLabel(gContext));
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

void lLabel::SetText(char *text_)
{
    text = text_;

    Text::SetText(gLocalization->Get(text));
}

void lLabel::HandleChangeLanguage(StringHash, VariantMap&)
{
    Text::SetText((char*)gLocalization->Get(text).CString());
}
