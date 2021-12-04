// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    class DrawingWidget;
    
    
    enum
    {
        kMutatorCursorGUI = 'curg'
    };
    
    
    class CursorGUI : public Widget, public Singleton < CursorGUI >
    {
    public:
    
        struct State
        {
            enum E
            {
                Normal,
                OverObject,                 // ������ ��������� ��� ��������, ������� ����� ���� �������
                OutScreenLeft,              // |
                OutScreenRight,             // |
                OutScreenUp,                // |
                OutScreenDown,              // | ��� ������� ��� ������, ����� ������
                OutScreenLeftUp,            // | �������� � ������� ��� ��������� �������
                OutScreenRightUp,           // |
                OutScreenRightDown,         // |
                OutScreenLeftDown,          // /
                kZoomIn,                    // ������ ����������� ������
                kZoomOut,                   // ������ �������� ������
                RotateLeft,                 // ������� ������ � ���� �������
                RotateRight,                // ������� ������ � ������ �������
                Count
            };
        };
    
        CursorGUI();
        ~CursorGUI();
    
        Point2D position;
    
        void Move() override;
    
    protected:
        virtual void Update() override;
    
    private:
        State::E state = State::E::Normal;
        Widget *mainWidget = nullptr;
    
        float currentFrame = 0.0f;
        static const int numFrames = 50;
        static const float speedAnimation;      // frames per second
        DrawingWidget *skins[State::Count][numFrames];
    
        void SetSkin(int numSkin);
        void PrepareSkins();
        DrawingWidget *CreateNormalOverSkin(int numFrame, State::E state);
        DrawingWidget *CreateOutScreenSkin(State::E state, int numFrame);
    };
    
    extern CursorGUI *TheCursor;
    
    class CursorGUIMutator final : public Mutator
    {
        friend class MutatorReg < CursorGUIMutator > ;
    
    public:
    
        CursorGUIMutator();
        ~CursorGUIMutator();
    
        void Move() override;
        void Reset() override;
    
    private:
    
        CursorGUIMutator(const CursorGUIMutator& cursorGUImutator);
    };

}
