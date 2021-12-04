// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Cameras/CameraRTS.h"


namespace Pi
{
    class Landscape;
    class GameObject;
    class GameObjectProperty;

    class GameWorld : public World
    {
    
    public:
    
        GameWorld(pchar name);
        ~GameWorld();
    
        WorldResult::B Preprocess() override;

        static GameWorld *Get();
    
        virtual void Render() override;

        virtual void Move() override;
    
        void ChangeCursorPosition(float deltaX, float deltaY);

        Landscape *GetLandscape() const { return landscape; }

        // Возвращает указатель на объект, кторый находится в экранных координатах coord
        GameObject *GameObjectInPosition(const Point2D &coord);
        GameObjectProperty *GameObjectPropertyInPosition(const Point2D &coord);

        // Преобразует мировые координаты точки в экранные
        Point3D TransformWorldCoordToDisplay(const Point3D &worldPosition);

        void AppendGameObject(GameObject *gameObject);
    
    private:
    
        static const LocatorMarker *FindSpectatorLocator(const Zone *zone);
    
        Landscape *landscape = nullptr;
    };
    
    extern GameWorld *TheGameWorld;
}
