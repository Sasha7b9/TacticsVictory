#include <stdafx.h>
#include "Sun.h"


using namespace Pi;


static ControllerReg<SunController> *TheControllerSun = nullptr;


Sun::Sun() : Node("Sun")
{
    PointLight *spotLight = new PointLight(K::green->GetColorRGB(), 1000.0f);
    PointLightObject *lightObject = spotLight->GetObject();
    lightObject->SetFadeDistance(Range<float>(0.0f, 1000.0f));
    AppendNewSubnode(spotLight);

    PrimitiveGeometry *primGeometry = new SphereGeometry(Vector3D(radius, radius, radius));
    PrimitiveGeometryObject *obj = primGeometry->GetObject();
    obj->SetBuildLevelCount(1);
    primGeometry->Update();
    obj->Build(primGeometry);
    AppendNewSubnode(primGeometry);
    primGeometry->Update();

    MaterialObject *sphereMaterial = new MaterialObject();
    DiffuseAttribute *diffuse = new DiffuseAttribute(K::white->GetColorRGB());
    sphereMaterial->AddAttribute(diffuse);
    primGeometry->SetMaterialObject(0, sphereMaterial);
    sphereMaterial->Release();

    TheControllerSun = new ControllerReg<SunController>(PiTypeController::Sun, "Sun");
    controller = new SunController();
    SetController(controller);
    controller->Wake();
}

Sun::~Sun()
{
    SAFE_DELETE(TheControllerSun);
}

SunController::SunController() : Controller(PiTypeController::Sun)
{

}

void SunController::Preprocess()
{
    Controller::Preprocess();
}

void SunController::Move()
{
    Controller::Move();

    Node *node = GetTargetNode();

    float dT = TheTimeMgr->GetFloatDeltaTime();

    angle += dT * 1e-3f;

    float cosA = 0.0f;
    float sinA = 0.0f;

    CosSin(angle, &cosA, &sinA);

    node->SetNodePosition(Point3D(cosA * radius, sinA * radius, 0.0f) + center);
    //node->SetNodePosition(Point3D(5.0f, -0.15f, 2.0f));
    node->Invalidate();
}