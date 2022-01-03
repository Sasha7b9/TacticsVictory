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

#include <Effects/PiParticles.h>
#include <Effects/PiMarkings.h>

#include <Geometry/PiMesh.h>
#include <Geometry/PiPrimitives.h>

#include <Graphics/PiRender.h>
#include <Graphics/PiGraphics.h>

#include <Interface/PiConfiguration.h>
#include <Interface/PiPaint.h>
#include <Interface/PiMutators.h>
#include <Interface/PiViewports.h>
#include <Interface/PiWidgets.h>
#include <Interface/PiToolWindows.h>

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
#include <System/PiProfiler.h>

#include <Utilities/PiLog.h>

#include <World/PiModels.h>
#include <World/PiSources.h>
#include <World/PiWorld.h>
#include <World/PiMarkers.h>

#ifdef WIN32
#pragma warning(pop)
#endif

#define SIZE_CHUNK_HEADER 4


#include "defines.h" 

