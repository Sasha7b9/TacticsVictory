// 2021/11/25 19:49:29 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "System/Events.h"
#include "Utilities/PiMap.h"


using namespace Pi;


// Структура для сохранения подписанных
struct StoragerTarget : public MapElement<StoragerTarget>
{
    StoragerTarget(EventTarget *subscriber) : object(subscriber) {}
    EventTarget *object;

    typedef void *KeyType;

    KeyType GetKey() const
    {
        return (KeyType)this;
    }
};


typedef void (*FuncEvent)(EventTarget *, Event *);


static void FUpdate(EventTarget *obj, Event *event) { obj->HandleEventUpdate((EventUpdate *)event); }

static void FMessage(EventTarget *obj, Event *event) { obj->HandleEventMessage((EventMessage *)event); }

static void FRenderBegin(EventTarget *obj, Event *event) { obj->HandleEventRenderBegin((EventRenderBegin *)event); }

// Каждой карте соответствует одно событие и в ней хранятся цели, на него подписанные
static Pi::Map<StoragerTarget> targets[(int)Event::E::Count];


static FuncEvent funcs[(int)Event::E::Count] =
{
    FUpdate,
    FMessage,
    FRenderBegin
};


void Event::Subscribe(EventTarget *object)
{
    targets[(uint)type].Insert(new StoragerTarget(object));
}


void Event::UnSubscribe(EventTarget *object)
{
    for(StoragerTarget *obj : targets[(uint)type])
    {
        if(obj->object == object)
        {
            targets[(uint)type].Remove(obj);
            break;
        }
    }
}


void Event::Post()
{
    for(StoragerTarget *obj : targets[(int)type])
    {
        funcs[(int)type](obj->object, this);
    }
}


void Event::Post(EventTarget *target)
{
    funcs[(int)type](target, this);
}
