#include "BlockWait.h"

BlockWaiter::BlockWaiter(int num)
{
    this->m_num.store(num);
}

bool BlockWaiter::Wait(int timeout)
{
    std::unique_lock lock(this->m_mutex);
    if(m_num.load() <= 0) return true;
    if(timeout == -1)
    {
        m_cond.wait(lock, [this]() {
            return m_num.load() <= 0;
        });
    }
    else
    {
        m_cond.wait_for(lock, std::chrono::milliseconds(timeout), [this]() {
            return m_num.load() == 0;
        });
        if(m_num.load() != 0) return false;
    }
    return true;
}

bool BlockWaiter::Decrease()
{
    std::unique_lock lock(this->m_mutex);
    m_num.fetch_sub(1);
    if(m_num.load() == 0)
    {
        m_cond.notify_one();
    }
    return true;
}
