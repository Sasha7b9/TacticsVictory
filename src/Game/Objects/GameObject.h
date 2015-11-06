#pragma once

class GameObject : public LogicComponent
{
public:
    GameObject(Context *context = gContext);

    void SetAutoReloaded(int time) { timeForReload = time; };

    void Update(float timeStep);

protected:
    int timeForReload = 0;
    int timeLastReload = 0;
    unsigned timeLastModified = 0;

private:
    GameObject& operator=(const GameObject&) {};
};