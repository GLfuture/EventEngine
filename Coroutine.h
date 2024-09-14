#ifndef __GALAY_COROUTINE_H__
#define __GALAY_COROUTINE_H__

#include <any>
#include <memory>
#include <coroutine>

class Coroutine
{
public:
    Coroutine& operator=(Coroutine& other) = delete;
    Coroutine& operator=(const Coroutine& other) = delete;
public:
    class promise_type
    {
    public:
        inline int get_return_object_on_alloaction_failure() noexcept { return -1; }
        inline Coroutine get_return_object() noexcept {
            this->m_coroutine = new Coroutine(std::coroutine_handle<promise_type>::from_promise(*this));
            return *this->m_coroutine;
        }
        inline std::suspend_never initial_suspend() noexcept { return {}; }
        inline std::suspend_always yield_value() noexcept { return {}; }
        inline std::suspend_never final_suspend() noexcept { return {};  }
        inline void unhandled_exception() noexcept {}
        inline void return_void () noexcept {}
        inline Coroutine* GetCoroutine() { return m_coroutine; }
        inline ~promise_type() { delete m_coroutine; }
    private:
        Coroutine* m_coroutine;
    };
    Coroutine(std::coroutine_handle<promise_type> handle) noexcept;
    Coroutine(Coroutine&& other) noexcept;
    Coroutine(const Coroutine& other) noexcept;
    Coroutine& operator=(Coroutine&& other) noexcept;

    bool Done();
    void Notify();
    void SetContext(std::any context);
    std::any GetContext();
    ~Coroutine() = default;
private:
    std::shared_ptr<std::any> m_context;
    std::coroutine_handle<promise_type> m_handle;
};

class AsyncExecutor
{
public:
    using ptr = std::shared_ptr<AsyncExecutor>;
    //true will suspend, false will not
    virtual bool AsyncExcute(Coroutine* coroutine) = 0;
};

class Awaiter_int
{
public:
    Awaiter_int(AsyncExecutor::ptr executor, bool suspend = true);
    bool await_ready() const noexcept;
    //true will suspend, false will not
    bool await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) noexcept;
    int await_resume() const noexcept;
private:
    bool m_suspend;
    AsyncExecutor::ptr m_executor;
    std::coroutine_handle<Coroutine::promise_type> m_handle;
};

#endif