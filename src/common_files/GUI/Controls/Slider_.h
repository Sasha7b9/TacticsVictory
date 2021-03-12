// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class lSlider : public Slider
{
    URHO3D_OBJECT(lSlider, Slider);

public:
    lSlider(Context *context = TheContext);

    static void RegisterObject();
    static SharedPtr<lSlider> Create(Window *window, char *text);
};
