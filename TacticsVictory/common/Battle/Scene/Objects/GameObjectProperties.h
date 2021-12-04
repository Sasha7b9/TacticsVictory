// 2021/12/2 22:09:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Objects/Indicator.h"


namespace Pi
{
    class GameObject;

    namespace PiTypeProperty
    {
        const S GameObject = "GameObject";
    }

    class GameObjectProperty : public Property
    {
        friend class GameObjectController;

    public:

        GameObjectProperty(GameObject *);

        virtual ~GameObjectProperty();

        bool IsSelectable() const { return true; }

        // Установить выделение
        void SetSelection();

        void SetMapPosition(float x, float y) { positionMap = {x, y}; }

        // Снять выделение
        void RemoveSelection();

        bool IsSelected() const { return selection; }

        GameObject *GetGameObject() { return gameObject; }

    private:

        GameObject *gameObject;
        bool        selection = false;
        Indicator  *indicator;
        Vector3D    rotate;
        float       scale = 1.0F;
        Vector2D    positionMap{0.0f, 0.0f};
    };
}
