#include <stdafx.h>


#include "Slider.h"


vSlider::vSlider(Context *context) :
    Slider(context)
{

}

void vSlider::RegisterObject(Context *context)
{
    context->RegisterFactory<vSlider>("UI");

    COPY_BASE_ATTRIBUTES(Slider);
}

SharedPtr<vSlider> vSlider::Create(Window *window, char *text_)
{
    SharedPtr<Text> text(new Text(gContext));
    text->SetText(gLocalization->Get(text_));
    text->SetStyle("MainMenuButton");
    window->AddChild(text);

    SharedPtr<vSlider> slider(gUIRoot->CreateChild<vSlider>());
    slider->SetMinHeight(15);
    window->AddChild(slider);
    slider->SetRange(1.0f);
    slider->SetStyle("Slider");
    window->AddChild(slider);
    return slider;
}