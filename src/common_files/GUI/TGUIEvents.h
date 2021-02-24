// 2021/02/24 9:06:04 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

namespace Urho3D
{
    // evetn means that cursor is over the element GUI and cursor must be selected
    URHO3D_EVENT(E_HOVER_BEGIN_ELEMENT_GUI, HoverBeginElementGUI)
    {

    }

    // event means that cursor is not over the element and should be set to normal state
    URHO3D_EVENT(E_HOVER_END_ELEMENT_GUI, HoverEndElementGUI)
    {

    }
}
