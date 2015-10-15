#include <stdafx.h>


struct StructText
{
    tvLabel* label;
    const char* text;
};


static PODVector<StructText> mapTexts;  // »спользуетс€ дл€ перезагрузки при изменении €зыка


void tvLabel::ReloadLanguage()
{
    for(PODVector<StructText>::Iterator i = mapTexts.Begin(); i != mapTexts.End(); i++)
    {
        i->label->SetText(gLocalization->Get(i->text));
    }
}


tvLabel::tvLabel(Context *context) :
    Text(context)
{

}

void tvLabel::RegisterObject(Context *context)
{
    context->RegisterFactory<tvLabel>("UI");

    COPY_BASE_ATTRIBUTES(Text);
}

SharedPtr<tvLabel> tvLabel::Create(char *text_, int sizeFont, int width /* = -1 */, int height /* = -1 */)
{
    SharedPtr<tvLabel> text(new tvLabel(gContext));
    text->SetFont(gFont, sizeFont);
    text->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);

    StructText str = {text, text_};
    mapTexts.Push(str);

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

    text->SetText(gLocalization->Get(text_));

    return text;
}

void tvLabel::SetNewText(const char *text)
{
    for(uint i = 0; i < mapTexts.Size(); i++)
    {
        if(mapTexts[i].label == this)
        {
            mapTexts[i].text = text;
            SetText(gLocalization->Get(text));
        }
    }
}