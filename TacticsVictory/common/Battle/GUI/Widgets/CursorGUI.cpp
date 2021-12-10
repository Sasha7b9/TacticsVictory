// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "CursorGUI.h"
#include "GUI/Panels/PanelBottom.h"
#include "GUI/Panels/PanelGUI.h"
#include "Button.h"
#include "DrawingWidget.h"
#include "Utils/Math.h"
#include "Scene/Cameras/CameraRTS.h"
#include "Scene/World/GameWorld.h"
#include "Scene/Objects/GameObject.h"


using namespace Pi;


const float CursorGUI::speedAnimation = 5.0f * 1e-2f;


namespace Pi
{
    CursorGUI *CursorGUI::self = nullptr;
}


CursorGUI::CursorGUI()
    : Widget(),
    Singleton<CursorGUI>(self)
{

    for(int st = 0; st < State::Count; st++)
    {
        for(int fr = 0; fr < numFrames; fr++)
        {
            skins[st][fr] = nullptr;
        }
    }

    mainWidget = new Widget();

    PrepareSkins();

    AppendNewSubnode(mainWidget);

    state = State::Normal;

    SetSkin(0);
}

CursorGUI::~CursorGUI()
{
    for(int st = 0; st < State::Count; st++)
    {
        for(int fr = 0; fr < numFrames; fr++)
        {
            delete skins[st][fr];
        }
    }
}

void CursorGUI::Move()
{
    Vector2D speed = CameraRTS::self->GetSpeed();

    if (speed == Vector2D::ZERO)
    {
        state = GameObject::GetFromScreen(position).GetGameObjectProperty().Selectable() ? State::OverObject : State::Normal;
    }
    else
    {
        if (speed.y == 0.0f)
        {
            state = speed.x < 0.0f ? State::OutScreenLeft : State::OutScreenRight;
        }
        else if (speed.x == 0.0f)
        {
            state = speed.y > 0.0f ? State::OutScreenDown : State::OutScreenUp;
        }
        else if (speed.y < 0.0f)
        {
            state = speed.x < 0.0f ? State::OutScreenLeftUp : State::OutScreenRightUp;
        }
        else if (speed.y > 0.0f)
        {
            state = speed.x < 0.0f ? State::OutScreenLeftDown : State::OutScreenRightDown;
        }
    }

    float dT = TheTimeMgr->GetFloatDeltaTime();
    currentFrame += dT * speedAnimation;

    while(currentFrame > (numFrames - 1))
    {
        currentFrame -= numFrames;
    }

    int frame = (int)currentFrame;
 
   SetSkin(frame);
}


void CursorGUI::PrepareSkins()
{
    for(int i = 0; i < numFrames; i++)
    {
        skins[State::Normal][i] = CreateNormalOverSkin(i, State::Normal);
        skins[State::OverObject][i] = CreateNormalOverSkin(i, State::OverObject);
    }

    for(int s = State::OutScreenLeft; s < State::Count; s++)
    {
        for(int i = 0; i < numFrames; i++)
        {
            skins[s][i] = CreateOutScreenSkin((State::E)s, i);
        }
    }
}


DrawingWidget* CursorGUI::CreateNormalOverSkin(int numFrame, State::E eState)
{
    float size = 40;

    float component = 0.0f;

    Point2D points[3] = {
        {0.0F, 0.0F},
        {(float)(size - 1), (float)(size / 2)},
        {(float)(size / 2), (float)(size - 1)}
    };

    DrawingWidget *skin = new DrawingWidget(Vector2D(size, size));
    ColorRGBA color(component, component, component);
    skin->ClearAndFillRegion(points, 3, color, Mathem::OneComplement(color), Point2D(5, 5));
    skin->EndScene();

    float radiusMax = size / (eState == State::Normal ? 3.0f : 2.0f);
    float radiusMin = size / 10.0f;
    float centerX = size / 2.0f;
    float centerY = size / 2.0f;
    int shiftCircle = (int)(size / 3.5f);
    DrawingWidget *circle = new DrawingWidget(Vector2D(size, size));
    circle->SetColorBackground(ColorRGBA(0.0, 0.0, 0.0, 0.0f));
    circle->Clear();
    circle->SetColorBrush(eState == State::Normal ? K::black : ColorRGBA(0.25f, 0.25f, 0.25f));
    circle->FillCircle(centerX, centerY, radiusMax);
    circle->SetColorBrush(K::white);
    circle->DrawCircle(centerX, centerY, radiusMax);
    circle->DrawCircle(centerX, centerY, radiusMin);

    int numLines = 6;
    float stepAngle = K::two_pi / static_cast<float>(numLines);
    float frameAngle = K::two_pi / numFrames * static_cast<float>(numFrame) / static_cast<float>(numLines);

    for(int i = 0; i < numLines; i++)
    {
        float angle = frameAngle + static_cast<float>(i) * stepAngle;
        float lenMin = radiusMin * 1.5f;
        float lenMax = radiusMax * 0.8f;
        float xStart = centerX + Cos(angle) * lenMin + 0.5f;
        float yStart = centerY + Sin(angle) * lenMin + 0.5f;
        float xEnd = centerX + Cos(angle) * lenMax + 0.5f;
        float yEnd = centerY + Sin(angle) * lenMax + 0.5f;
        circle->DrawLine(xStart, yStart, xEnd, yEnd);
    }

    circle->EndScene();

    skin->AppendNewSubnode(circle);

    Transform4D transform = circle->GetWidgetTransform();
    transform.SetTranslation((float)shiftCircle, (float)shiftCircle, 0.0f);
    circle->SetWidgetTransform(transform);

    return skin;
}

