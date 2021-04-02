// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Game/Logic/SunEngine_.h"
#include "Network/Game/Messages/GameMessages_.h"
#include "Scene/SceneC.h"
#include "Scene/Cameras/Camera.h"
#include "Scene/Objects/ObjectC.h"
#include "Scene/Objects/Units/Ground/Tank/Tank_.h"
#include "Scene/Terrain/Level_.h"


namespace Message
{
    void Message::Handle(VariantMap &map)
    {
        MemoryBuffer msg(map[NetworkMessage::P_DATA].GetBuffer());

        switch (id)
        {
        case CLNT_RETURN_LEVEL:       ((ReturnLevel *)this)->Handle(msg);      break;
        case CLNT_CREATE_GAME_OBJECT: ((CreateGameObject *)this)->Handle(msg); break;
        case CLNT_SEND_TANK_POSITION: ((SendTankPosition *)this)->Handle(msg); break;
        case CLNT_SEND_SCENE:         ((SendScene *)this)->Handle(msg);        break;
        }

    }
}


void Message::Message::Send(bool reliable)
{
    Connection *connection = TheNetwork->GetServerConnection();

    if (connection)
    {
        connection->SendMessage(id, reliable, reliable, buffer);
    }
}


void Message::ReturnLevel::Handle(MemoryBuffer &msg)
{
    TheScene->Create();

    TheTerrain = new TerrainT();
    TheTerrain->level->Load(msg);
    TheTerrain->CreateFromVector(TheTerrain->level->map);

    SharedPtr<Node> lightNode;
    lightNode = TheScene->CreateChild("LigthNode");
    SunEngine *sunEngine = lightNode->CreateComponent<SunEngine>(LOCAL);
    sunEngine->SetCenter({ TheTerrain->HeightX() / 2.0f, 50.0f, TheTerrain->WidthZ() / 2.0f });
    sunEngine->SetMoveSpeed(0.1f);

    Light *light = lightNode->CreateComponent<Light>(LOCAL);
    lightNode->SetScale(0.01f);
    light->SetLightType(LIGHT_POINT);
    light->SetRange(1000.0f);
    light->SetCastShadows(true);
    light->SetShadowBias(BiasParameters(0.00011f, 2.0f));
    light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
    light->SetEnabled(true);

    ThePathIndicator = new PathIndicator();

    TheCamera = CameraT::Create();
}


void Message::CreateGameObject::Handle(MemoryBuffer &msg)
{
    uint idNode = msg.ReadUInt();
    StringHash hashTypeObject = msg.ReadStringHash();
    Vector3 position = msg.ReadVector3();
    Quaternion rotation = msg.ReadQuaternion();

    ObjectT *object = (ObjectT *)TheScene->CreateChild("", LOCAL)->CreateComponent(hashTypeObject, LOCAL);

    object->physics->pos.SetWorld(position);

    object->physics->rot.SetWorld(rotation);

    ObjectSpecificC::remoteStorage[idNode] = object;
}


void Message::SendTankPosition::Handle(MemoryBuffer &msg)
{
    String name = msg.ReadString();

    Node *node = TheScene->GetChild(name);

    if (node)
    {
        node->SetPosition(msg.ReadVector3());
    }
}


void Message::SendScene::Handle(MemoryBuffer &msg)
{
    TheScene->Decompress(msg);
}
