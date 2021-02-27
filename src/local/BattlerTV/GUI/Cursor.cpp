// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/2D/Image.h"
#include "GUI/Cursor.h"
#include "GUI/GUIEvents.h"
#include "GUI/GUI.h"
#include "GUI/Menu/TMenu.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"


bool operator==(const CursorShapes::StructShape& keyLeft, const CursorShapes::StructShape& keyRight)
{
    return keyLeft.numFrame == keyRight.numFrame && keyLeft.type == keyRight.type;
}


#define border       Color::CYAN
#define transparent {0.0f, 0.0f, 0.0f, 0.0f}


TCursor::TCursor(Context *context) : Cursor(context)
{
    cursor = new Cursor(TheContext);

    int size = 100;

    SharedPtr<TImage> image(new TImage());
    image->SetSize(size, size);

    image->Clear({0.0f, 0.0f, 1.0f, 1.0f});

    cursor->DefineShape("Normal", image, {0, 0, size, size}, {0, 0});
    cursor->SetName("Cursor");
    TheUI->SetCursor(cursor);
    cursor->SetPosition(TheGraphics->GetWidth() / 2, TheGraphics->GetHeight() / 2);

    shapes = new CursorShapes();

    nodeSprite = TheScene->CreateChild("Cursor sprite");
    staticSprite = nodeSprite->CreateComponent<StaticSprite2D>();
    staticSprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f), 1.0f));
    staticSprite->SetBlendMode(BLEND_ALPHA);
    nodeSprite->SetEnabled(true);

    SubscribeToEvent(E_HOVER_BEGIN_ELEMENT_GUI, URHO3D_HANDLER(TCursor, HandleHoverBeginElementGUI));
    SubscribeToEvent(E_HOVER_END_ELEMENT_GUI, URHO3D_HANDLER(TCursor, HandleHoverEndElementGUI));
}



void TCursor::RegisterObject(Context *context)
{
    pchar UI_CATEGORY = "UI";

    context->RegisterFactory<TCursor>(UI_CATEGORY);
}


void TCursor::Show()
{
    hidden = false;
}


void TCursor::Hide()
{
    hidden = true;
}


SharedPtr<Cursor> TCursor::GetCursor()
{
    return cursor;
}

void TCursor::Update(float dT)
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
        SharedPtr<TImage> image(new TImage());
        image->SetSize(1, 1);
        cursor->DefineShape("Normal", image, {0, 0, image->GetWidth(), image->GetHeight()}, {0, 0});
    }
    else
    {
        static const int delta = 2;
        int posX = cursor->GetPosition().x_;
        int posY = cursor->GetPosition().y_;
        int width = TheGraphics->GetWidth();
        int height = TheGraphics->GetHeight();
        int numFrame = static_cast<int>(angle0) / 10;

        if(!TheMenu->IsActive() && !TheGUI->UnderCursor())
        {
            if(posX < delta && posY < delta)
            {
                type = Type::TopLeft;
            }
            else if(posX > width - delta && posY < delta)
            {
                type = Type::TopRight;
            }
            else if(posX > width - delta && posY > height - delta)
            {
                type = Type::DownRight;
            }
            else if(posX < delta && posY > height - delta)
            {
                type = Type::DownLeft;
            }
            else if(posX < delta)
            {
                type = Type::Left;
            }
            else if(posX > width - delta)
            {
                type = Type::Right;
            }
            else if(posY < delta)
            {
                type = Type::Up;
            }
            else if(posY > height - delta && !TheGUI->GheckOnDeadZoneForCursorBottomScreen(posX))
            {
                type = Type::Down;
            }
            else if (TheInput->GetMouseButtonDown(MOUSEB_RIGHT | MOUSEB_MIDDLE))
            {
                static float thisNumFrame = 0.0f;
                int dX = TheInput->GetMouseMoveX();
                int dY = TheInput->GetMouseMoveY();
                thisNumFrame += static_cast<float>(sqrt(dY * dY + dX * dX)) / 10.0f;
                if(thisNumFrame < 0.0f)
                {
                    thisNumFrame = 36.0f;
                }
                else if(thisNumFrame > 36.0f)
                {
                    thisNumFrame = 0.0f;
                }
                numFrame = static_cast<int>(thisNumFrame);
                type = Type::Busy;
            }
            else
            {
                type = selected ? Type::Selected : Type::Normal;
            }
        }
        else
        {
            type = selected ? Type::Selected : Type::Normal;
        }
        static Type::E prevType = Type::Count;
        static int prevFrame = -1;

        if (prevType != type || prevFrame != numFrame)
        {
            prevFrame = numFrame;
            prevType = type;

            SharedPtr<TImage> image = shapes->GetShape(type, numFrame);

            cursor->DefineShape("Normal", image, {0, 0, image->GetWidth(), image->GetHeight()}, image->GetHotSpot());
            /*
            SharedPtr<Texture2D> texture(new Texture2D(TheContext));
            texture->SetSize(image->GetWidth(), image->GetHeight(), D3DFMT_X8R8G8B8);
            texture->SetData(image->GetUImage());
            SharedPtr<Sprite2D> sprite(new Sprite2D(TheContext));
            sprite->SetTexture(texture);
            staticSprite->SetSprite(sprite);
            nodeSprite->SetPosition({100.0f, 100.0f, -100.0f});
            */
        }
    }

    if (overElementGUI)
    {
        SetSelected();
    }
    else
    {
        SetSelectedOverUnit();
    }
}


