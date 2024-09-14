#include "EventScheduler.h"
#include <thread>
#include <vector>
#include <iostream>
#include <spdlog/spdlog.h>

#define EVENT_SCHEDULER_NUM 4

int main()
{
    spdlog::set_level(spdlog::level::debug);
    std::vector<std::thread> threads;
    std::vector<EventScheduler> schedulers(EVENT_SCHEDULER_NUM);
    BlockWaiter::ptr waiter = std::make_shared<BlockWaiter>(EVENT_SCHEDULER_NUM);
    for(int i = 0 ; i < EVENT_SCHEDULER_NUM ; ++i)
    {
        threads.push_back(std::thread([i, &schedulers, waiter](){
            if(!schedulers[i].Loop()) {
                std::cout << schedulers[i].GetLastError() << std::endl;
            }
            std::cout << "thread " << i << " exit" << std::endl;
            waiter->Decrease();
        }));
        threads[i].detach();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    for(int i = 0 ; i < EVENT_SCHEDULER_NUM ; ++i) 
    {
        while(!schedulers[i].Stop()) {
            std::cout << "stop scheduler " << i << std::endl;
        }
    }
    if(!waiter->Wait(1000)) {
        std::cout << "wait timeout" << std::endl;
    };
    sleep(1);
    return 0;
}