// 2021/12/12 21:37:13 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/GameObject_.h"


namespace Pi
{
    // Класс для визуализации пути юнита
    class PathMapping : public Node
    {
    public:

        static PathMapping *empty;
        static void Construct();
        static void Destruct();

        PathMapping(const GameObject &object, const Array<Integer2D> &_path);

        // Возвращает указать на PathMapping для object, если таковой существует в сцене
        static PathMapping *FromScene(const GameObject &object);

        void Log();

    private:
        Array<Point2D> path;

        static String<> NameForObject(const GameObject &object);

        class CellPath : public Node, public ListElement<CellPath>
        {
        public:
            CellPath(const Integer2D &position);
            virtual ~CellPath() {};

            void MoveTo(const Integer2D &position);

        private:

            Node *CreateMember(const Integer2D &position);
        };
    };
}
