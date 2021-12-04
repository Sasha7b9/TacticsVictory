// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Cameras/CameraRTS.h"
#include "Shaders/SparkParticleSystem.h"


namespace Pi
{

    enum
    {
        kLocatorSpectator = 'spec'
    };
    
    class Battle : public Application, public Singleton<Battle>
    {
    public:
        Battle();
        ~Battle();
    
        virtual void ApplicationTask() override;

        void HandleOnButtonQuit(Widget *widget, const WidgetEventData *eventData);
    
        // ���������� ���� � �������� � ������� ���� (Data/TacticsVictory)
        std::string DataPath() const;
    
    private:
        DisplayEventHandler             displayEventHandler;
        LocatorRegistration             locatorReg;
    
        static World* ConstructWorld(pchar name, void *cookie);
        static void HandleDisplayEvent(const DisplayEventData *eventData, void *data);
    
        void CreateScene();
    };
    
    extern Battle *TheBattle;

}
