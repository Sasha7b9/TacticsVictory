#pragma once


#include "GUI/Elements/Window.h"


class vPanelMap : public vWindow
{
    OBJECT(vPanelMap);

public:
    vPanelMap(Context *context);

    virtual void Update(float timeStep);

    static void RegisterObject(Context *context);

    void Toggle();

private:
    vPanelMap& operator=(const vPanelMap&)
    {};

    Vector<Vector<float> > map;
    SharedPtr<vLineTranslator2D> translator;
    SharedPtr<vImage> imageMap;
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