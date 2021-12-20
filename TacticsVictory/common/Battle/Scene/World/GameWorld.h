﻿// 2021/12/20 15:59:17 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    class GameWorld : public World
    {
    public:

        GameWorld(pchar name);

        virtual ~GameWorld();

        static GameWorld *self;

        virtual WorldResult::B Preprocess() override;
    };
}
