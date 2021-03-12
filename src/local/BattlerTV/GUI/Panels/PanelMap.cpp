// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/2D/Image.h"
#include "GUI/Cursor.h"
#include "GUI/Panels/PanelMap.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"
#include "Utils/Settings.h"


PanelMap::PanelMap(Context *context) :
    WindowT(context)
{
    SetName("PanelMap");

    SetFixedSize(SET::PANEL::MAP::SIZE);

    SetMovable(false);

    IntVector2 posStart = {0, TheGraphics->GetHeight() - SET::PANEL::BOTTOM::HEIGHT - SET::PANEL::MAP::HEIGHT + 1};
    IntVector2 posFinish = {-SET::PANEL::MAP::WIDTH, posStart.y_};

    translator = new LineTranslator2D(posStart, posFinish, TheSet->GetFloat(TV_PANEL_SPEED), LineTranslator2D::State_PointStart);

    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(PanelMap, HandleMouseDown));
    SubscribeToEvent(E_MOUSEMOVE, URHO3D_HANDLER(PanelMap, HandleMouseMove));
    SubscribeToEvent(E_MAP_CHANGED, URHO3D_HANDLER(PanelMap, HandleMapChanged));
}


void PanelMap::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<PanelMap>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowT);
}


void PanelMap::Update(float dT)
{
    SetPosition(translator->Update(dT));

    if (!parent_->IsVisible() || !IsVisible())
    {
        return;
    }
    
    if(redrawMap)
    {
        map = TheTerrain->level->map;

        redrawMap = false;

        uint sizeX = SizeXMap();
        uint sizeY = SizeYMap();

        uint sizeMap = sizeX > sizeY ? sizeX : sizeY;

        imageMap = new ImageT(TheContext);
        imageMap->SetSize((int)sizeMap, (int)sizeMap);

        imageMap->Clear(Color::BLACK);

        float maxHeight = GetMaxHeight();
        float stand = 0.0f;
        float scaleColor = (1.0f - stand) / maxHeight;

        int prevX = 0;
        int prevY = 0;
        int posX = 0;

        uint X0 = 0, Y0 = 0;

        if(sizeX < sizeMap)
        {
            X0 = (sizeMap - sizeX) / 2;
        }
        if(sizeY < sizeMap)
        {
            Y0 = (sizeMap - sizeY) / 2;
        }

        for(uint x = 0; x < sizeX; x++)
        {
            for(uint y = 0; y < sizeY; y++)
            {
                posX = (int)(X0 + x);
                int posY = (int)(Y0 + y);
                float color = GetMapHeight(x, y) * scaleColor;
                Color col = {stand + color, stand + color, stand + color};

                {
                    imageMap->SetPoint(posX, posY, col);
                }
                prevY = posY;
            }
            prevX = posX;
        }

        imageMap->Resize(GetWidth(), GetHeight());

        imageMap->DrawRectangle(0, 0, GetWidth() - 1, GetHeight() - 1, Color::WHITE);
    }

    Vector2 points[4] =
    {
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f}
    };

    SharedPtr<ImageT> image(new ImageT(TheContext));
    image->SetSize(imageMap->GetWidth(), imageMap->GetHeight());

    uchar *data = imageMap->GetData();

    image->SetData(data);

    uint sizeX = SizeXMap();
    uint sizeY = SizeYMap();

    float scaleX = (GetWidth() - 2) / (float)sizeX;
    float scaleY = (GetHeight() - 2) / (float)sizeY;

    scale = scaleY;

    if(scaleX < scaleY)
    {
        scale = scaleX;

        x0 = 0;
        y0 = (int)(GetHeight() / 2.0f - (scale * sizeY) / 2.0f);
    }
    else
    {
        x0 = (int)(GetWidth() / 2.0f - (scale * sizeX) / 2.0f);
        y0 = 0;
    }

