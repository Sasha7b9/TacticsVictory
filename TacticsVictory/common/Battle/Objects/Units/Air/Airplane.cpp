// 2021/12/15 21:10:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Air/Airplane.h"


using namespace Pi;


Airplane *Airplane::Create()
{
    Airplane *node = new Airplane();

    node->SetController(new AirplaneController());

    return node;
}


Airplane::Airplane() : AirUnitObject(TTypeAirUnit::Airplane)
{
    PrimitiveGeometry *geometry = new PyramidGeometry({1.0f, 1.0f}, 1.0f);
    geometry->GetObject()->Build(geometry);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.4f, 0.4f, 0.6f});
    material->AddAttribute(diffuse);
    geometry->SetMaterialObject(0, material);
    material->Release();

    Node *rootNode = new Node();

    rootNode->SetNodeTransform({1.0f, 0.2f, 1.0f}, {-0.5f, -0.1f, 0.0f}, Transform4D().SetRotationAboutX(-K::pi / 2.0f));

    rootNode->AppendNewSubnode(geometry);

    AppendNewSubnode(rootNode);
}


Airplane::~Airplane()
{

}


AirplaneController::AirplaneController() : AirUnitController(TTypeAirUnit::Airplane)
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
}


void AirplaneController::Move()
{
    AirUnitController::Move();

    float speed = 1.0f;

    float dT = TheTimeMgr->GetDeltaSeconds();

    Point3D position = GetTargetNode()->GetNodePosition();
    position.y += dT * speed;

    GetTargetNode()->SetNodePosition(position);
    GetTargetNode()->Invalidate();
}
