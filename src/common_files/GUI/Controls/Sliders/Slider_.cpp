// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/Sliders/Slider_.h"


SliderT::SliderT(Context *context) :
    Slider(context)
{

}


void SliderT::RegisterObject()
{
    TheContext->RegisterFactory<SliderT>("UI");

    Context *context = TheContext;

    URHO3D_COPY_BASE_ATTRIBUTES(Slider);
}


SharedPtr<SliderT> SliderT::Create(Window *window, char *text_)
{
    SharedPtr<Text> text(new Text(TheContext));
    text->SetText(TheLocalization->Get(text_));
    text->SetStyle("MainMenuButton");
    window->AddChild(text);

    SharedPtr<SliderT> slider(TheUIRoot->CreateChild<SliderT>());
    slider->SetMinHeight(15);
    window->AddChild(slider);
    slider->SetRange(1.0f);
    slider->SetStyle("Slider");
    window->AddChild(slider);
    return slider;
}
