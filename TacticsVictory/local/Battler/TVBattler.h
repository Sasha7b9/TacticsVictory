// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Objects/World/CameraRTS.h"
#include "Graphics/Effects/SparkParticleSystem.h"
#include "PeriodicTasks.h"


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
        virtual ~Battler();

        static Battler *self;

        virtual void ApplicationTask() override;

        void HandleOnButtonQuit(Widget *widget, const WidgetEventData *eventData);

        // ?????????? ???? ? ???????? ? ??????? ???? (Data/TacticsVictory)
        std::string DataPath() const;

        void ReloadLandscape() const;

    private:

        static World *ConstructWorld(pchar name, void *cookie);

//        Creator<ParticleSystem>     particleSystemCreator {&CreateParticleSystem};
//        static ParticleSystem *CreateParticleSystem()

        // Commands
        CommandObserver<Battler> gizmoCommandObserver      {this, &Battler::HandleGizmoCommand};
        CommandObserver<Battler> fogDensityCommandObserver {this, &Battler::HandleFogDensityCommand};
        CommandObserver<Battler> pingCommandObserver       {this, &Battler::HandlePingCommand};
        CommandObserver<Battler> trafficCommandObserver    {this, &Battler::HandleTrafficCommand};
        CommandObserver<Battler> serverCommandObserver     {this, &Battler::HandleServerCommand};

        void HandleGizmoCommand(Command *, pchar);
        void HandleFogDensityCommand(Command *, pchar);
        void HandlePingCommand(Command *, pchar);
        void HandleTrafficCommand(Command *, pchar);
        void HandleServerCommand(Command *, pchar);

        void CreateCommands();

        // Network
        virtual void HandleConnectionEvent(ConnectionEvent, const NetworkAddress &, const void *) override;
        virtual void HandleGameEvent(GameEvent, const void *) override;
        virtual void HandlePlayerEvent(PlayerEvent, Player *, const void *) override;
        virtual void ReceiveMessage(Player *, const NetworkAddress &, const Message *) override;
        virtual Message *CreateMessage(PiTypeMessage::E, Decompressor &) const override;
    };
}
