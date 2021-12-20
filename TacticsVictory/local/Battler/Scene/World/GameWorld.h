// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class Landscape;
    class GameObject;
    class GameObjectProperty;

    class GameWorld : public World
    {
    public:

        GameWorld(pchar name);

        virtual ~GameWorld();

        virtual WorldResult::B Preprocess() override;

        static GameWorld *self;

        virtual void Render() override;

        virtual void Move() override;

        void ChangeCursorPosition(float deltaX, float deltaY);

        // Преобразует мировые координаты точки в экранные
        Point3D TransformWorldCoordToDisplay(const Point3D &worldPosition);

    private:

        static const LocatorMarker *FindSpectatorLocator(const Zone *zone);

        void CreateObjects();
    };
}
