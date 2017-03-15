#include "stdafx.h"
#define BUILD_DLL
#include "AdditionalDependences.h"
#include <Urho3D/AngelScript/Addons.h>
#include <Urho3D/AngelScript/APITemplates.h>
#include <Urho3D/AngelScript/Script.h>
#include <Urho3D/AngelScript/ScriptFile.h>
#include <Urho3D/AngelScript/ScriptInstance.h>



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BUILD_DLL int GetFractal()
{
    asIScriptContext* con = asGetActiveContext();
    return 5;
}
