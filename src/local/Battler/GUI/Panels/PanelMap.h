// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Controls/WindowRTS.h"



class ImageRTS;



/*
    Эта панель расположена в правом нижнем углу - миникарта
*/
class PanelMap : public WindowRTS
{
    URHO3D_OBJECT(PanelMap, WindowRTS);

public:
    PanelMap(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

    virtual void Update(float timeStep);

private:
    Vector<Vector<float> > map;
    SharedPtr<ImageRTS> imageMap;
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

    DEFAULT_MEMBERS(PanelMap);
};
