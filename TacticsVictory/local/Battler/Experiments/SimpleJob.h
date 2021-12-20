// 2021/12/4 15:19:01 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

class SimpleJob : public Job
{
public:
    SimpleJob();

    static SimpleJob *Self(Job *job) { return (SimpleJob *)job; }

    int GetCounter() const { return counter; };

private:
    static void FunctionExecute(Job *, void *);

    int counter = 0;
};

}
