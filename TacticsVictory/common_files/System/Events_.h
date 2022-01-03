// 2021/11/25 19:34:21 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Base/PiBase.h"


namespace Pi
{
    class EventTarget;

    class Event
    {
    public:

        enum class E
        {
            Update,
            Message,
            RenderBegin,
            Count
        };

        // Подписывает target на события своего типа
        void Subscribe(EventTarget *target);

        // Отписывает target от событий своего типа
        void UnSubscribe(EventTarget *target);

        // Посыалет себя всем подписчикам
        void Post();

        // Посылает сообщение конкретной цели
        void Post(EventTarget *target);

    protected:
        Event(E _type) : type(_type) {}

    private:
        E type;
    };


    class EventUpdate : public Event
    {
    public:
        EventUpdate(float _time = 0.0f) : Event(Event::E::Update), time(_time)  {}
        float time;
    };


    class EventMessage : public Event
    {
    public:
        EventMessage(pchar msg = nullptr) : Event(Event::E::Message), message(msg)  {}
        pchar message;
    };


    class EventRenderBegin : public Event
    {
    public:
        EventRenderBegin() : Event(Event::E::RenderBegin)  {}
    };

    // Могут быть подписаны на события
    class EventTarget
    {
    public:

        virtual ~EventTarget()  {}
        virtual void HandleEventUpdate(EventUpdate *)           {};
        virtual void HandleEventMessage(EventMessage *)         {};
        virtual void HandleEventRenderBegin(EventRenderBegin *) {};
    };
}
