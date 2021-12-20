// 2021/12/15 21:10:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/Airplane_.h"
#include "Objects/Units/UnitParameters_.h"


using namespace Pi;


Airplane *Airplane::Create()
{
    Airplane *node = new Airplane();

    node->SetController(new AirplaneController());

    return node;
}


Airplane::Airplane() : AirUnitObject(TypeAirUnit::Airplane)
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
}


Airplane::~Airplane()
{

}


AirplaneController::AirplaneController() : AirUnitController(TypeAirUnit::Airplane, &parameters)
{

}


AirplaneController::AirplaneController(const AirplaneController &controller) : AirUnitController(controller)
{

}


AirplaneController::~AirplaneController()
{

}


Controller *AirplaneController::Replicate() const
{
    return new AirplaneController(*this);
}


void AirplaneController::Preprocess()
{
    AirUnitController::Preprocess();

    param->speed.y = Math::RandomFloat(0.00001f, 0.003f);
}


void AirplaneController::Move()
{
    AirUnitController::Move();
}


CommanderAirplane::CommanderAirplane(UnitController *controller) : Commander(controller)
{

}


DriverAirplane::DriverAirplane(UnitController *controller) : Driver(controller)
{

}


ShooterAirplane::ShooterAirplane(UnitController *controller) : Shooter(controller)
{

}
