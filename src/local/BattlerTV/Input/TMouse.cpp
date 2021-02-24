// 2021/02/24 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/TCursor.h"
#include "Input/TMouse.h"
#include "Scene/TCScene.h"


Mouse::Mouse() : Object(TheContext)
{
    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(Mouse, HandleMouseDown));
}


void Mouse::HandleMouseDown(StringHash, VariantMap &eventData)
{
    int buttons = static_cast<int>(eventData[MouseButtonDown::P_BUTTONS].GetInt());

    if (buttons == MOUSEB_LEFT)
    {
        ProcessMouseLeft();
    }
    else if (buttons == MOUSEB_RIGHT)
    {
        ProcessMouseRight();
    }
}


void Mouse::ProcessMouseLeft()
{
    Vector3 hitCoord;
    Drawable *object = TheCursor->GetRaycastNode(&hitCoord);

    if (!object)
    {
        return;
    }

    Node *node = object->GetNode();
    String name = node->GetName();

    if (name == NAME_NODE_TANK)
    {
        Vector3 position = node->GetPosition();
        Coord coord(static_cast<uint>(-position.z_), static_cast<uint>(position.x_)); //-V2004

        ThePathIndicator->SetStartPosition(coord);
        ThePathIndicator->Disable();
    }
    else if (name == NAME_NODE_TERRAIN)
    {
        ThePathIndicator->Enable();
    }
}


void Mouse::ProcessMouseRight()
{
    ThePathIndicator->Disable();

    Drawable *object = TheCursor->GetRaycastNode();

    if (object && object->GetNode()->GetName() == NAME_NODE_TANK)
    {
    }
}