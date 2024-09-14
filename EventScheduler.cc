#include "EventScheduler.h"
#ifdef __linux__
#include <sys/epoll.h>
#include <sys/eventfd.h>
#endif
#include <string.h>
#include <spdlog/spdlog.h>

OrderEventChain::OrderEventChain(GSocket sock)
{
    this->m_invalid = false;
    this->m_sock = sock;
}

void OrderEventChain::AddEvent(Event *node)
{
    m_events.push_back(node);
    node->BelongTo(this);
}

bool OrderEventChain::HasEvent()
{
    return !m_events.empty();
}

Event *OrderEventChain::NextEvent()
{
    Event* event = m_events.front();
    m_events.pop_front();
    return event;
}

EventType OrderEventChain::GetEventType()
{
    return kEventTypeRead;
}


bool OrderEventChain::Invalid()
{
    return m_invalid;
}

void OrderEventChain::SetInvalid(bool invalid)
{
    m_invalid = invalid;
}

GSocket OrderEventChain::GetBindSocket()
{
    return m_sock;
}

OrderEventChain::~OrderEventChain()
{
    for(auto iter = m_events.begin(); iter != m_events.end(); ++iter)
    {
        delete *iter;
    }
    m_events.clear();
    close(m_sock);
}

EpollEventEngine::EpollEventEngine(int max_events)
{
    this->m_epfd = 0;
    this->m_event_chain = nullptr;
    this->m_event_num = max_events;
    this->m_events = new epoll_event[max_events];
    bzero(m_events, sizeof(epoll_event) * max_events);
    this->m_stop = true;
}

bool EpollEventEngine::Loop(int timeout)
{
    this->m_epfd = epoll_create(1);
    if(this->m_epfd < 0) {
        m_error = "epoll_create: ";
        m_error += strerror(errno);
        return false;
    }
    int event_sock = eventfd(0, EFD_CLOEXEC | EFD_SEMAPHORE | EFD_NONBLOCK);
    spdlog::debug("EpollEventEngine::Loop create eventfd: {}", event_sock);
    if(event_sock < 0) {
        m_error = "eventfd: ";
        m_error += strerror(errno);
        return false;
    }
    epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    this->m_event_chain = new OrderEventChain(event_sock);
    ev.data.ptr = this->m_event_chain;
    epoll_ctl(m_epfd, EPOLL_CTL_ADD, event_sock, &ev);
    bool initial = true;
    do
    {
        int nEvents;
        if(initial) {
            initial = false;
            this->m_stop = false;
            nEvents = epoll_wait(m_epfd, m_events, m_event_num, timeout);
        }else{
            nEvents = epoll_wait(m_epfd, m_events, m_event_num, timeout);
        }
        spdlog::debug("EpollEventEngine::Loop epoll_wait return: {}", nEvents);
        if(nEvents < 0) {
            spdlog::error("EpollEventEngine::Loop epoll_wait failed, error: {}", strerror(errno));
            continue;
        };
        for(int i = 0; i < nEvents; ++i)
        {
            EventChain* chain = (EventChain*)m_events[i].data.ptr;
            while(chain->HasEvent())
            {
                Event* event = chain->NextEvent();
                event->HandleEvent(this);
                delete event;
            }
            if (chain->Invalid()) {
                DelEventChain(chain);
                spdlog::debug("EpollEventEngine::Loop event chain invalid, delete it, sock: {}", chain->GetBindSocket());
                delete chain;
            }
            else {
                ModifyEventChain(chain);
            }
        }
    } while (!this->m_stop);
    spdlog::info("EpollEventEngine::Loop exit");
    return true;
}

bool EpollEventEngine::IsRunning()
{
    return !m_stop;
}

bool EpollEventEngine::Stop()
{
    if(this->m_stop.load() == false)
    {
        this->m_stop.store(true);
        return true;
    }
    return false;
}

std::string EpollEventEngine::GetLastError() const
{
    return m_error;
}

