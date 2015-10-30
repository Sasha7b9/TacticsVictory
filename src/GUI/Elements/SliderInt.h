#pragma once


EVENT(E_SLIDERINTCHANGED, SliderIntChanged)
{
    PARAM(P_ELEMENT, Element);
    PARAM(P_VALUE, Value);
}


class lSliderInt : public Slider
{
    OBJECT(lSliderInt);
public:
    lSliderInt(Context *context = gContext);

    static void RegisterObject(Context* context = gContext);
    static SharedPtr<lSliderInt> Create(UIElement *uielement, const IntVector2 &size);

    void SetRange(int min, int max, int step = 1);
    virtual void OnDragMove(const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, int buttons, int qualifiers, Cursor* cursor);
    int GetValueInt();
    int GetValueMax();
    int GetValueMin();
    void SetValueInt(int value);
    void Increase();
    void Decrease();

private:
    lSliderInt& operator=(const lSliderInt&)
    {};

    int min = 0;
    int max = 100;
    int value = 0;
    int step = 1;
    float delta = 0.0f;     // –азница между минимальным значением и нулЄм(минимальным значением родительского Slider)
};