void TCursor::SetSelectedOverUnit()
{
    Vector3 hitPosition;

    Drawable *drawable = GetRaycastNode(&hitPosition);

    if (drawable)
    {
        if (drawable->GetNode()->GetVar(VAR_NODE_IS_UNIT).GetBool())
        {
            SetSelected();
        }
        else
        {
            SetNormal();
        }
    }
    else
    {
        SetNormal();
    }
}


void TCursor::HandleHoverBeginElementGUI(StringHash, VariantMap &)
{
    overElementGUI = true;
}


void TCursor::HandleHoverEndElementGUI(StringHash, VariantMap &)
{
    overElementGUI = false;
}


void TCursor::SetNormal()
{
    selected = false;
}


void TCursor::SetSelected()
{
    selected = true;
}


Drawable* TCursor::GetRaycastNode(Vector3 *hitPos_)
{
    if(TheUI->GetElementAt(TheUI->GetCursorPosition(), true))
    {
        return nullptr;
    }

    Ray ray = TheCamera->GetCursorRay();
    PODVector<RayQueryResult> results;
    RayOctreeQuery query(results, ray, RAY_TRIANGLE, M_INFINITY, DRAWABLE_GEOMETRY, VIEW_MASK_FOR_MISSILE);
    TheScene->GetComponent<Octree>()->Raycast(query);

    if(results.Size())
    {
        RayQueryResult& result = results[0];
        String name = result.drawable_->GetNode()->GetName();
        if (result.drawable_->GetNode()->GetName() == NAME_NODE_TILE_PATH && results.Size() > 1)
        {
            result = results[1];
        }

        if(hitPos_)
        {
            *hitPos_ = result.position_;
        }
        return result.drawable_;
    }

    return nullptr;
}


CursorShapes::CursorShapes() : Object(TheContext)
{
    /*
    for (int iType = 0; iType < Type::Size; iType++)
    {
    SharedPtr<Image> shape = GetShape((TypeCursor)iType, 0);
    }
    */
}


SharedPtr<TImage> CursorShapes::GetShape(TCursor::Type::E type, int numFrame)
{
    typedef void(CursorShapes::*pToFunc)(int);
    const pToFunc funcs[TCursor::Type::Count] =
    {
        &CursorShapes::CreateNormal,
        &CursorShapes::CreateSelected,
        &CursorShapes::CreateLeft,
        &CursorShapes::CreateUp,
        &CursorShapes::CreateRight,
        &CursorShapes::CreateDown,
        &CursorShapes::CreateTopLeft,
        &CursorShapes::CreateTopRight,
        &CursorShapes::CreateDownLeft,
        &CursorShapes::CreateDownRight,
        &CursorShapes::CreateBusy
    };

    StructShape key = {type, numFrame};

    if (!map.Contains(key))
    {
        pToFunc func = funcs[type];
        (this->*func)(numFrame);
    }

    return map[key];
}


void CursorShapes::CalcXYforNormal(int numFrame, int *x1, int *y1, int *x2, int *y2)
{
    float size = 100.0f;

    float angle0 = numFrame - 45.0f;
    float angle1 = angle0 + 180.0f;

    float radius = size / 6.0f;

    *x1 = static_cast<int>(size / 2.0f + Cos(angle0) * radius);
    *y1 = static_cast<int>(size / 2.0f + Sin(angle0) * radius);

    *x2 = static_cast<int>(size / 2.0f + Cos(angle1) * radius);
    *y2 = static_cast<int>(size / 2.0f + Sin(angle1) * radius);
}


