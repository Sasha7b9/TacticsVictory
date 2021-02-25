// 2021/02/24 21:10:26 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


URHO3D_EVENT(EU_MOUSE_CLICK, UnitMouseClick)
{
    URHO3D_PARAM(P_NODE, Node);
    URHO3D_PARAM(P_CTRL_PRESSED, bool);
}

