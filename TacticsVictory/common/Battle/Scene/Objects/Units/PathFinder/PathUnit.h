// 2021/12/4 11:09:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


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

        void Find(const UnitObject *unit, const Point2D &destionation);

        void Find(const Point2D &source, const Point2D &destination);

        bool PathIsFound();

        Array<Point2D> ToArray();

        void Destroy();

    private:

        typedef Array<Point2D> Wave;

        void SetCell(Wave &wave, uint row, uint col, int numWave);
        void NextWave(Array<Wave> &waves);
        bool Contain(const Wave &wave, const Point2D &coord);
        void AddPrevWave(Array<Point2D> &path);
        void FindPath();
        void SetSize();
        void Visualize();

        bool pathIsFound = false;
        Point2D start{0.0f, 0.0f};
        Point2D end{0.0f, 0.0f};
        Array<Array<int>> cells;
        float heightStart = 0.0f;
        uint numRows = 0U;                    // Количество ячеек по X
        uint numCols = 0U;                    // Количество ячеек по Y
        Array<Point2D> path;                  // Здесь хранится рассчитанный путь
        Landscape *landscape = landscape;


        // Этот класс в отдельном потоке будет рассчитывать путь -----------------------------------------------------------
        class JobPathFinder : public Job
        {
        private:
            static void JobFunction(Job *, void *);
        public:
            JobPathFinder(PathUnit *_path) : Job(JobFunction, (void *)_path)
            {};
        };

        JobPathFinder *jobFinder = nullptr;


        // Класс визуализирует путь перемещения юнита -----------------------------------------------------------------------
        class CellPath : public Node
        {
        public:
            CellPath(const Point2D &position);

        private:

            Node *CreateMember(const Point2D &position);
        };
    };
}
