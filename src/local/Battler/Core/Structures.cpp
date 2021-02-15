// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "Structures.h"



void Coord::RegisterInAS()
{
    asIScriptEngine *engine = gScript->GetScriptEngine();
    engine->RegisterObjectType("Coord", sizeof(Coord), asOBJ_VALUE | asOBJ_POD);
}
