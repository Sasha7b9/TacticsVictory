#include <stdafx.h>


#include "Cursor.h"
#include "Core/Camera.h"
#include "GUI/GUI.h"
#include "GUI/Elements/CursorShapes.h"
#include "GUI/Elements/Image.h"
#include "Game/Objects/Terrain.h"


lCursor::lCursor() : Object(gContext)
{
    cursor = new Cursor(gContext);

    lImage image(50, 50);

    image.Clear({0.0f, 0.0f, 1.0f, 1.0f});

    cursor->DefineShape("Normal", image.GetImage(), {0, 0, 50, 50}, {0, 0});
    gUI->SetCursor(cursor);
    cursor->SetPosition(gGraphics->GetWidth() / 2, gGraphics->GetHeight() / 2);

    shapes = new lCursorShapes();
}

void lCursor::Show()
{
    hidden = false;
}

void lCursor::Hide()
{
    hidden = true;
}

SharedPtr<Cursor> lCursor::GetCursor()
{
    return cursor;
}

void lCursor::Update(float dT)
{
    
    const float speed = 500.0f;
    static float angle0 = 0.0f;

    angle0 += speed * dT;

    if(angle0 > 360.0f)
    {
        angle0 -= 360.0f;
    }

    if(hidden)
    {
        SharedPtr<lImage> image(new lImage(1, 1));
        cursor->DefineShape("Normal", image->GetImage(), {0, 0, image->GetImage()->GetWidth(), image->GetImage()->GetHeight()}, {0, 0});
    }
    else
    {
        static const int delta = 2;
        int posX = cursor->GetPosition().x_;
        int posY = cursor->GetPosition().y_;
        int width = gGraphics->GetWidth();
        int height = gGraphics->GetHeight();
        int numFrame = (int)angle0 / 10;

        if(!gGUI->MenuIsVisible() && !gGUI->UnderCursor())
        {
            if(posX < delta && posY < delta)
            {
                type = TypeCursor_TopLeft;
            }
            else if(posX > width - delta && posY < delta)
            {
                type = TypeCursor_TopRight;
            }
            else if(posX > width - delta && posY > height - delta)
            {
                type = TypeCursor_DownRight;
            }
            else if(posX < delta && posY > height - delta)
            {
                type = TypeCursor_DownLeft;
            }
            else if(posX < delta)
            {
                type = TypeCursor_Left;
            }
            else if(posX > width - delta)
            {
                type = TypeCursor_Right;
            }
            else if(posY < delta)
            {
                type = TypeCursor_Up;
            }
            else if(posY > height - delta && !gGUI->GheckOnDeadZoneForCursorBottomScreen(posX))
            {
                type = TypeCursor_Down;
            }
            else if (gInput->GetMouseButtonDown(Urho3D::MOUSEB_RIGHT | Urho3D::MOUSEB_MIDDLE))
            {
                static float thisNumFrame = 0.0f;
                int dX = gInput->GetMouseMoveX();
                int dY = gInput->GetMouseMoveY();
                thisNumFrame += (float)sqrt(dY * dY + dX * dX) / 10.0f;
                if(thisNumFrame < 0.0f)
                {
                    thisNumFrame = 36.0f;
                }
                else if(thisNumFrame > 36.0f)
                {
                    thisNumFrame = 0.0f;
                }
                numFrame = (int)thisNumFrame;
                type = TypeCursor_Busy;
            }
            else
            {
                type = selected ? TypeCursor_Selected : TypeCursor_Normal;
            }
        }
        else
        {
            type = selected ? TypeCursor_Selected : TypeCursor_Normal;
        }
        SharedPtr<lImage> image = shapes->GetShape(type, type <= TypeCursor_Selected ? (int)(angle0) : numFrame);
        cursor->DefineShape("Normal", image->GetImage(), {0, 0, image->GetWidth(), image->GetHeight()}, image->GetHotSpot());
    }
}

void lCursor::SetNormal()
{
    selected = false;
}

void lCursor::SetSelected()
{
    selected = true;
}

Drawable* lCursor::GetRaycastNode(Vector3 *hitPos_)
{
    if(gUI->GetElementAt(gUI->GetCursorPosition(), true))
    {
        return nullptr;
    }

    Ray ray = gCamera->GetCursorRay();
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, ray, Urho3D::RAY_TRIANGLE, Urho3D::M_INFINITY, Urho3D::DRAWABLE_GEOMETRY);
    gScene->GetComponent<Octree>()->RaycastSingle(query);

    if(results.Size())
    {
        RayQueryResult& result = results[0];
        Vector3 hitPos = result.position_;
        if(hitPos_)
        {
            *hitPos_ = hitPos;
        }
        return result.drawable_;
    }

    return nullptr;
}
