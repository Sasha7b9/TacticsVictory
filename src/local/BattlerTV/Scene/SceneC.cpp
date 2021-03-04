// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Audio/Sounds.h"
#include "Game/Particles.h"
#include "GUI/Cursor.h"
#include "GUI/GuiGame/WindowTarget.h"
#include "Scene/SceneC.h"
#include "Scene/Objects/ObjectC.h"


SceneC::SceneC(Context *context) : SceneT(context)
{

}


SceneC::~SceneC()
{

}


void SceneC::Create()
{
    SceneT::Create();

    Particles::Init();

    Sounds::Init();

    TheRenderer->SetShadowMapSize(2048);

    TheWindowTarget = new WindowTarget();
    TheUIRoot->AddChild(TheWindowTarget);
    TheWindowTarget->SetVisible(false);
}


void SceneT::Decompress(MemoryBuffer &buffer)
{
    uint start = TheTime->GetSystemTime();

    while (!buffer.IsEof())
    {
        uint id = buffer.ReadUInt();
        Vector3 position = buffer.ReadVector3();

        ObjectT *object = ObjectSpecificC::remoteStorage[id];

        object->GetNode()->SetPosition(position);
    }

    LOGINFOF("time receive scene %d ms", TheTime->GetSystemTime() - start);
}
