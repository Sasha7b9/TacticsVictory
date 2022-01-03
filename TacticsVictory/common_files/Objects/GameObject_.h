// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObjectTypes_.h"
#include "Objects/GameObjectParameters_.h"
#include "Objects/Staff/CommanderTasks_.h"
#include "System/Events_.h"


namespace Pi
{
    class GameObjectProperty;
    class InfoWindow;
    class UnitObject;
    class WorldObject;
    class Commander;
    class Driver;
    class Shooter;
    struct CommanderTask;


    class GameObject : public Node, public MapElement<GameObject>
    {
    public:

        typedef int KeyType;

        static Map<GameObject> objects;

        static GameObject *empty;

        static void Construct();
        static void Destruct();

        const int id = 0;

        GameObjectParameters &params;

        const TypeGameObject typeGameObject;

        Driver *driver = nullptr;      // Это водитель

        KeyType GetKey() const { return params.id; }

        bool IsUnit() const { return typeGameObject == TypeGameObject::Unit; }
        bool IsWorldObject() const { return typeGameObject == TypeGameObject::World; }

        Node *GetNodeGeometry() { return nodeGeometry; }

        void SetDirection(const Vector3D &direction, const Vector3D &up = Vector3D::UP);

        // Преобразует к указателю на UnitObject, если возможно, и возвращает nullptr в ином случае
        UnitObject *GetUnitObject() { return IsUnit() ? (UnitObject *)this : nullptr; }
        UnitObject *GetUnitObject() const { return IsUnit() ? (UnitObject *)this : nullptr; }
        WorldObject *GetWorldObject() { return IsWorldObject() ? (WorldObject *)this : nullptr; }

        // Добавить задание в конец очереди (оно выполнится после всех заданий)
        void AppendTask(CommanderTask *task);

        // Добавить объект в игру
        bool AppendInGame(int x, int y);

        virtual void Move(float dT);

        // Возвращает указатель на объект, кторый находится в экранных координатах coord
        static GameObject &GetFromScreen(const Point2D &coord);

        GameObjectProperty &GetGameObjectProperty() { return *(GameObjectProperty *)GetProperty(PiTypeProperty::GameObject); }

    protected:

        GameObject(TypeGameObject, const GameObjectParameters *, int);

        virtual ~GameObject();

        Commander *commander = nullptr;     // Это командир

        // Создаёт узел с именем name и подвешивает к нему узел с геометрией
        Node *CreateNodeForGeometry(pchar name, Node *nodeGeometry);

    private:

        GameObjectProperty *property        = nullptr;

        // Может ли обрабатывать задания типа type
        bool CanExecute(CommanderTask::Type type) const;

        virtual void Preprocess() override;

        Node *nodeGeometry = nullptr;           // На этом узле хранится геометрия

        static int createdObjects;              // Столько объектов уже создано

        // Прячем эту функцию, чтобы непосредственно нельзя было установить позицию. Позиция устанавливается
        // через члены GameObjectParameters
        void SetNodePosition(const Point3D &position);
    };


    class GameObjectProperty : public Property, public EventTarget
    {
        friend class GameObjectController;

    public:

        GameObjectProperty(GameObject &);

        virtual ~GameObjectProperty();

        bool Selectable() const { return gameObject.IsUnit(); }

        // Установить выделение
        void SetSelection();

        // Снять выделение
        void RemoveSelection();

        // Сюда посылается событие мыши : 0 - левая кнопка, 1 - средняя кнопка, 2 - правая кнопка
        void MouseEvent(uint state);

        bool Selected() const { return selected; }

        // Возвращает GameObjectProperty в позиции на экране, указываемой координатами coord
        static GameObjectProperty *GetFromScreen(const Point2D &coord);

        GameObject &gameObject;

        bool        selected = false;
        InfoWindow *infoWindow = nullptr;
    };
}
