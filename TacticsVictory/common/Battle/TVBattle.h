// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


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

        // ¬озвращает путь к каталогу с данными игры (Data/TacticsVictory)
        std::string DataPath() const;

    private:

        LocatorRegistration    locatorReg{PiTypeLocator::Spectator, "Spectator Camera"};

        static World *ConstructWorld(pchar name, void *cookie);

        virtual void ApplicationTask() override;

        // Network
        virtual void HandleConnectionEvent(ConnectionEvent, const NetworkAddress &, const void *) override;
        virtual void HandleGameEvent(GameEvent, const void *) override;
        virtual void HandlePlayerEvent(PlayerEvent, Player *, const void *) override;
        virtual void ReceiveMessage(Player *, const NetworkAddress &, const Message *) override;
        virtual Message *CreateMessage(PiTypeMessage::E, Decompressor &) const override;
    };
}
