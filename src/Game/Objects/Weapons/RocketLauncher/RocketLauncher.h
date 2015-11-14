#pragma once


class RocketLauncher : public Object
{
    URHO3D_OBJECT(RocketLauncher, Object);
public:
    RocketLauncher(Context *context = gContext, Tank *tank = nullptr);

    void Init();
    void Update(float deltaStep);

private:
    RocketLauncher& operator=(const RocketLauncher&)
    {};

    Tank *tank = nullptr;

    float radiusDetect = 50.0f;
    float timeRecharge = 10.0f;
    float timeElapsedAfterShoot = 0.0f;

    Camera *cameraTarget = nullptr;         // Camera for determination of visibility of the target.
    SharedPtr<Texture2D> renderTexture;
    SharedPtr<RenderSurface> renderSurface;

    bool TargetInPointView(Tank* tank);

    void HandlePostRenderUpdate(StringHash, VariantMap&);
};