// 2021/02/24 9:06:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

namespace Urho3D
{
    URHO3D_EVENT(E_HOVERBEGINELEMENTGUI, HoverBeginElementGUI)
    {
        URHO3D_PARAM(P_ELEMENT, Element);
    }


    URHO3D_EVENT(E_HOVERENDELEMENTGUI, HoverEndElementGUI)
    {
        URHO3D_PARAM(P_ELEMENT, Element);
    }
}
