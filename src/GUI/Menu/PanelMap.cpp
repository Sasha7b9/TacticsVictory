#include <stdafx.h>


#include "PanelMap.h"
#include "Core/Camera.h"
#include "Game/Level.h"
#include "GUI/Elements/Image.h"
#include "GUI/Elements/Cursor.h"
#include "GUI/Logic/LineTranslator2D.h"


lPanelMap::lPanelMap(Context *context) :
    lWindow(context)
{
    SetName("PanelMap");

    SetFixedSize(SET::PANEL::MAP::SIZE);

    SetMovable(false);

    IntVector2 posStart = {0, gGraphics->GetHeight() - SET::PANEL::BOTTOM::HEIGHT - SET::PANEL::MAP::HEIGHT + 1};
    IntVector2 posFinish = {-SET::PANEL::MAP::WIDTH, posStart.y_};

    translator = new lLineTranslator2D(posStart, posFinish, gSet->GetFloat(TV_PANEL_SPEED), lLineTranslator2D::State_PointStart);

    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, HANDLER(lPanelMap, HandleMouseDown));
    SubscribeToEvent(Urho3D::E_MOUSEMOVE, HANDLER(lPanelMap, HandleMouseMove));
}


void lPanelMap::RegisterObject(Context *context)
{
    context->RegisterFactory<lPanelMap>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}

void lPanelMap::Toggle()
{
    translator->Toggle();
}

void lPanelMap::Update(float dT)
{
    SetPosition(translator->Update(dT));

    if (!parent_->IsVisible())
    {
        return;
    }
    
    if(first)
    {
        map = vLevel::Get();

        if(map.Empty())
        {
            return;
        }

        first = false;

        uint sizeX = SizeXMap();
        uint sizeY = SizeYMap();

        float scaleX = (GetWidth() - 2) / (float)sizeX;
        float scaleY = (GetHeight() - 2) / (float)sizeY;

        scale = scaleX < scaleY ? scaleX : scaleY;

        if(scaleX < scaleY)
        {
            y0 = (int)(GetHeight() / 2.0f - (scale * sizeY) / 2.0f);
        }
        else
        {
            x0 = (int)(GetWidth() / 2.0f - (scale * sizeX) / 2.0f);
        }

        imageMap = new lImage(GetWidth(), GetHeight());

        imageMap->Clear(Color::BLACK);
        imageMap->DrawRectangle(0, 0, GetWidth() - 1, GetHeight() - 1, Color::WHITE);


        float maxHeight = GetMaxHeight();
        float stand = 0.0f;
        float scaleColor = (1.0f - stand) / maxHeight;

        int prevX = 0;
        int prevY = 0;
        int posX = 0;

        for(uint x = 0; x < sizeX; x++)
        {
            for(uint y = 0; y < sizeY; y++)
            {
                posX = (int)((float)x0 + scale * x + 0.5f);
                int posY = (int)((float)y0 + scale * y + 0.5f);
                float color = GetMapHeight(x, y) * scaleColor;
                Color col = {stand + color, stand + color, stand + color};

                //if(prevY + 1 == posY)
                {
                    imageMap->SetPoint(1 + posX, 1 + posY, col);
                }
                /*
                else
                {
                image->FillRectangle(prevX + 1, prevY + 1, posX - prevX - 1, posY - prevY - 1, col);
                }
                */
                prevY = posY;
            }
            prevX = posX;
        }
    }

    Vector2 points[4] =
    {
        {1.0f, 1.0f},
        {0.0f, 1.0f},
        {0.0f, 0.0f},
        {1.0f, 0.0f}
    };

    SharedPtr<lImage> image(new lImage(imageMap->GetWidth(), imageMap->GetHeight()));

    uchar *data = imageMap->GetImage()->GetData();

    image->GetImage()->SetData(data);

#define DRAW_LINE(p0, p1)   \
    image->DrawLine((int)(x0 + p0.x_ * scale), (int)(y0 - p0.y_ * scale), (int)(x0 + p1.x_ * scale), (int)(y0 - p1.y_ * scale), Color::WHITE);

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

    SharedPtr<Texture2D> texture(new Texture2D(gContext));
    texture->SetSize(GetWidth(), GetHeight(), D3DFMT_X8R8G8B8);
    texture->SetData(image->GetImage());

    SetTexture(texture);
    SetFullImageRect();
}

bool lPanelMap::FindIntersectionX0Z(const Vector2 &screenPoint, Vector2 &hitPointOut)
{
    Camera *camera = gCamera->GetNode()->GetComponent<Camera>();
    Plane planeX0Z({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f});
    Ray ray = camera->GetScreenRay(screenPoint.x_, screenPoint.y_);
    float distanceHit = ray.HitDistance(planeX0Z);
    if(distanceHit == Urho3D::M_INFINITY)
    {
        return false;
    }
    Vector3 hitPoint = camera->ScreenToWorldPoint({screenPoint.x_, screenPoint.y_, distanceHit});
    hitPointOut.x_ = hitPoint.x_;
    hitPointOut.y_ = hitPoint.z_;
    return true;
}

float lPanelMap::GetMapHeight(uint x, uint y)
{
    return map[y][x];
}

float lPanelMap::GetMaxHeight()
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

uint lPanelMap::SizeXMap()
{
    return map[0].Size();
}

uint lPanelMap::SizeYMap()
{
    return map.Size();
}

void lPanelMap::HandleMouseDown(StringHash, VariantMap &eventData)
{
    if (parent_->IsVisible() && IsInside(gCursor->GetCursor()->GetPosition(), true))
    {
        int buttons = (int)eventData[Urho3D::MouseButtonDown::P_BUTTONS].GetInt();

        if (buttons == Urho3D::MOUSEB_RIGHT)
        {
            IntVector2 coordMap = gCursor->GetCursor()->GetPosition() - GetPosition();

            float xSpace = (coordMap.x_ - x0) / scale;
            float zSpace = -(coordMap.y_ - y0) / scale;

            gCamera->ParallelTranslateLookAt({xSpace, 0.0f, zSpace});
        }
    }
}

void lPanelMap::HandleMouseMove(StringHash eventType, VariantMap &eventData)
{
    if (parent_->IsVisible() && IsInside(gCursor->GetCursor()->GetPosition(), true) && (int)eventData[Urho3D::MouseMove::P_BUTTONS].GetInt() == Urho3D::MOUSEB_RIGHT)
    {
        eventData = GetEventDataMap();
        eventData[Urho3D::MouseButtonDown::P_BUTTONS] = Urho3D::MOUSEB_RIGHT;
        HandleMouseDown(eventType, eventData);
    }
}