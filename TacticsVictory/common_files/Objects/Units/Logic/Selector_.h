// 2021/12/13 15:33:03 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
*   Визуализация выделяемой области и определение юнитов, находящихся на ней
*/


namespace Pi
{
    class Selector : public Node
    {
    public:

        Selector();
    };


    class SelectorController : public Controller
    {
    public:

        SelectorController();

    private:

        virtual void Move() override;

        bool captured = false;              // Если true - ноходимся в режиме захвата - левая кнопка мыши зажата

        void UpdateCaptured();

        void UpdateUnCaptured();
    };
}
