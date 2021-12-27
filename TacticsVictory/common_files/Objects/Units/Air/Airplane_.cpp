// 2021/12/15 21:10:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/UnitParameters_.h"
#include "Utils/Math_.h"


using namespace Pi;


Map<Airplane> Airplane::objects;


Airplane *Airplane::Create(int id)
{
    return new Airplane(id);
}


Airplane::Airplane(int id) : AirUnitObject(TypeAirUnit::Airplane, id, new AirplaneController(this))
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

    objects.Insert(this);
}


DriverAirplane::DriverAirplane(UnitController *controller) :
    Driver(controller)
{
/*
#ifdef PiSERVER
    controller->param.speed = Math::RandomFloat(0.01f, 1.0f);
    controller->param.direction.RotateAboutZ((float)rand() / 1e3f);
#endif
*/
}


void DriverAirplane::Update(float dT)
{
    UnitParameters &param = controller->param;

    if(param.speed == 0.0f)
    {
        param.direction.RotateAboutZ(K::pi / 2.0f / 1000.0f * (float)rand());

        param.speed = Math::RandomFloat(0.25f, 1.0f);
        param.speedRotate.x = Math::RandomFloat(0.5f, 1.5f);
        param.speedRotate.y = Math::RandomFloat(0.5f, 1.5f);
        param.speedRotate.z = Math::RandomFloat(0.5f, 1.5f);
    }

    MoveForward(dT);

    YawCompensate(dT);

    Roll(dT);

    PitchCompensate(dT);

    unit->SetDirection(param.direction, param.up);
    unit->Invalidate();
}
