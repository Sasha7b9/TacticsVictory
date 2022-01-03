/// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/World/Sun_.h"
#include "Objects/Staff/DriverTasks_.h"
#include "Objects/Staff/Driver_.h"
#include "Objects/Staff/Commander_.h"


using namespace Pi;


class DriverTaskSun : public DriverTask
{
public:
    DriverTaskSun(Driver *driver) : DriverTask(driver) { }
    virtual void RunStep(float dT) override
    {
        angle += dT;
        float cosA, sinA;
        CosSin(angle, &cosA, &sinA);
        params.cur.position = Point3D(cosA * radius, sinA * radius, 0.0f) + center;
        params.apply_translation = true;
    }
private:
    float angle = 0.0f;
    float radius = 5.0f;
    Point3D center{50.0f, 50.0f, 30.0f};
};


Sun::Sun(int id) : WorldObject(TypeWorldObject::Sun, &parameters, id)
{
    PointLight *spotLight = new PointLight(K::green->GetColorRGB(), 10000.0f);
    PointLightObject *lightObject = spotLight->GetObject();
    lightObject->SetFadeDistance(Range<float>(0.0f, 10000.0f));
    GetNodeGeometry()->AppendNewSubnode(spotLight);

    PrimitiveGeometry *primGeometry = new SphereGeometry(Vector3D(radius, radius, radius));
    PrimitiveGeometryObject *obj = primGeometry->GetObject();
    obj->SetBuildLevelCount(1);
    primGeometry->Update();
    obj->Build(primGeometry);
    GetNodeGeometry()->AppendNewSubnode(primGeometry);
    primGeometry->Update();

    MaterialObject *sphereMaterial = new MaterialObject();
    SpecularAttribute *diffuse = new SpecularAttribute(K::white->GetColorRGB(), 1.0f);
    sphereMaterial->AddAttribute(diffuse);
    primGeometry->SetMaterialObject(0, sphereMaterial);
    sphereMaterial->Release();

    driver = Driver::Create(this);
    commander = new Commander(this);

    driver->AppendTask(new DriverTaskSun(driver));
}
