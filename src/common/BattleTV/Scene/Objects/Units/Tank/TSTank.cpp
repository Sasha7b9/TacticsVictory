// 2021/02/17 15:56:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"


void STank::RegisterObject(Context *context)
{
    context->RegisterFactory<STank>();
}


SharedPtr<STank> STank::Create(Tank::TypeTank type, uint _id_)
{
    SharedPtr<Node> node(TheScene->scene->CreateChild(NODE_TANK, LOCAL));
    SharedPtr<STank> tank(node->CreateComponent<STank>(LOCAL));

    tank->Init(type, _id_);
    allTanks.Push(tank);
    return tank;
}


void STank::RegisterInAS()
{
    asIScriptEngine *engine = TheScript->GetScriptEngine();
    engine->RegisterObjectType("STank", 0, asOBJ_REF);
#pragma warning(push)
#pragma warning(disable:4191)
    engine->RegisterObjectBehaviour("STank", asBEHAVE_ADDREF, "void AddRef()", asMETHOD(Tank, AddRef), asCALL_THISCALL);
    engine->RegisterObjectBehaviour("STank", asBEHAVE_RELEASE, "void ReleaseRef()", asMETHOD(Tank, ReleaseRef), asCALL_THISCALL);
    engine->RegisterObjectProperty("STank", "bool inProcessFindPath", offsetof(STank, inProcessFindPath));
#pragma warning(pop)
}
