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


    class Battler : public Application, public Singleton<Battler>
    {
    public:
        Battler();
        ~Battler();

        static Battler *self;

        virtual void ApplicationTask() override;

        void HandleOnButtonQuit(Widget *widget, const WidgetEventData *eventData);

        // ¬озвращает путь к каталогу с данными игры (Data/TacticsVictory)
        std::string DataPath() const;

        void ReloadLandscape() const;

    private:

        CommandObserver<Battler> gizmoCommandObserver { this, &Battler::HandleGizmoCommand };
        CommandObserver<Battler> fogDensityCommandObserver { this, &Battler::HandleFogDensityCommand };

        DisplayEventHandler    displayEventHandler{&HandleDisplayEvent};
        LocatorRegistration    locatorReg{PiTypeLocator::Spectator, "Spectator Camera"};

        static World *ConstructWorld(pchar name, void *cookie);

        static void HandleDisplayEvent(const DisplayEventData *eventData, void *data);

        void CreateScene();

        void CreateCommands();

        // Commands
        void HandleGizmoCommand(Command *, pchar);
        void HandleFogDensityCommand(Command *, pchar);

        // Network
        virtual void HandleConnectionEvent(ConnectionEvent, const NetworkAddress &, const void *) override;
        virtual void HandleGameEvent(GameEvent, const void *) override;
        virtual void HandlePlayerEvent(PlayerEvent, Player *, const void *) override;
        virtual void ReceiveMessage(Player *, const NetworkAddress &, const Message *) override;
        virtual Message *CreateMessage(PiTypeMessage::E, Decompressor &) const override;
    };
}