#define DRAW_LINE(color, num, val0, val1, val2, val3, val4, val5, val6, val7)   \
    int buffer[] = {val0, val1, val2, val3, val4, val5, val6, val7};            \
    image->DrawPolyline(color, num, buffer);


void CursorShapes::CreateNormal(int numFrame)
{
    numFrame *= 10;

    int size = 100;

    SharedPtr<TImage> image(new TImage());
    image->SetSize(size, size);
    image->Clear(transparent);

    int x1, y1, x2, y2;

    CalcXYforNormal(numFrame, &x1, &y1, &x2, &y2);

    FillGradient(image, TCursor::Type::Normal, numFrame);

    DRAW_LINE(border, 4, 0, 0, x1, y1, x2, y2, 0, 0); //-V112

    StructShape key = {TCursor::Type::Normal, numFrame / 10};

    map[key] = image;
}


void CursorShapes::CreateSelected(int numFrame)
{
    numFrame *= 10;

    int size = 100;

    SharedPtr<TImage> image(new TImage());
    image->SetSize(size, size);
    image->Clear(transparent);

    int x1, y1, x2, y2;

    CalcXYforNormal(numFrame, &x1, &y1, &x2, &y2);

    FillGradient(image, TCursor::Type::Selected, numFrame);

    DRAW_LINE(border, 4, 0, 0, x1, y1, x2, y2, 0, 0); //-V112

    FillGradient(image, TCursor::Type::Selected, numFrame + 360);   // Draw circle

    StructShape key = { TCursor::Type::Selected, numFrame / 10 };

    map[key] = image;
}


void CursorShapes::CreateLeft(int numFrame)
{
    SharedPtr<TImage> image(new TImage());
    image->SetSize(dimensionTriangleBig, dimensionTriangleBig);

    int width = dimensionTriangleSmall;
    int height = dimensionTriangleBig;

    FillGradient(image, TCursor::Type::Left, numFrame);

    DRAW_LINE(border, 4, 0, height / 2, width, 0, width, height, 0, height / 2); //-V112

    image->FillRegion(1, 1, transparent, border);
    image->FillRegion(1, height - 1, transparent, border);
    image->FillRegion(height - 1, 1, transparent, border);
    image->SetHotSpot(0, height / 2);
    StructShape key = {TCursor::Type::Left, numFrame};
    map[key] = image;
}


void CursorShapes::CreateRight(int numFrame)
{
    SharedPtr<TImage> image(new TImage());
    image->SetSize(dimensionTriangleBig, dimensionTriangleBig);

    int width = dimensionTriangleSmall;
    int height = dimensionTriangleBig;

    FillGradient(image, TCursor::Type::Right, numFrame);

    DRAW_LINE(border, 4, 0, 0, width, height / 2, 0, height, 0, 0); //-V112

    image->FillRegion(1, 1, transparent, border);
    image->FillRegion(width - 1, 1, transparent, border);
    image->FillRegion(width - 1, height - 1, transparent, border);
    image->SetHotSpot(width, height / 2);
    StructShape key = { TCursor::Type::Right, numFrame};
    map[key] = image;
}


void CursorShapes::CreateUp(int numFrame)
{
    SharedPtr<TImage> image(new TImage());
    image->SetSize(dimensionTriangleBig, dimensionTriangleBig);

    int width = dimensionTriangleBig;
    int height = dimensionTriangleSmall;

    FillGradient(image, TCursor::Type::Up, numFrame);

    DRAW_LINE(border, 4, width / 2, 0, width, height, 0, height, width / 2, 0); //-V112

    image->FillRegion(1, 1, transparent, border);
    image->FillRegion(width - 1, 1, transparent, border);
    image->FillRegion(1, height + 3, transparent, border);
    image->SetHotSpot(width / 2, 0);
    StructShape key = { TCursor::Type::Up, numFrame};
    map[key] = image;
}


void CursorShapes::CreateDown(int numFrame)
{
    SharedPtr<TImage> image(new TImage());
    image->SetSize(dimensionTriangleBig, dimensionTriangleBig);

    int width = dimensionTriangleBig;
    int height = dimensionTriangleSmall;

    FillGradient(image, TCursor::Type::Down, numFrame);

    DRAW_LINE(border, 4, 0, 0, width, 0, width / 2, height, 0, 0); //-V112

    image->FillRegion(width / 2, height + 1, transparent, border);
    image->SetHotSpot(width / 2, height);
    StructShape key = { TCursor::Type::Down, numFrame };
    map[key] = image;
}


