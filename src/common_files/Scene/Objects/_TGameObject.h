// 2021/02/18 22:31:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class GameObject : public LogicComponent
{
    URHO3D_OBJECT(GameObject, LogicComponent);

public:

    virtual void FixedUpdate(float time) override = 0;

    static Vector<GameObject *> storage;

protected:

    void LoadFromJSON(const String &file);

    GameObject(Context *context);

private:

    SharedPtr<StaticModel> staticModel;

    float speed = 0.0f;

    float deltaRotate = 0.0f;
};
