﻿// 2021/12/4 11:09:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Array2D.h"
#include "Utils/Point2DI.h"


namespace Pi
{
    class UnitObject;

    namespace PiTypeController
    {
        const S PathUnit = "PathUnit";
    }

    class PathUnitController : public Controller
    {
    public:
        PathUnitController() : Controller(PiTypeController::PathUnit) {}
    private:
        virtual void Move() override;
    };

    class PathUnit : public Node, public Singleton<PathUnit>
    {
        friend class PathUnitController;

    public:
        // Конструктор принимает указатель на оъект, которого требуется переместить в точку destination и собственно destination
        PathUnit();
        virtual ~PathUnit() {};

        static PathUnit *self;

        // Установить цель для наблюдения
        void SetTarget(const UnitObject *uint);

        // Снять наблюдение
        void RemoveTarget();

        Array<Point2DI> ToArray();

        void Clear();

    private:

        // В волне содержится набор клеток для каждой волны
        class Wave
        {
        public:
            int GetElementCount() const { return points.GetElementCount(); }
            void AddElement(const Point2DI &point) { points.AddElement(point); }
            // Добавить в волну клетку с координатами (col, row) и отметить её индекс в массиве num_wave
            void SetCell(int col, int row, int numWave, Array2D<int> &num_wave);
            bool Contain(const Point2DI &coord);

            Point2DI &operator[](int i) { return points[i]; }
            Point2DI &operator[](int i) const { return points[i]; }

        private:
            Array<Point2DI> points;
        };

        // Рассчитать и добавить следующую волну в массив волн
        void CalculateNextWave(Array<Wave> &waves);
        void AddPrevWave(Array<Point2DI> &path);
        void FindPath(Job *job);
        void SetSize();
        void Visualize();                       // Отобразить найденный путь
        void StopSearch();
        void StartSearch();

        const UnitObject *target = nullptr;     // Цель для наблюдения
        bool needSearching = false;             // Если true - нужно производить поиск
        bool pathIsFound = false;               // Если true - путь найден
        Point2DI start{0, 0};
        Point2DI end{0, 0};
        Array2D<int> num_wave;                  // Здесь будет храниться номер волны (расстояние в клетках от точки начала поиска
        Array<Point2DI> path;                   // Здесь хранится рассчитанный путь
        Array2D<float> heightMap;               // Карта высот
        bool visualized = false;                // Если true, то путь уже визуализирован


        // Этот класс в отдельном потоке будет рассчитывать путь -----------------------------------------------------------
        class JobPathFinder : public Job
        {
        private:
            static void JobFunction(Job *, void *);
        public:
            JobPathFinder(PathUnit *_path) : Job(JobFunction, (void *)_path) {};
        };

        JobPathFinder *jobFinder = nullptr;


        // Класс визуализирует путь перемещения юнита -----------------------------------------------------------------------
        class CellPath : public Node, public ListElement<CellPath>
        {
        public:
            CellPath(const Point2DI &position);
            virtual ~CellPath() {};

            void MoveTo(const Point2DI &position);

            static List<CellPath> chains;                   // Здесь хранятся визуализированные клеточки

        private:

            Node *CreateMember(const Point2D &position);
        };
    };
}