void CursorShapes::CreateTopLeft(int numFrame)
{
    SharedPtr<TImage> image(new TImage());
    image->SetSize(dimensionTriangleBig, dimensionTriangleBig);

    int size = static_cast<int>(dimensionTriangleSmall * 1.41f);

    FillGradient(image, TCursor::Type::TopLeft, numFrame);

    DRAW_LINE(border, 4, 0, 0, size, 0, 0, size, 0, 0); //-V112

    image->FillRegion(size, size, transparent, border);
    image->SetHotSpot(0, 0);
    StructShape key = { TCursor::Type::TopLeft, numFrame};
    map[key] = image;
}


void CursorShapes::CreateTopRight(int numFrame)
{
    int size = static_cast<int>(dimensionTriangleSmall * 1.41f);
    SharedPtr<TImage> image(new TImage());
    image->SetSize(size + 1, size + 1);

    FillGradient(image, TCursor::Type::TopRight, numFrame);

    DRAW_LINE(border, 4, 0, 0, size, 0, size, size, 0, 0); //-V112

    image->FillRegion(0, size, transparent, border);
    image->SetHotSpot(size, 0);
    StructShape key = { TCursor::Type::TopRight, numFrame};
    map[key] = image;
}


void CursorShapes::CreateDownLeft(int numFrame)
{
    int size = static_cast<int>(dimensionTriangleSmall * 1.41f);
    SharedPtr<TImage> image(new TImage());
    image->SetSize(size + 1, size + 1);

    FillGradient(image, TCursor::Type::DownLeft, numFrame);

    DRAW_LINE(border, 4, 0, 0, size, size, 0, size, 0, 0); //-V112

    image->FillRegion(size, 0, transparent, border);
    image->SetHotSpot(0, size);
    StructShape key = { TCursor::Type::DownLeft, numFrame};
    map[key] = image;
}


void CursorShapes::CreateDownRight(int numFrame)
{
    int size = static_cast<int>(dimensionTriangleSmall * 1.41f);

    SharedPtr<TImage> image(new TImage());
    image->SetSize(size + 1, size + 1);

    FillGradient(image, TCursor::Type::DownRight, numFrame);

    DRAW_LINE(border, 4, size, 0, size, size, 0, size, size, 0); //-V112

    image->FillRegion(0, 0, transparent, border);
    image->SetHotSpot(size, size);
    StructShape key = { TCursor::Type::DownRight, numFrame};
    map[key] = image;
}


void CursorShapes::CreateBusy(int numFrame)
{
    int size = 72;
    SharedPtr<TImage> image(new TImage());
    image->SetSize(size, size);

    FillGradient(image, TCursor::Type::Busy, numFrame);

    image->DrawCircle(size / 2.0f, size / 2.0f, size / 2.1f, border);
    image->FillRegion(0, 0, transparent, border);
    image->FillRegion(size - 1, 0, transparent, border);
    image->FillRegion(0, size - 1, transparent, border);
    image->FillRegion(size - 1, size - 1, transparent, border);
    image->SetHotSpot(image->GetWidth() / 2, image->GetHeight() / 2);
    StructShape key = { TCursor::Type::Busy, numFrame};
    map[key] = image;
}


#define CORRECTION_COLOR            \
    colorComponent += dColor;       \
    if(colorComponent > 1.0f)       \
    {                               \
        dColor = -dColor;           \
        colorComponent = 1.0f;      \
    }                               \
    else if(colorComponent < 0.0f)  \
    {                               \
        dColor = -dColor;           \
            colorComponent = 0.0f;  \
    }


#define CALCULATE_COLORS(T)                                 \
    if(type == T)                                           \
    {                                                       \
        numFrame = 36 - numFrame;                           \
    }                                                       \
    float dColor = 1.0f / 18.0f;                            \
    float colorComponent = numFrame * dColor;               \
    if(numFrame > 18)                                       \
    {                                                       \
        colorComponent = 1.0f - (numFrame - 18) * dColor;   \
        dColor = -dColor;                                   \
    }                   


