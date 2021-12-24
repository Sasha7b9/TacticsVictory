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

        // Возвращает путь к каталогу с данными игры (Data/TacticsVictory)
        std::string DataPath() const;

        void ReloadLandscape() const;

    private:

        static World *ConstructWorld(pchar name, void *cookie);

        // Отложенные задачи
        List<DeferredTask> deferredTasks;

        // Commands
        CommandObserver<Battler> gizmoCommandObserver{this, &Battler::HandleGizmoCommand};
        CommandObserver<Battler> fogDensityCommandObserver{this, &Battler::HandleFogDensityCommand};
        CommandObserver<Battler> pingCommandObserver{this, &Battler::HandlePingCommand};

        void HandleGizmoCommand(Command *, pchar);
        void HandleFogDensityCommand(Command *, pchar);
        void HandlePingCommand(Command *, pchar);

        void CreateCommands();

        // Network
        virtual void HandleConnectionEvent(ConnectionEvent, const NetworkAddress &, const void *) override;
        virtual void HandleGameEvent(GameEvent, const void *) override;
        virtual void HandlePlayerEvent(PlayerEvent, Player *, const void *) override;
        virtual void ReceiveMessage(Player *, const NetworkAddress &, const Message *) override;
        virtual Message *CreateMessage(PiTypeMessage::E, Decompressor &) const override;
    };
}
