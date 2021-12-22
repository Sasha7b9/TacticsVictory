// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

#ifdef WIN32
#pragma warning(push, 0)
#endif

#include <cstdarg>
#include <filesystem>
#include <functional>
#include <climits>

#include <Base/PiMemory.h>

#include <Controllers/PiController.h>

#include <Math/PiVector3D.h>

#include <Network/PiMessages.h>

#include <Physics/PiCharacter.h>
#include <Physics/PiContacts.h>
#include <Physics/PiPhysics.h>
#include <Physics/PiSimulation.h>
#include <Physics/PiWater.h>

#include <Resource/PiPacking.h>

#include <System/PiAudioCapture.h>
#include <System/PiInput.h>
#include <System/PiApplication.h>
#include <System/PiTypes.h>
#include <System/PiSound.h>
#include <System/PiMain.h>
#include <System/PiEngine.h>

#include <World/PiModels.h>
#include <World/PiSources.h>
#include <World/PiWorld.h>
#include <World/PiMarkers.h>


#ifdef WIN32
#pragma warning(pop)
#endif

#define SIZE_CHUNK_HEADER 4


#include "defines.h"
#include "Utils/Log_.h"