#undef DRAW_LINE
#define DRAW_LINE(img, x0_, y0_, x1_, y1_)                                                               \
    img->DrawLine(x0_, y0_, x1_, y1_, {colorComponent, colorComponent, colorComponent, 1.0f});    \
    CORRECTION_COLOR


void CursorShapes::FillGradient(TImage *image, TCursor::Type::E type, int numFrame)
{
    int width = image->GetWidth();
    int height = image->GetHeight();

    if (type == TCursor::Type::Left || type == TCursor::Type::Right)
    {
        CALCULATE_COLORS(TCursor::Type::Left)

            for (int i = 0; i < width; i++)
            {
                DRAW_LINE(image, i, 0, i, height);
            }
    }
    else if (type == TCursor::Type::Up || type == TCursor::Type::Down)
    {
        CALCULATE_COLORS(TCursor::Type::Up)

            for (int i = 0; i < height; i++)
            {
                DRAW_LINE(image, 0, i, width, i);
            }
    }
    else if (type == TCursor::Type::TopLeft || type == TCursor::Type::DownRight)
    {
        CALCULATE_COLORS(TCursor::Type::TopLeft)

            for (int x = 1; x < width; x++)
            {
                DRAW_LINE(image, x, 0, 0, x);
            }
        for (int x = 0; x < width; x++)
        {
            DRAW_LINE(image, x, height, width, x);
        }
    }
    else if (type == TCursor::Type::TopRight || type == TCursor::Type::DownLeft)
    {
        CALCULATE_COLORS(TCursor::Type::DownLeft);

        for (int y = height; y > 0; y--)
        {
            DRAW_LINE(image, 0, y, height - y, height);
        }
        for (int x = 0; x < width; x++)
        {
            DRAW_LINE(image, x, 0, width, height - x);
        }
    }
    else if (type == TCursor::Type::Busy)
    {
        float k = 2.0f;
        float dColor = 1.0f / 36.0f / k;
        float colorComponent = numFrame * dColor * 2 * k;
        if (numFrame > 18)
        {
            colorComponent = 1.0f - (numFrame - 18) * dColor * 2 * k;
            dColor = -dColor;
        }

        for (int x = 0; x < width; x++)
        {
            DRAW_LINE(image, x, 0, width - x, height);
        }
        for (int y = 0; y < height; y++)
        {
            DRAW_LINE(image, width, y, 0, height - y);
        }
    }
    else if (type == TCursor::Type::Normal || type == TCursor::Type::Selected)
    {
        if (type == TCursor::Type::Selected && numFrame >= 360) // if numFrame > 360 - draw circle
        {
            numFrame -= 360;
            SharedPtr<TImage> imageCircle(new TImage());
            imageCircle->SetSize(width, height);

            float k = 2.0f;
            float dColor = 1.0f / 360.0f / k;
            float colorComponent = numFrame * dColor * 2 * k;
            if (numFrame > 180)
            {
                colorComponent = 1.0f - (numFrame - 180) * dColor * 2 * k;
                dColor = -dColor;
            }

            for (int x = 0; x < width; x++)
            {
                DRAW_LINE(imageCircle, x, 0, width - x, height);
            }
            for (int y = 0; y < height; y++)
            {
                DRAW_LINE(imageCircle, width, y, 0, height - y);
            }

            imageCircle->DrawCircle(width / 2.0f, height / 2.0f, 17.0f, border);
            imageCircle->FillRegion(1, 1, transparent, border);
            image->CopyImage(0, 0, *imageCircle);
        }
        else
        {
            int x1, y1, x2, y2;

            CalcXYforNormal(numFrame, &x1, &y1, &x2, &y2);

            float dX = static_cast<float>(fabs(static_cast<double>(x2 - x1)));
            float dY = static_cast<float>(fabs(static_cast<double>(y2 - y1)));

            float numSteps = (dY > dX) ? dY : dX;
            numSteps *= 200.0f;

            float dColor = 1.0f / numSteps;
            float colorComponent = 0.0f;

            float stepX = (x2 - x1) / numSteps;
            float stepY = (y2 - y1) / numSteps;

            int step = 0;

            for (float x = static_cast<float>(x1), y = static_cast<float>(y1); step < numSteps; step++, x += stepX, y += stepY)
            {
                image->DrawLine(0, 0, static_cast<int>(x), static_cast<int>(y), {colorComponent, colorComponent, colorComponent, 1.0f});
                colorComponent += dColor;
            }
        }
    }
}