#define DRAW_LINE(p0, p1)                                                   \
    image->DrawLine((int)(x0 + p0.x_ * scale), (int)(y0 - p0.y_ * scale),   \
                    (int)(x0 + p1.x_ * scale), (int)(y0 - p1.y_ * scale), Color::BLUE);

    Vector2 point0;
    if(FindIntersectionX0Z(points[0], point0))
    {
        Vector2 point1;
        if(FindIntersectionX0Z(points[1], point1))
        {
            DRAW_LINE(point0, point1);
            Vector2 point2;
            if(FindIntersectionX0Z(points[2], point2))
            {
                DRAW_LINE(point1, point2);
                Vector2 point3;
                if(FindIntersectionX0Z(points[3], point3))
                {
                    DRAW_LINE(point2, point3);
                    DRAW_LINE(point3, point0);
                }
            }
        }
    }

    SharedPtr<Texture2D> texture(new Texture2D(TheContext));

    texture->SetSize(GetWidth(), GetHeight(), D3DFMT_X8R8G8B8);
    texture->SetData((SharedPtr<Image>)image);

    SetTexture(texture);
    SetFullImageRect();
}


bool PanelMap::FindIntersectionX0Z(const Vector2 &screenPoint, Vector2 &hitPointOut)
{
    Camera *camera = TheCamera->GetNode()->GetComponent<Camera>();
    Plane planeX0Z({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f});
    Ray ray = camera->GetScreenRay(screenPoint.x_, screenPoint.y_);
    float distanceHit = ray.HitDistance(planeX0Z);
    if(fabs(distanceHit - M_INFINITY) > M_EPSILON)
    {
        return false;
    }
    Vector3 hitPoint = camera->ScreenToWorldPoint({screenPoint.x_, screenPoint.y_, distanceHit});
    hitPointOut.x_ = hitPoint.x_;
    hitPointOut.y_ = hitPoint.z_;
    return true;
}


float PanelMap::GetMapHeight(uint x, uint y)
{
    return map[y][x];
}


float PanelMap::GetMaxHeight()
{
    uint sizeX = SizeXMap();
    uint sizeY = SizeYMap();

    float height = 0.0f;

    for(uint x = 0; x < sizeX; x++)
    {
        for(uint y = 0; y < sizeY; y++)
        {
            if(GetMapHeight(x, y) > height)
            {
                height = GetMapHeight(x, y);
            }
        }
    }

    return height;
}


uint PanelMap::SizeXMap()
{
    return map.Empty() ? 0 : map[0].Size();
}


uint PanelMap::SizeYMap()
{
    return map.Empty() ? 0 : map.Size();
}


void PanelMap::HandleMouseDown(StringHash, VariantMap &eventData)
{
    if (parent_->IsVisible() && IsInside(TheCursor->GetCursor()->GetPosition(), true))
    {
        int buttns = (int)eventData[MouseButtonDown::P_BUTTONS].GetInt();

        if (buttns == MOUSEB_RIGHT)
        {
            IntVector2 coordMap = TheCursor->GetCursor()->GetPosition() - GetPosition();

            float xSpace = (coordMap.x_ - x0) / scale;
            float zSpace = -(coordMap.y_ - y0) / scale;

            TheCamera->ParallelTranslateLookAt({xSpace, 0.0f, zSpace});
        }
    }
}


void PanelMap::HandleMouseMove(StringHash eventType, VariantMap &eventData)
{
    if (IsInside(TheCursor->GetCursor()->GetPosition(), true) && (int)eventData[MouseMove::P_BUTTONS].GetInt() == MOUSEB_RIGHT)
    {
        eventData = GetEventDataMap();
        eventData[MouseButtonDown::P_BUTTONS] = MOUSEB_RIGHT;
        HandleMouseDown(eventType, eventData);
    }
}


void PanelMap::HandleMapChanged(StringHash, VariantMap&)
{
    redrawMap = true;
}
