#include <stdafx.h>


#include "GUI/GUI.h"
#include "Cursor.h"


tvCursor::tvCursor() : Object(gContext)
{
    cursor = new Cursor(gContext);

    tvImage image(50, 50);

    image.Clear({0.0f, 0.0f, 1.0f, 1.0f});

    cursor->DefineShape("Normal", image.GetImage(), {0, 0, 50, 50}, {0, 0});
    gUI->SetCursor(cursor);
    cursor->SetPosition(gGraphics->GetWidth() / 2, gGraphics->GetHeight() / 2);

    shapes = new tvCursorShapes();
}

void tvCursor::Show()
{
    hidden = false;
}

void tvCursor::Hide()
{
    hidden = true;
}

SharedPtr<Cursor> tvCursor::GetCursor()
{
    return cursor;
}

void tvCursor::Update(float dT)
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
        SharedPtr<tvImage> image(new tvImage(1, 1));
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

        if(!gGUI->MenuIsVisible())
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
        SharedPtr<tvImage> image = shapes->GetShape(type, type <= TypeCursor_Selected ? (int)(angle0) : numFrame);
        cursor->DefineShape("Normal", image->GetImage(), {0, 0, image->GetWidth(), image->GetHeight()}, image->GetHotSpot());
    }
}

void tvCursor::SetNormal()
{
    selected = false;
}

void tvCursor::SetSelected()
{
    selected = true;
}