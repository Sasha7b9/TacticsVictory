// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/Units/Ground/Tank_.h"
#include "Objects/GameObjectParameters_.h"
#include "Scene/World/Landscape_.h"
#include "Objects/Staff/Driver_.h"
#include "Objects/Staff/DriverTasks_.h"


using namespace Pi;


Map<Tank> Tank::objects;



Tank *Tank::Create(int id)
{
    return new Tank(id);
}


Tank::Tank(int id) : GroundUnitObject(TypeGroundUnit::Tank, &parameters, id)
{
    GetNodeGeometry()->AppendNewSubnode(CreateBody());
    GetNodeGeometry()->AppendNewSubnode(CreateTrack(true));
    GetNodeGeometry()->AppendNewSubnode(CreateTrack(false));
    GetNodeGeometry()->AppendNewSubnode(CreateTower());
    GetNodeGeometry()->AppendNewSubnode(CreateBarrel());

    driver = Driver::Create(this);

    commander = new Commander(this);

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


CommanderTank::CommanderTank(GameObject *object) : Commander(object)
{
}
