#include <stdafx.h>


tvSlider::tvSlider(Context *context) :
    Slider(context)
{

}

void tvSlider::RegisterObject(Context *context)
{
    context->RegisterFactory<tvSlider>("UI");

    COPY_BASE_ATTRIBUTES(Slider);
}

SharedPtr<tvSlider> tvSlider::Create(Window *window, char *text_)
{
    SharedPtr<Text> text(new Text(gContext));
    text->SetText(gLocalization->Get(text_));
    text->SetStyle("MainMenuButton");
    window->AddChild(text);

    SharedPtr<tvSlider> slider(gUIRoot->CreateChild<tvSlider>());
    slider->SetMinHeight(15);
    window->AddChild(slider);
    slider->SetRange(1.0f);
    slider->SetStyle("Slider");
    window->AddChild(slider);
    return slider;
}