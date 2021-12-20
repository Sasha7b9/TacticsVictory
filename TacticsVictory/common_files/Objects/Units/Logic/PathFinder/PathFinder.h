// 2021/12/4 11:09:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/Array2D_.h"


namespace Pi
{
    class UnitObject;

    namespace PiTypeController
    {
        const S PathFinder = "PathFinder";
    }


    // ----------------------------------------------------------------------------------------------------------------
    class PathFinderController : public Controller
    {
    public:
        PathFinderController() : Controller(PiTypeController::PathFinder) {}
    private:
        virtual void Preprocess() override;
        virtual void Move() override;
    };


    // ----------------------------------------------------------------------------------------------------------------
    class PathFinder : public Node
    {
        friend class PathFinderController;

    public:

        PathFinder(const Point2D &start, const Point2D &finish);

        // Метод принимает в качестве аргумента указатель на функцюи, в которую нужно передать результат вычисления
        void Find(std::function<void (const Array<Integer2D> &)>);

    private:

        virtual ~PathFinder()  {};

        Array<Integer2D> ToArray();

        void Clear();

        // В волне содержится набор клеток для каждой волны
        class Wave
        {
        public:
            int GetElementCount() const { return points.GetElementCount(); }
            void AddElement(const Integer2D &point) { points.AddElement(point); }
            // Добавить в волну клетку с координатами (col, row) и отметить её индекс в массиве num_wave
            void SetCell(int col, int row, int numWave, Array2D<int> &num_wave);
            bool Contain(const Integer2D &coord);

            Integer2D &operator[](int i) { return points[i]; }
            Integer2D &operator[](int i) const { return points[i]; }

        private:
            Array<Integer2D> points;
        };

        // Рассчитать и добавить следующую волну в массив волн
        void CalculateNextWave(Array<Wave> &waves);
        void AddPrevWave(Array<Integer2D> &path);
        void FindPath(Job *job);
        void SetSize();
        void StopSearch();
        void StartSearch();

        std::function<void(const Array<Integer2D> &path)> callbackComplete = nullptr;    // Эта функция будет вызвана после завершения поиска
        bool needSearching = false;             // Если true - нужно производить поиск
        bool pathIsFound = false;               // Если true - путь найден
        Integer2D start{0, 0};
        Integer2D finish{0, 0};
        Array2D<int> num_wave;                  // Здесь будет храниться номер волны (расстояние в клетках от точки начала поиска
        Array<Integer2D> path;                   // Здесь хранится рассчитанный путь
        Array2D<float> heightMap;               // Карта высот


        // Этот класс в отдельном потоке будет рассчитывать путь -----------------------------------------------------------
        class JobPathFinder : public Job
        {
        private:
            static void JobFunction(Job *, void *);
        public:
            JobPathFinder(PathFinder *_path) : Job(JobFunction, (void *)_path) {};
        };

        JobPathFinder *jobFinder = nullptr;
    };
}
