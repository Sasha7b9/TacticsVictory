#pragma once


class vSlider : public Slider
{
    OBJECT(vSlider);
public:
    vSlider(Context *context);

    static void RegisterObject(Context *context);
    static SharedPtr<vSlider> Create(Window *window, char *text);

private:
    vSlider& operator=(const vSlider&)
    {};
};