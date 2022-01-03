// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Widgets/ObjectViewportWidget.h"
#include "Objects/World/Sun_.h"


using namespace Pi;

static Sun *sunViewport = nullptr;


ObjectViewportWidget::ObjectViewportWidget(const Vector2D& size, float focalLength) : DrawingWidget(size)
{
    SetColorBrush(ColorRGBA(0.5f, 0.5f, 0.5f));
    DrawRectangle(0.0f, 0.0f, size.x - 1, size.y - 1);
    EndScene();

    viewport = new WorldViewportWidget(size - Vector2D(2.0f, 2.0f), focalLength);
    viewport->LoadWorld("world/test");
    viewport->EnableCameraOrbit(Point3D::ZERO, 1.0f);
    viewport->SetCameraAngles(0.0f, 0.5f);
    viewport->GetViewportWorld()->GetRootNode()->AppendNewSubnode(sunViewport);
    viewport->SetWidgetPosition({1.0f, 1.0f, 0.0f});
    AppendNewSubnode(viewport);
}