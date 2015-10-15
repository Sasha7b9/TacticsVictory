#pragma once


class tvSlider : public Slider
{
    OBJECT(tvSlider);
public:
    tvSlider(Context *context);

    static void RegisterObject(Context *context);
    static SharedPtr<tvSlider> Create(Window *window, char *text);

private:
    tvSlider& operator=(const tvSlider&)
    {};
};