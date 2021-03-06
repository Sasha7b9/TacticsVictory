// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Utils/PeriodicTask_.h"


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

        // Возвращает путь к каталогу с данными игры (Data/TacticsVictory)
        std::string DataPath() const;

        ListPeriodicTask periodicTasks;

    private:

        static World *ConstructWorld(pchar name, void *cookie);

        virtual void ApplicationTask() override;

        // Эти задачи выполняются с периодичностью 40 мс
        void RunTasksAcross40ms();

        // Эти задачи выполняются с периодичностью 1000 мс
        void RunTasksAcross1000ms();

        // Network
        virtual void HandleConnectionEvent(ConnectionEvent, const NetworkAddress &, const void *) override;
        virtual void HandleGameEvent(GameEvent, const void *) override;
        virtual void HandlePlayerEvent(PlayerEvent, Player *, const void *) override;
        virtual void ReceiveMessage(Player *, const NetworkAddress &, const Message *) override;
        virtual Message *CreateMessage(PiTypeMessage::E, Decompressor &) const override;
    };
}
