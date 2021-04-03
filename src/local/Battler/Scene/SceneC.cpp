// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Audio/Sounds.h"
#include "Game/Particles.h"
#include "Game/Logic/SunEngine_.h"
#include "GUI/GuiGame/WindowTarget.h"
#include "Scene/SceneC.h"
#include "Scene/Objects/ObjectC.h"


SceneC::SceneC(SceneC **self) : SceneT()
{
    *self = this;
}


SceneC::~SceneC()
{

}


void SceneC::Create()
{
    SceneT::Create();

    Particles::Init();

    Sounds::Init();

    TheRenderer->SetShadowMapSize(16384);

    TheWindowTarget = new WindowTarget();
    TheUIRoot->AddChild(TheWindowTarget);
    TheWindowTarget->SetVisible(false);
}


void SceneT::Decompress(MemoryBuffer &buffer)
{
    while (!buffer.IsEof())
    {
        uint id = buffer.ReadUInt();

        ObjectSpecificC::GetFromID(id)->Decompress(buffer);
    }
}
