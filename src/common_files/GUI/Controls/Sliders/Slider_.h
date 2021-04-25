// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class SliderT : public Slider
{
    URHO3D_OBJECT(SliderT, Slider);

public:
    SliderT(Context *);
    static void RegisterObject();

    static SharedPtr<SliderT> Create(Window *window, pchar text);
};
