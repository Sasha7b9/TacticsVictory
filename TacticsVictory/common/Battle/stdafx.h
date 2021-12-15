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
#include <Graphics/PiRender.h>
#include <System/PiAudioCapture.h>
#include <Physics/PiCharacter.h>
#include <System/PiInput.h>
#include <Graphics/PiGraphics.h>
#include <System/PiApplication.h>
#include <Geometry/PiMesh.h>
#include <Interface/PiConfiguration.h>
#include <Geometry/PiPrimitives.h>
#include <Controllers/PiController.h>
#include <Effects/PiParticles.h>
#include <Effects/PiMarkings.h>
#include <World/PiModels.h>
#include <World/PiSources.h>
#include <Interface/PiPaint.h>
#include <Physics/PiContacts.h>
#include <Physics/PiPhysics.h>
#include <World/PiWorld.h>
#include <Resource/PiPacking.h>
#include <System/PiTypes.h>
#include <System/PiSound.h>
#include <Interface/PiMutators.h>
#include <Interface/PiViewports.h>
#include <Physics/PiSimulation.h>
#include <Interface/PiWidgets.h>
#include <World/PiMarkers.h>
#include <System/PiMain.h>
#include <Math/PiVector3D.h>
#include <Interface/PiToolWindows.h>


#ifdef WIN32
#pragma warning(pop)
#endif

#define SIZE_CHUNK_HEADER 4


#include "defines.h" 
