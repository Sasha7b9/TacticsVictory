// 2021/12/29 19:00:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Objects/PoolObjects_.h"
#include "Objects/Units/UnitParameters_.h"
#include "PeriodicTasks.h"


/*
*   Попытки увеличения скорости расчёта путём выделения каждому потоку своего упорядоченного пула данных
*  закончились неудачей. Разницы нет. Вероятно, потому, что для расчёта берутся данные и из других мест
*/


namespace Pi
{
    namespace PoolObjects
    {
        const int MAX_NUM_OBJECTS = 1000;
        static UnitParameters pool[MAX_NUM_OBJECTS + 1];    // 1 нужно прибавлять потому, что нумерация объектов начинается с нуля,
                                                            // id == 0 соответствует "пустому" объекту

//        // Стрктура для пула одного потока
//        struct PoolThread
//        {
//            UnitParameters *parameters = nullptr;
//        };
//
//        // Массив структур для потоков
//        PoolThread *pools = nullptr;
    }
}


using namespace Pi;


UnitParameters *PoolObjects::AllocateParameters(int id)
{
    return &pool[id];

//    int num_pool = id % TaskMain::NumberThreads();
//    int num_object = id / TaskMain::NumberThreads();
//
//    return &pools[num_pool].parameters[num_object];
}


void PoolObjects::Consruct()
{
//    pools = new PoolThread[(size_t)TaskMain::NumberThreads()];
//
//    for (int i = 0; i < TaskMain::NumberThreads(); i++)
//    {
//        pools[i].parameters = new UnitParameters[(size_t)(MAX_NUM_OBJECTS / (TaskMain::NumberThreads() - 1) + 1)];
//    }
}


void PoolObjects::Destruct()
{

}