void EpollEventEngine::AddActiveEvent(Event* event)
{
    m_event_chain->AddEvent(event);
}

void EpollEventEngine::NotifyActiveEvent()
{
    if( eventfd_write(m_event_chain->GetBindSocket(), 1) == -1){
        spdlog::error("EventScheduler::Stop eventfd_write failed, error: {}", strerror(errno));
    };
}

int 
EpollEventEngine::AddEventChain(EventChain *chain)
{
    epoll_event event;
    ConvertToEpollEvent(event, chain);
    event.data.ptr = chain;
    int ret = epoll_ctl(m_epfd, EPOLL_CTL_ADD, chain->GetBindSocket(), &event);
    if( ret != 0 ){
        m_error = strerror(errno);
    }
    else {
        if (!m_error.empty()){
            m_error.clear();
        }
    }
    return ret;
}

int EpollEventEngine::ModifyEventChain(EventChain *chain)
{
    epoll_event event;
    event.data.ptr = chain;
    ConvertToEpollEvent(event, chain);
    return epoll_ctl(m_epfd, EPOLL_CTL_MOD, chain->GetBindSocket(), &event);
}

int 
EpollEventEngine::DelEventChain(EventChain *chain)
{
    epoll_event event;
    event.data.ptr = chain;
    return epoll_ctl(m_epfd, EPOLL_CTL_DEL, chain->GetBindSocket(), &event);
}

EpollEventEngine::~EpollEventEngine()
{
    if(m_epfd > 0) close(m_epfd);
    delete[] m_events;
}

void 
EpollEventEngine::ConvertToEpollEvent(epoll_event &ev, EventChain *chain)
{
    switch (chain->GetEventType())
    {
    case kEventTypeRead:
        ev.events = EPOLLIN | EPOLLET;
        break;
    case kEventTypeWrite:
        ev.events = EPOLLOUT | EPOLLET;
        break;
    default:
        break;
    }
}

StopEvent::StopEvent(std::function<void(Event*, EventEngine*)>&& callback)
{
    this->m_callback = callback;
    this->m_belong_chain = nullptr;
}

void StopEvent::BelongTo(EventChain *chain)
{
    this->m_belong_chain = chain;
}

EventChain *StopEvent::GetEventChain()
{
    return this->m_belong_chain;
}

void StopEvent::HandleEvent(EventEngine *engine)
{
    m_callback(this, engine);
}

CoroutineEvent::CoroutineEvent(Coroutine *coroutine)
{
    this->m_coroutine = coroutine;
    this->m_belong_chain = nullptr;
}

void CoroutineEvent::BelongTo(EventChain *chain)
{
    this->m_belong_chain = chain;
}

EventChain *CoroutineEvent::GetEventChain()
{
    return nullptr;
}

void CoroutineEvent::HandleEvent(EventEngine *engine)
{
    m_coroutine->Notify();
}

EventScheduler::EventScheduler()
{
#if defined(__linux__)
    m_engine = std::make_shared<EpollEventEngine>();
#endif
}

bool EventScheduler::Loop(int timeout)
{
    return m_engine->Loop(timeout);
}

bool EventScheduler::Stop()
{
    if(!m_engine->IsRunning()) return false;
    std::function<void(Event*,EventEngine*)> callback = [](Event* event, EventEngine* engine){
        eventfd_t val;
        eventfd_read(event->GetEventChain()->GetBindSocket(), &val);
        event->GetEventChain()->SetInvalid();
        engine->Stop();
    };
    StopEvent* event = new StopEvent(std::move(callback));
    m_engine->AddActiveEvent(event);
    m_engine->NotifyActiveEvent();
    return true;
}

std::string EventScheduler::GetLastError()
{
    return m_engine->GetLastError();
}

int EventScheduler::AddEventChain(EventChain* chain)
{
    return m_engine->AddEventChain(chain);
}

int EventScheduler::DelEventChain(EventChain* chain)
{
    return m_engine->DelEventChain(chain);
}

EventScheduler::~EventScheduler()
{
}