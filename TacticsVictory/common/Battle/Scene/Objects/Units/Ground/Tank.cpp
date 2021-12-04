#include <stdafx.h>
#include "Tank.h"


using namespace Pi;


Tank::Tank() :
    tankControllerRegistration(PiTypeController::Tank, "Tank"),
    tankModelRegistration(PiTypeModel::Tank, "Tank", "models/Tank", ModelRegistrationFlag::Precache, PiTypeController::Tank)
{
}


GameObject *Tank::Create()
{
    Tank *node = new Tank();

    node->SetController(new TankController());

    Model *model = Model::Get(PiTypeModel::Tank);

    node->AppendNewSubnode(model);

    return node;
}


TankController::TankController() :
    GroundUnitController(GroundUnitController::Type::Tank, PiTypeController::Tank)
{

}


TankController::TankController(const TankController& tankController) :
    GroundUnitController(tankController)
{

}


TankController::~TankController()
{

}


Controller *TankController::Replicate() const
{
    return new TankController(*this);
}


void TankController::Preprocess()
{
    GameObjectController::Preprocess();
}
