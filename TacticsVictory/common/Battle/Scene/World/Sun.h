// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

    class SunController;
    
    namespace PiTypeController
    {
        const S Sun = 'sun_';
    }

    class Sun : public Node
    {
    
    public:
        Sun();
        virtual ~Sun();
    private:
        SunController *controller = nullptr;
        float radius = 1.0f;
    };
    
    class SunController final : public Controller
    {
    public:
    
        SunController();
    
        void SetParameters(const Point3D &_center)
        {
            this->center = _center;
        }
        virtual void Preprocess() override;
        virtual void Move() override;
    
    private:
        float angle = 0.0f;
        float radius = 5.0f;
        Point3D center = Point3D(0.0f, 0.0f, 50.0f);
    };

}
