// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "Tank.h"


using namespace Pi;


GameObject *Tank::Create()
{
    Tank *node = new Tank();

    node->SetController(new TankController());

    Model *model = Model::Get(PiTypeModel::Tank);

    node->AppendNewSubnode(model);

    return node;
}


TankController::TankController() :
    GroundUnitController(PiTypeController::Tank)
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
