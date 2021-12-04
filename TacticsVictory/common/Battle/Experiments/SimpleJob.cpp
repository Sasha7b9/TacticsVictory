// 2021/12/4 15:19:07 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Experiments/SimpleJob.h"


using namespace Pi;


SimpleJob::SimpleJob() : Job(SimpleJob::FunctionExecute)
{

}


void SimpleJob::FunctionExecute(Job *_job, void *)
{
    SimpleJob *job = SimpleJob::Self(_job);

    job->counter = 0;

    while (job->counter < INT_MAX)
    {
        job->counter++;
    }
}
