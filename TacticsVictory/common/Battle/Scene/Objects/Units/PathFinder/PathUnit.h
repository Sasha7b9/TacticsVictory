// 2021/12/4 11:09:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Array2D.h"


namespace Pi
{
    class UnitObject;
    class Landscape;

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

        Array<Point2D> ToArray();

    private:

        typedef Array<Point2D> Wave;

        void SetCell(Wave &wave, uint row, uint col, int numWave);
        void NextWave(Array<Wave> &waves);
        bool Contain(const Wave &wave, const Point2D &coord);
        void AddPrevWave(Array<Point2D> &path);
        void FindPath(Job *job);
        void SetSize();
        void Visualize();                       // Отобразить найденный путь
        void Clear();
        void StopSearch();
        void StartSearch();

        const UnitObject *target = nullptr;     // Цель для наблюдения
        bool needSearching = false;             // Если true - нужно производить поиск
        bool pathIsFound = false;               // Если true - путь найден
        Point2D start{0.0f, 0.0f};
        Point2D end{0.0f, 0.0f};
        Array2D<int> cells;
        float heightStart = 0.0f;
        uint numRows = 0U;                      // Количество ячеек по X
        uint numCols = 0U;                      // Количество ячеек по Y
        Array<Point2D> path;                    // Здесь хранится рассчитанный путь
        Landscape *landscape = nullptr;
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
            CellPath(const Point2D &position);
            virtual ~CellPath() {};

            void MoveTo(const Point2D &position);

            static List<CellPath> chains;                   // Здесь хранятся визуализированные клеточки

        private:

            Node *CreateMember(const Point2D &position);
        };
    };
}
