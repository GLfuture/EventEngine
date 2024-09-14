#ifndef __GALAY_EVENTSCHEDULER_H__
#define __GALAY_EVENTSCHEDULER_H__
#include "Base.h"
#include "Coroutine.h"
#include "BlockWait.h"
#include <functional>
#include <list>
#include <string>
#include <memory>
#include <atomic>
#include <mutex>
#include <unordered_map>

#define MAX_EVENTS 1024
#if defined(__linux__)
#define USE_EPOLL
#endif

enum EventType
{
    kEventTypeRead,
    kEventTypeWrite,
};

class EventEngine;
class EventChain;

//如果事件 invalid 为 true，则释放内存，否则重新进入eventchain
class Event
{
public:
    virtual void HandleEvent(EventEngine* engine) = 0;
    virtual EventChain* GetEventChain() = 0;
    virtual void BelongTo(EventChain* chain) = 0;
};

class EventChain
{
public:
    virtual void AddEvent(Event* node) = 0;
    virtual bool HasEvent() = 0;
    virtual EventType GetEventType() = 0;
    virtual Event* NextEvent() = 0;
    virtual bool Invalid() = 0;
    virtual void SetInvalid(bool invalid = true) = 0;
    virtual GSocket GetBindSocket() = 0;
};


class OrderEventChain: public EventChain
{
public:
    OrderEventChain(GSocket sock);
    virtual void AddEvent(Event* node) override;
    virtual bool HasEvent() override;
    virtual Event* NextEvent() override;
    virtual EventType GetEventType() override;
    virtual bool Invalid() override;
    virtual void SetInvalid(bool invalid = true) override;
    virtual GSocket GetBindSocket() override;
    virtual ~OrderEventChain();
private:
    GSocket m_sock;
    bool m_invalid;
    std::mutex m_mutex;
    std::list<Event*> m_events;
};

class CoroutineEventChain: public EventChain
{
public:
    virtual void AddEvent(Event* node) override
    {

    }
    virtual bool HasEvent() override;
    virtual Event* NextEvent() override;
    virtual EventType GetEventType() override
    {
        return kEventTypeRead;
    }

    virtual bool Invalid() override;
    virtual void SetInvalid(bool invalid = true) override;
    virtual GSocket GetBindSocket() override;
private:
    std::mutex m_mutex;
};

class EventEngine
{
public:
    using ptr = std::shared_ptr<EventEngine>;
    virtual bool Loop(int timeout = -1) = 0;
    virtual bool IsRunning() = 0;
    virtual bool Stop() = 0;
    virtual std::string GetLastError() const = 0;
    virtual void AddActiveEvent(Event* event) = 0;
    virtual void NotifyActiveEvent() = 0;
    virtual int AddEventChain(EventChain* chain) = 0;
    virtual int ModifyEventChain(EventChain* chain) = 0;
    virtual int DelEventChain(EventChain* chain) = 0;
};

#if defined(USE_EPOLL)
//default ET mode
class EpollEventEngine: public EventEngine
{
public:
    EpollEventEngine(int max_events = MAX_EVENTS);
    virtual bool Loop(int timeout = -1) override;
    virtual bool IsRunning() override;
    virtual bool Stop() override;
    virtual std::string GetLastError() const override;
    virtual void AddActiveEvent(Event* event) override;
    virtual void NotifyActiveEvent() override;
    virtual int AddEventChain(EventChain* chain) override;
    virtual int ModifyEventChain(EventChain* chain) override;
    virtual int DelEventChain(EventChain* chain) override;
    virtual ~EpollEventEngine();
private:
    void ConvertToEpollEvent(struct epoll_event &ev, EventChain *chain);
private:
    int m_epfd;
    int m_event_num;
    std::string m_error;
    EventChain* m_event_chain;
    epoll_event *m_events;
    std::atomic_bool m_stop;
};
#elif defined(USE_SELECT)

#elif defined(__APPLE__)
#endif

class StopEvent: public Event
{
public:
    StopEvent(std::function<void(Event*, EventEngine*)>&& callback);
    virtual void BelongTo(EventChain* chain) override;
    virtual EventChain* GetEventChain() override;
    virtual void HandleEvent(EventEngine* engine) override;
    virtual ~StopEvent() = default; 
private:
    std::function<void(Event*, EventEngine*)> m_callback;
    EventChain* m_belong_chain;
};

class CoroutineEvent: public Event
{
public:
    CoroutineEvent(Coroutine* coroutine);
    virtual void BelongTo(EventChain* chain) override;
    virtual EventChain* GetEventChain() override;
    virtual void HandleEvent(EventEngine* engine) override;
    virtual ~CoroutineEvent() = default;
private:
    Coroutine* m_coroutine;
    EventChain* m_belong_chain;
};

class NetRecvEvent: public Event
{
public:

};

class EventScheduler
{
public:
    EventScheduler();
    bool Loop(int timeout = -1);
    bool Stop();
    std::string GetLastError();
    int AddEventChain(EventChain *chain);
    int DelEventChain(EventChain* chain);
    ~EventScheduler();
private:
    EventEngine::ptr m_engine;
};



#endif