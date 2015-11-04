#include <stdafx.h>


#include "Label.h"


Label::Label(UContext *context) :
    UText(context)
{
    SubscribeToEvent(Urho3D::E_CHANGELANGUAGE, HANDLER(Label, HandleChangeLanguage));
}

void Label::RegisterObject(UContext *context)
{
    context->RegisterFactory<Label>("UI");

    COPY_BASE_ATTRIBUTES(UText);
}

SharedPtr<Label> Label::Create(char *text_, int sizeFont, int width /* = -1 */, int height /* = -1 */, Urho3D::HorizontalAlignment ha, Urho3D::VerticalAlignment va)
{
    SharedPtr<Label> text(new Label(gContext));
    text->text = text_;
    text->SetFont(gFont, sizeFont);
    text->SetAlignment(ha, va);

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

    UText::SetText(gLocalization->Get(text));
}

void Label::HandleChangeLanguage(StringHash, VariantMap&)
{
    UText::SetText((char*)gLocalization->Get(text).CString());
}
