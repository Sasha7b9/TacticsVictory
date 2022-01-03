// 2021/12/15 21:10:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/GameObjectParameters_.h"
#include "Utils/Math_.h"
#include "Objects/PoolObjects_.h"
#include "Objects/Staff/Commander_.h"


#ifdef PiCLIENT
    #include "GameWorld.h"
    #include "Graphics/Effects/SmokeTrail.h"
#endif


using namespace Pi;


Map<Airplane> Airplane::objects;


SmokeTrailParticleSystem *Airplane::smokeTrail = nullptr;


Airplane *Airplane::Create(int id)
{
    return new Airplane(id);
}


Airplane::Airplane(int _id) : AirUnitObject(TypeAirUnit::Airplane, &parameters, _id)
{
    PrimitiveGeometry *geometry = new PyramidGeometry({1.0f, 1.0f}, 1.0f);
    geometry->GetObject()->Build(geometry);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.4f, 0.4f, 0.6f});
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    Node *bodyNode = new Node();
    bodyNode->SetNodeName("Body");

    bodyNode->SetNodeTransform({1.0f, 0.05f, 0.5f}, {-0.5f, -0.025f, 0.0f}, Transform4D().SetRotationAboutX(-K::pi / 2.0f));

    bodyNode->AppendNewSubnode(geometry);

    GetNodeGeometry()->AppendNewSubnode(bodyNode);

    driver = Driver::Create(this);

    commander = new Commander(this);

    objects.Insert(this);

#ifdef PiCLIENT

    if (smokeTrail == nullptr)
    {
        smokeTrail = new SmokeTrailParticleSystem({0.5f, 0.5f, 1.0f, 1.0f});
        GameWorld::self->AddNewNode(smokeTrail);
    }

#endif
}
