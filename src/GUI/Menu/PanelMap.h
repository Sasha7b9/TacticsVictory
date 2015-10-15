#pragma once


class tvPanelMap : public tvWindow
{
    OBJECT(tvPanelMap);

public:
    tvPanelMap(Context *context);

    virtual void Update(float timeStep);

    static void RegisterObject(Context *context);

    void Toggle();

private:
    tvPanelMap& operator=(const tvPanelMap&)
    {};

    Vector<Vector<float> > map;
    SharedPtr<tvLineTranslator2D> translator;
    SharedPtr<tvImage> imageMap;
    int x0 = 0;
    int y0 = 0;
    float scale = 0.0f;
    bool first = true;

    float GetMapHeight(uint x, uint y);
    float GetMaxHeight();
    uint SizeXMap();
    uint SizeYMap();
    bool FindIntersectionX0Z(const Vector2 &screenPoint, Vector2 &hitPoint);
};