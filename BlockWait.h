#ifndef __GALAY_BLOCKWAIT_H__
#define __GALAY_BLOCKWAIT_H__

#include <memory>
#include <atomic>
#include <condition_variable>

class BlockWaiter
{
public:
    using ptr = std::shared_ptr<BlockWaiter>;
    BlockWaiter(int num);
    bool Wait(int timeout = -1); //ms
    bool Decrease();
private:
    std::mutex m_mutex;
    std::atomic_int m_num;
    std::condition_variable m_cond;
};

#endif