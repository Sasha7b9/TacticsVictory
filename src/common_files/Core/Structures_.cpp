// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Core/Structures_.h"


void Coord::RegisterInAS()
{
    asIScriptEngine *engine = TheScript->GetScriptEngine();
    engine->RegisterObjectType("Coord", sizeof(Coord), asOBJ_VALUE | asOBJ_POD);
}
