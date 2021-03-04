// 2021/02/24 15:45:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Cursor.h"
#include "Input/Mouse.h"
#include "Scene/SceneC.h"
#include "Scene/Objects/Units/UnitsEvents_.h"


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

    if (node->GetVar(VAR_NODE_IS_UNIT).GetBool())
    {
        VariantMap &eventData = GetEventDataMap();
        eventData[UnitMouseClick::P_NODE] = node;
        eventData[UnitMouseClick::P_CTRL_PRESSED] = TheInput->GetKeyDown(KEY_CTRL);
        node->SendEvent(EU_MOUSE_CLICK, eventData);
    }
    else if (name == NAME_NODE_TERRAIN)
    {
        ThePathIndicator->Enable();
    }

//    if (name == NAME_NODE_TANK)
//    {
//        Vector3 position = node->GetPosition();
//        Coord coord(static_cast<uint>(-position.z_), static_cast<uint>(position.x_)); //-V2004
//
//        ThePathIndicator->SetStartPosition(coord);
//        ThePathIndicator->Disable();
//    }

}


void Mouse::ProcessMouseRight()
{
    ThePathIndicator->Disable();

//    Drawable *object = TheCursor->GetRaycastNode();
//
//    if (object && object->GetNode()->GetName() == NAME_NODE_TANK)
//    {
//    }
}
