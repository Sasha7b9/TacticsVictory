// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    class SharedString : public Shared
    {
    public:
        SharedString(char *text);
    
    protected:
        virtual ~SharedString();
    
    private:
        char *buffer = nullptr;
    };

}
