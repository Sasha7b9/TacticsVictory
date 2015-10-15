#pragma once


EVENT(E_SLIDERINTCHANGED, SliderIntChanged)
{
    PARAM(P_ELEMENT, Element);
    PARAM(P_VALUE, Value);
}


class tvSliderInt : public Slider
{
    OBJECT(tvSliderInt);
public:
    tvSliderInt(Context *context);

    static void RegisterObject(Context* context);
    static SharedPtr<tvSliderInt> Create(UIElement *uielement, const IntVector2 &size);

    void SetRange(int min, int max);
    virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor);
    int GetValueInt();
    void SetValueInt(int value);

private:
    tvSliderInt& operator=(const tvSliderInt&)
    {};

    int min = 0;
    int max = 100;
    int value = 0;
    float delta = 0.0f;     // –азница между минимальным значением и нулЄм(минимальным значением родительского Slider)
};