DrawingWidget* CursorGUI::CreateOutScreenSkin(State::E _state, int /*numFrame*/)
{
    float width = 100.0f;
    float height = 51.0f;

    float component = 1.0f;
    float delta = 5.0f;

    DrawingWidget *skin = new DrawingWidget(Vector2D(width, height));
    skin->SetColorBackground( {0.0f, 0.0f, 0.0f, 0.0f} );
    skin->Clear();
    ColorRGBA color(component, component, component);
    skin->SetColorBrush(color);

    Point2D topLef{5, 5};
    Point2D topRight{50, 5};
    Point2D downRight{50, 50};
    Point2D downLeft{5, 50};

    Point2D left{5, 25};
    Point2D right{50, 25};
    Point2D top{25, 5};
    Point2D down{25, 50};

    if(_state == State::OutScreenLeft)
    {
        skin->DrawLine(left, right);
        skin->DrawLine(left, top);
        skin->DrawLine(left, down);
    }
    else if(_state == State::OutScreenLeftUp)
    {
        skin->DrawLine(topLef, left);
        skin->DrawLine(topLef, downRight);
        skin->DrawLine(topLef, top);
    }
    else if(_state == State::OutScreenUp)
    {
        skin->DrawLine(top, down);
        skin->DrawLine(top, left);
        skin->DrawLine(top, right);
    }
    else if(_state == State::OutScreenDown)
    {
        skin->DrawLine(top, down);
        skin->DrawLine(left, down);
        skin->DrawLine(right, down);
        skin->SetWidgetPosition({0.0f, -height - delta, 0.0f});
    }
    else if(_state == State::OutScreenRightUp)
    {
        skin->DrawLine(downLeft, topRight);
        skin->DrawLine(top, topRight);
        skin->DrawLine(topRight, right);
        skin->SetWidgetPosition({-height - delta, 0.0f, 0.0f});
    }
    else if(_state == State::OutScreenRight)
    {
        skin->DrawLine(left, right);
        skin->DrawLine(top, right);
        skin->DrawLine(down, right);
        skin->SetWidgetPosition({-55.0f, 0.0f, 0.0f});
    }
    else if (_state == State::OutScreenRightDown)
    {
        skin->DrawLine(topLef, downRight);
        skin->DrawLine(topRight, downRight);
        skin->DrawLine(downLeft, downRight);
        skin->SetWidgetPosition({-55.0f, -height - delta, 0.0f});
    }
    else if (_state == State::OutScreenLeftDown)
    {
        skin->DrawLine(topLef, downLeft);
        skin->DrawLine(topRight, downLeft);
        skin->DrawLine(downRight, downLeft);
        skin->SetWidgetPosition({0.0f, -height - delta, 0.0f});
    }
    else
    { 
        skin->DrawCircle(20, 20, 10);
    }

    skin->EndScene();

    return skin;
}

void CursorGUI::Update()
{

}

void CursorGUI::SetSkin(int numSkin)
{
    mainWidget->RemoveSubtree();
    mainWidget->AppendSubnode(skins[state][numSkin]);
}

CursorGUIMutator::CursorGUIMutator() : Mutator(kMutatorCursorGUI)
{

}

CursorGUIMutator::~CursorGUIMutator()
{
//    float dT = TheTimeMgr->GetFloatDeltaTime();
//    static_cast<CursorGUI*>(GetTargetWidget())->currentFrame += dT * 
}

void CursorGUIMutator::Move()
{

}

void CursorGUIMutator::Reset()
{

}
