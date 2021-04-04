// 2021/04/04 11:28:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


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
}
