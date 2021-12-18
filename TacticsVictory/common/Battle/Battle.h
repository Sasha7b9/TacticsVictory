// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Scene/Cameras/CameraRTS.h"
#include "Shaders/SparkParticleSystem.h"


namespace Pi
{
    namespace PiTypeLocator
    {
        const S Spectator = 'spec';
    }

    class Battle : public Application, public Singleton<Battle>
    {
    public:
        Battle();
        ~Battle();

        static Battle *self;

        virtual void ApplicationTask() override;

        void HandleOnButtonQuit(Widget *widget, const WidgetEventData *eventData);

        // ¬озвращает путь к каталогу с данными игры (Data/TacticsVictory)
        std::string DataPath() const;

        void ReloadLandscape() const;

    private:

        CommandObserver<Battle> gizmoCommandObserver { this, &Battle::HandleGizmoCommand };
        CommandObserver<Battle> fogDensityCommandObserver { this, &Battle::HandleFogDensityCommand };

        DisplayEventHandler    displayEventHandler{&HandleDisplayEvent};
        LocatorRegistration    locatorReg{PiTypeLocator::Spectator, "Spectator Camera"};

        static World *ConstructWorld(pchar name, void *cookie);

        static void HandleDisplayEvent(const DisplayEventData *eventData, void *data);

        virtual void HandleGameEvent(GameEvent::E event, const void *param) override;

        void HandleGizmoCommand(Command *, pchar);
        void HandleFogDensityCommand(Command *, pchar);

        void CreateScene();

        void CreateCommands();
    };
}
