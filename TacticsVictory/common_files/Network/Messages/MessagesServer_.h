// 2021/12/21 17:52:16 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    namespace PiTypeMessage
    {
        enum : E
        {
            CreateLandscape = BaseCount
        };
    }


    class MessageCreateLandscape : public Message
    {
        friend class Battle;
        friend class Battler;
    public:
        const String<> &GetNameLandscapeFile() const { return name_file; }

        virtual void Compress(Compressor &) const override;
        virtual bool Decompress(Decompressor &) override;
        virtual bool HandleMessage(Player *sender) const override;

        MessageCreateLandscape(pchar name_file);
        MessageCreateLandscape();
        String<> name_file;
    };
}
