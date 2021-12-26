// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    class Mouse;
    class TButton;
    class PanelMap;

    class MouseObservable : public Observable<MouseObservable, Type>
    {
    public:
        MouseObservable()
        {
        };
        virtual ~MouseObservable();
    private:
    };
    
    
    class Mouse : public Singleton<Mouse>
    {
    public:
    
        enum class Event
        {
            LeftChanged,
            MiddleChanged,
            RightChanged,
            PositionChanged
        };

        static void Create();

        virtual ~Mouse() { }

        static Mouse *self;
    
        void AddObserver(Observer<TButton, MouseObservable> *observer);
        void AddObserver(Observer<PanelMap, MouseObservable> *observer);
    
        void ChangePos(int posX, int posY)
        {
            leftNowPressed = false;
            leftNowReleased = false;
            pos.x = (float)posX;
            pos.y = (float)posY;
            observable.PostEvent((int)Event::LeftChanged);
        }
    
        bool LeftIsPressed()
        {
            return leftIsPressed;
        }
    
        bool LeftNowReleased()
        {
            return leftNowReleased;
        }
    
        void SetLeftPressed();
    
        void SetLeftReleased();
    
        void SetMiddlePressed()
        {
            middleIsPressed = true;
            observable.PostEvent((int)Event::MiddleChanged);
        }
    
        bool MiddleIsPressed()
        {
            return middleIsPressed;
        }
    
        void SetMiddleReleased()
        {
            middleIsPressed = false;
            observable.PostEvent((int)Event::MiddleChanged);
        }
    
        bool RightIsPressed()
        {
            return rightIsPressed;
        }
    
        void SetRightPressed()
        {
            rightIsPressed = true;
            observable.PostEvent((int)Event::RightChanged);
        }
    
        void SetRightReleased()
        {
            rightIsPressed = false;
            observable.PostEvent((int)Event::RightChanged);
        }
    
        Point2D GetPosition()
        {
            return pos;
        }
    
    private:

        Mouse() : Singleton<Mouse>(self) { }

        MouseObservable observable;
        Point2D pos;
    
        bool leftNowPressed = false;
        bool leftNowReleased = false;
        bool leftIsPressed = false;
    
        bool rightNowPressed = false;
        bool rightNowReleased = false;
        bool rightIsPressed = false;
    
        bool middleNowPressed = false;
        bool middleNowReleased = false;
        bool middleIsPressed = false;
    };

}
