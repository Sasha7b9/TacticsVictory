// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class PanelMap;
    class PanelMain;
    class PanelBottom;
    
    class GUI : public Widget, public Singleton<GUI> {
    
    private:
        GUI();
    public:
        ~GUI();

        static void Create();

        static GUI *self;
    
        void Hide();
        void Show();
    
    private:
    };
}
