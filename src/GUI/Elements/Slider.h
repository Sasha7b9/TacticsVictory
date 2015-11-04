#pragma once


class vSlider : public Slider
{
    OBJECT(vSlider);
public:
    vSlider(UContext *context = gContext);

    static void RegisterObject(UContext *context = gContext);
    static SharedPtr<vSlider> Create(Window *window, char *text);

private:
    vSlider& operator=(const vSlider&)
    {};
};