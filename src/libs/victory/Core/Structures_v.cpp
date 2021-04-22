// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Structures_v.h"


void Coord::RegisterInAS(Urho3D::Script *script)
{
    asIScriptEngine *engine = script->GetScriptEngine();
    engine->RegisterObjectType("Coord", sizeof(Coord), asOBJ_VALUE | asOBJ_POD);
}
