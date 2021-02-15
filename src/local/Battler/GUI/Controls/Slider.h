#pragma once



class lSlider : public Slider
{
    URHO3D_OBJECT(lSlider, Slider);

public:
    lSlider(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);
    static SharedPtr<lSlider> Create(Window *window, char *text);

private:
    DEFAULT_MEMBERS(lSlider);
};
