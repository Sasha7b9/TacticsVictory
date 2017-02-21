#include <stdafx.h>


#include "Cursor.h"
#include "Core/Camera.h"
#include "GUI/GUI.h"
#include "GUI/Elements/CursorShapes.h"
#include "GUI/Elements/Image.h"
#include "Game/Objects/Terrain/Terrain.h"


lCursor::lCursor() : Object(gContext)
{
    cursor = new Cursor(gContext);

    int size = 100;

    SharedPtr<lImage> image(new lImage());
    image->SetSize(size, size);

    image->Clear({0.0f, 0.0f, 1.0f, 1.0f});

    cursor->DefineShape("Normal", image, {0, 0, size, size}, {0, 0});
    cursor->SetName("Cursor");
    gUI->SetCursor(cursor);
    cursor->SetPosition(gGraphics->GetWidth() / 2, gGraphics->GetHeight() / 2);

    shapes = new CursorShapes();

    nodeSprite = gScene->CreateChild("Cursor sprite");
    staticSprite = nodeSprite->CreateComponent<StaticSprite2D>();
    staticSprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f), 1.0f));
    staticSprite->SetBlendMode(BLEND_ALPHA);
    nodeSprite->SetEnabled(true);
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
        SharedPtr<lImage> image(new lImage());
        image->SetSize(1, 1);
        cursor->DefineShape("Normal", image, {0, 0, image->GetWidth(), image->GetHeight()}, {0, 0});
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
            else if (gInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
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
        static TypeCursor prevType = TypeCursor_Size;
        static int prevFrame = -1;

        if (prevType != type || prevFrame != numFrame)
        {
            prevFrame = numFrame;
            prevType = type;

            SharedPtr<lImage> image = shapes->GetShape(type, numFrame);

            cursor->DefineShape("Normal", image, {0, 0, image->GetWidth(), image->GetHeight()}, image->GetHotSpot());
            /*
            SharedPtr<Texture2D> texture(new Texture2D(gContext));
            texture->SetSize(image->GetWidth(), image->GetHeight(), D3DFMT_X8R8G8B8);
            texture->SetData(image->GetUImage());
            SharedPtr<Sprite2D> sprite(new Sprite2D(gContext));
            sprite->SetTexture(texture);
            staticSprite->SetSprite(sprite);
            nodeSprite->SetPosition({100.0f, 100.0f, -100.0f});
            */
        }
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
    RayOctreeQuery query(results, ray, RAY_TRIANGLE, M_INFINITY, DRAWABLE_GEOMETRY, VIEW_MASK_FOR_MISSILE);
    gScene->GetComponent<Octree>()->Raycast(query);

    if(results.Size())
    {
        RayQueryResult& result = results[0];
        String name = result.drawable_->GetNode()->GetName();
        if (result.drawable_->GetNode()->GetName() == NODE_TILE_PATH && results.Size() > 1)
        {
            result = results[1];
        }
        Vector3 hitPos = result.position_;
        if(hitPos_)
        {
            *hitPos_ = hitPos;
        }
        return result.drawable_;
    }

    return nullptr;
}
