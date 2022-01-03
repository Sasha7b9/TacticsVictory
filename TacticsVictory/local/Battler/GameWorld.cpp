// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/GUI.h"
#include "GUI/Widgets/CursorGUI.h"
#include "Input/Mouse.h"
#include "Objects/GameObject_.h"
#include "Graphics/Meshes/WorldGizmo.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Graphics/Textures/PoolTextures.h"
#include "Objects/Units/Logic/Selector_.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/Water/Submarine_.h"
#include "TVBattler.h"
#include "Objects/World/Sun_.h"
#include "GameWorld.h"
#include "Objects/World/Landscape_.h"


using namespace Pi;


namespace Pi
{
    GameWorld *GameWorld::self = nullptr;
}


GameWorld::GameWorld(pchar name) : World(name)
{
    self = this;
}


GameWorld::~GameWorld()
{
    SAFE_DELETE(CursorGUI::self);
}


WorldResult::B GameWorld::Preprocess()
{
    WorldResult::B result = World::Preprocess();

    if(result != WorldResult::Okay)
    {
        return (result);
    }

    SetCamera(CameraRTS::self);
    CameraRTS::self->Invalidate();
    CameraRTS::self->Update();

    GetRootNode()->AppendNewSubnode(new WorldGizmo());

    return (WorldResult::Okay);
}


void GameWorld::CreateObjects()
{
    GetRootNode()->AppendNewSubnode(new Selector());
}


void GameWorld::ChangeCursorPosition(float deltaX, float deltaY)
{
    CursorGUI::self->position.x += deltaX * 3.0F;
    CursorGUI::self->position.y += deltaY * 3.0F;

    float displayWidth = (float)TheDisplayMgr->GetDisplayWidth();
    float displayHeight = (float)TheDisplayMgr->GetDisplayHeight();

    CursorGUI::self->position.x = FmaxZero(CursorGUI::self->position.x);
    CursorGUI::self->position.y = FmaxZero(CursorGUI::self->position.y);

    CursorGUI::self->position.x = Fmin(displayWidth - 1,  CursorGUI::self->position.x);
    CursorGUI::self->position.y = Fmin(displayHeight - 1, CursorGUI::self->position.y);

    Vector2D cursorSize = CursorGUI::self->GetWidgetSize();
    float posX = CursorGUI::self->position.x - 0.5F * cursorSize.x;
    float posY = CursorGUI::self->position.y - 0.5F * cursorSize.y;

    CursorGUI::self->SetWidgetPosition(Point3D((float)((int)posX), (float)((int)posY), 0.0F));
    CursorGUI::self->Invalidate();

    if(GUI::self)
    {
        Mouse::self->ChangePos((int)posX, (int)posY);
    }
}


Point3D GameWorld::TransformWorldCoordToDisplay(const Point3D &worldPosition)
{
    // Transform the world point into camera space
    Point3D displayPoint = CameraRTS::self->GetInverseWorldTransform() * worldPosition;

    // Project the point onto the focal plane
    const FrustumCameraObject *object = CameraRTS::self->GetObject();
    float focalLength = object->GetFocalLength();
    displayPoint.x *= focalLength / displayPoint.z;
    displayPoint.y *= focalLength / displayPoint.z;

    // Rescale to the width and height of the display
    float w = (float)(TheDisplayMgr->GetDisplayWidth() / 2);
    float h = (float)(TheDisplayMgr->GetDisplayHeight() / 2);
    displayPoint.x = w * displayPoint.x + w;
    displayPoint.y = h * displayPoint.y / object->GetAspectRatio() + h;
    displayPoint.z = 0.0f;

    return displayPoint;
}
