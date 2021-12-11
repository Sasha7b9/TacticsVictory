// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "PanelMap.h"
#include "Settings.h"
#include "GUI/Widgets/Button.h"
#include "Scene/World/Landscape.h"
#include "Utils/Math.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Scene/World/GameWorld.h"


using namespace Pi;


float PanelMapMutator::scale = 0.0f;
Point2D PanelMapMutator::leftTop;
PanelMap *PanelMap::self = nullptr;


PanelMap::PanelMap()
    : PanelGUI(SET::GUI::MAP::SIZE()),
    Singleton<PanelMap>(self)
{

    SetMovementMutator(Point2D((float)SET::GUI::MAP::VIEW::X(), (float)SET::GUI::MAP::VIEW::Y()),
        Point2D((float)-SET::GUI::MAP::WIDTH(), (float)SET::GUI::MAP::VIEW::Y()),
        Vector2D(-SET::GUI::PANEL::SPEED(), 0.0f));

    mutator = new PanelMapMutator(this);
    AddMutator(mutator);

    observer = new Observer<PanelMap, MouseObservable>(this, &PanelMap::HandleObserver);
    Mouse::self->AddObserver(observer);
}


PanelMap::~PanelMap()
{
    SAFE_DELETE(observer);
}


void PanelMap::HandleObserver(MouseObservable *, ::Type type)
{
    if ((uint)type == (uint)Mouse::Event::RightChanged)
    {
        Point3D position = GetWorldPosition();
        Vector2D size = GetWidgetSize();
        Point2D positionMouse = Mouse::self->GetPosition();
        if (!Mathem::PointInRect(&positionMouse, position.x, position.y, size.x, size.y))
        {
            return;
        }
        Point3D coordCamera = CameraRTS::self->GetCurrentFocus();
        Point3D coordWorld = PanelMapMutator::CoordMapToWorld({positionMouse.x - position.x, positionMouse.y - position.y});
        coordWorld.z = coordCamera.z;
        CameraRTS::self->MoveOn(coordWorld - coordCamera);
    }
}

void PanelMap::Preprocess()
{
    PanelGUI::Preprocess();
}

void PanelMap::HandleHideShow(Widget *, const WidgetEventData *)
{
    Toggle();
}


PanelMapMutator::PanelMapMutator(PanelMap *panel_) : Mutator(kMutatorPanelMap), panel(panel_)
{

}

void PanelMapMutator::Move()
{
    GameWorld *world = GameWorld::Get();

    Landscape *landscape = world->GetLandscape();
    int sizeMapX = landscape->GetSizeX_Columns();
    int sizeMapY = landscape->GetSizeY_Rows();

    float sizePanelX = panel->GetWidgetSize().x;
    float sizePanelY = panel->GetWidgetSize().y;

    float scaleX = (float)(sizePanelX - 2) / static_cast<float>(sizeMapX);
    float scaleY = (float)(sizePanelY - 2) / static_cast<float>(sizeMapY);

    scale = scaleX < scaleY ? scaleX : scaleY;

    Point2D sizeRect(scale * static_cast<float>(sizeMapX) - 1.0F, scale * static_cast<float>(sizeMapY) - 1.0F);
    leftTop = Point2D(1.0F, 1.0F);

    if (scaleX < scaleY)
    {
        leftTop.y = sizePanelY / 2 - sizeRect.y / 2;
    }
    else
    {
        leftTop.x = sizePanelX / 2 - sizeRect.x / 2;
    }

    panel->Clear();

    for (int row = 0; row < sizeMapY; row++)
    {
        for (int col = 0; col < sizeMapX; col++)
        {
            float height = landscape->GetHeightAccurately((float)col, (float)row, true);
            float r = height / 10.0F;
            if (r < 0.0F)
            {
                r = 0.0F;
            }
            if (r > 1.0F)
            {
                r = 1.0F;
            }
            float g = r;
            r /= 5.0F;
            panel->SetColorBrush(ColorRGBA(0.0F, g, 0.0F));
            if (scale > 1.0F)
            {
                panel->FillRegion(leftTop.x + static_cast<float>(col) * scale, leftTop.y + static_cast<float>(row) * scale, scale, scale);
            }
            else
            {
                float x = leftTop.x + static_cast<float>(col) * scale;
                float y = leftTop.y + static_cast<float>(row) * scale;
                panel->DrawPoint(x, y);
            }
        }
    }

    Point2D points[4] = {
        {0, 0},
        {SET::WINDOW::SIZE().x, 0},
        {SET::WINDOW::SIZE().x, SET::WINDOW::SIZE().y},
        {0, SET::WINDOW::SIZE().y}
    };
    Point3D point;

    panel->SetColorBrush(K::white);

    if (CameraRTS::self->GetIntersectionPlaneZ(points[0], &point))
    {
        Point3D point1;
        if (CameraRTS::self->GetIntersectionPlaneZ(points[1], &point1))
        {
            //            panel->DrawLine(CoordWorldToMap(point), CoordWorldToMap(point1));
            Point3D point2;
            if (CameraRTS::self->GetIntersectionPlaneZ(points[2], &point2))
            {
                //                panel->DrawLine(CoordWorldToMap(point1), CoordWorldToMap(point2));
                Point3D point3;
                if (CameraRTS::self->GetIntersectionPlaneZ(points[3], &point3))
                {
                    //                    panel->DrawLine(CoordWorldToMap(point2), CoordWorldToMap(point3));
                    //                    panel->DrawLine(CoordWorldToMap(point3), CoordWorldToMap(point));
                }
            }
        }
    }

    /*
    Point3D position = TheCamera->GetNodePosition();
    position.y = -position.y;

    position.y *= scale;
    position.x *= scale;

    panel->DrawCircle(leftTop.x + position.x, leftTop.y + position.y, 3);
    */

    panel->EndScene();
}

Point2D PanelMapMutator::CoordWorldToMap(const Point3D &coord)
{
    return Point2D(leftTop.x + coord.x * scale, leftTop.y - coord.y * scale);
}

Point3D PanelMapMutator::CoordMapToWorld(const Point2D &coord)
{
    return Point3D((coord.x - leftTop.x) / scale, -(coord.y - leftTop.y) / scale, 0.0f);
}

void PanelMapMutator::Reset()
{
    Mutator::Reset();
}

Mutator *PanelMapMutator::Replicate() const
{
    return new PanelMapMutator(*this);
}