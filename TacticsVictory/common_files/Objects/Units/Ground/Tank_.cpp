// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/Units/UnitParameters_.h"
#include "Scene/World/Landscape_.h"
#include "Objects/Units/Staff/Driver_.h"
#include "Objects/Units/Staff/DriverTasks_.h"


using namespace Pi;


Map<Tank> Tank::objects;



Tank *Tank::Create(int id)
{
    return new Tank(id);
}


Tank::Tank(int id) : GroundUnitObject(TypeGroundUnit::Tank, id, new TankController(this))
{
    GetNodeGeometry()->AppendNewSubnode(CreateBody());
    GetNodeGeometry()->AppendNewSubnode(CreateTrack(true));
    GetNodeGeometry()->AppendNewSubnode(CreateTrack(false));
    GetNodeGeometry()->AppendNewSubnode(CreateTower());
    GetNodeGeometry()->AppendNewSubnode(CreateBarrel());

    objects.Insert(this);
}


Node* Tank::CreateBody()
{
    float sizeX = 0.4f;
    float sizeY = 0.5f;
    float sizeZ = 0.15f;

    PrimitiveGeometry *body = new BoxGeometry({sizeX, sizeY, sizeZ});
    body->GetObject()->Build(body);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.5f, 0.1f, 0.3f});
    material->AddAttribute(diffuse);
    body->SetMaterialObject(0, material);
    material->Release();

    Node *bodyNode = new Node();
    bodyNode->AppendNewSubnode(body);
    
    Transform4D transform;
    transform.SetIdentity();
    transform.SetTranslation(-sizeX / 2.0f, -sizeY / 2.0f, 0.05f);
    bodyNode->SetNodeTransform(transform);

    return CreateNodeForGeometry("Body", bodyNode);
}


Node *Tank::CreateTrack(bool left)
{
    float sizeX = 0.1f;
    float sizeY = 0.95f;
    float sizeZ = 0.25f;

    PrimitiveGeometry *track = new BoxGeometry({sizeX, sizeY, sizeZ});
    track->GetObject()->Build(track);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.5f, 0.1f, 0.3f});
    material->AddAttribute(diffuse);
    track->SetMaterialObject(0, material);
    material->Release();

    Node *nodeTrack = new Node();
    nodeTrack->AppendNewSubnode(track);

    Transform4D transform;
    transform.SetIdentity();
    transform.SetTranslation(left ? -0.2f - sizeX : 0.2f, -sizeY / 2.0f, 0.0f);
    nodeTrack->SetNodeTransform(transform);

    return CreateNodeForGeometry(left ? "TrackLeft" : "TrackRight", nodeTrack);
}


Node *Tank::CreateTower()
{
    float size = 0.15f;
    float height = 0.2f;

    PrimitiveGeometry *tower = new CylinderGeometry({size, size}, height);
    tower->GetObject()->Build(tower);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.5f, 0.1f, 0.3f});
    material->AddAttribute(diffuse);
    tower->SetMaterialObject(0, material);
    material->Release();

    Node *nodeTower = new Node();
    nodeTower->AppendNewSubnode(tower);

    Transform4D transform;
    transform.SetIdentity();
    transform.SetTranslation(0.0f, 0.0f, 0.2f);
    nodeTower->SetNodeTransform(transform);

    return CreateNodeForGeometry("Tower", nodeTower);
}


Node *Tank::CreateBarrel()
{
    float size = 0.02f;
    float height = 0.5f;

    PrimitiveGeometry *barrel = new CylinderGeometry({size, size}, height);
    barrel->GetObject()->Build(barrel);

    MaterialObject *material = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute({0.2f, 0.05f, 0.7f});
    material->AddAttribute(diffuse);
    barrel->SetMaterialObject(0, material);
    material->Release();

    Node *node = new Node();
    node->AppendNewSubnode(barrel);

    Transform4D transform;
    transform.SetIdentity();
    transform.SetRotationAboutX(-1.5f);

    node->SetNodeTransform(transform);
    node->SetNodePosition({0.0f, 0.12f, 0.3f});

    return CreateNodeForGeometry("Barrel", node);
}


TankController::TankController(Tank *tank) : GroundUnitController(tank, parameters)
{
}


TankController::~TankController()
{
}


void TankController::Preprocess()
{
    GroundUnitController::Preprocess();
}


CommanderTank::CommanderTank(UnitController *controller) : Commander(controller)
{
}


void CommanderTank::ParseMove(const CommanderTask *task) const
{
    float dest_x = task->destination.x;
    float dest_y = task->destination.y;
    float dest_z = Landscape::self->GetHeightCenter(task->destination);

    if (dest_x < 0.0f || dest_x >= (float)Landscape::self->GetSizeX_Columns() ||
        dest_y < 0.0f || dest_y >= (float)Landscape::self->GetSizeY_Rows())
    {
        return;
    }

    float z = Landscape::self->GetHeightCenter(unit->GetNodePosition());

    if (dest_z != z)
    {
        return;
    }

    driver->AppendTask(new DriverTaskMove(driver, {dest_x, dest_y, dest_z}));
}


DriverTank::DriverTank(UnitController *controller) : Driver(controller)
{
}


ShooterTank::ShooterTank(UnitController *controller) : Shooter(controller)
{
}
