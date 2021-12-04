#pragma once
#include "Scene/Objects/GameObjectProperties.h"


namespace Pi
{
    class GameObject : public Node
    {
    public:

        static GameObject &Empty();

        GameObjectProperty *GetGameObjectProperty();

        // Установить координаты объекта на карте. От мировых они отличаются на 0.5f
        void SetMapPosition(float mapX, float mapY);

    protected:

        GameObject();

        virtual ~GameObject() {}

    private:
        void SetNodePosition(const Point3D &position);
    };

    
    class GameObjectController : public Controller, public LinkTarget<GameObjectController>
    {
    
    public:

        enum class Type
        {
            Unit
        };
    
        virtual ~GameObjectController();
    
        virtual void Preprocess() override;
        virtual void Move() override;
    
    protected:
    
        GameObjectController(Type gameObjType, PiTypeController::S contrType);
        GameObjectController(const GameObjectController &gameObjectController);
    
    private:
    
        Type gameObjectType;
    
        float scaleDefault = 1.0F;
        Vector3D rotateDefault {Vector3D::ZERO};
    
    
        Point3D coordGame;
    };
}
