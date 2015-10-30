#pragma once


class vSlider : public Slider
{
    OBJECT(vSlider);
public:
    vSlider(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);
    static SharedPtr<vSlider> Create(Window *window, char *text);

private:
    vSlider& operator=(const vSlider&)
    {};
};