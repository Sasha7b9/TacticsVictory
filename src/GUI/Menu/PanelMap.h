#pragma once


#include "GUI/Elements/Window.h"


class lPanelMap : public lWindow
{
    OBJECT(lPanelMap);

public:
    lPanelMap(Context *context);

    virtual void Update(float timeStep);

    static void RegisterObject(Context *context);

    void Toggle();

private:
    lPanelMap& operator=(const lPanelMap&)
    {};

    Vector<Vector<float> > map;
    SharedPtr<lLineTranslator2D> translator;
    SharedPtr<lImage> imageMap;
    int x0 = 0;
    int y0 = 0;
    float scale = 0.0f;
    bool redrawMap = true;

    void HandleMouseDown(StringHash eventType, VariantMap &eventData);
    void HandleMouseMove(StringHash eventType, VariantMap &eventData);
    void HandleMapChanged(StringHash, VariantMap&);

    float GetMapHeight(uint x, uint y);
    float GetMaxHeight();
    uint SizeXMap();
    uint SizeYMap();
    bool FindIntersectionX0Z(const Vector2 &screenPoint, Vector2 &hitPoint);
};