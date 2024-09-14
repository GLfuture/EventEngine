
#include "Coroutine.h"

Coroutine::Coroutine(std::coroutine_handle<promise_type> handle) noexcept
{
    this->m_handle = handle;
    this->m_context = std::make_shared<std::any>();
}

Coroutine::Coroutine(Coroutine&& other) noexcept
{
    this->m_context.swap(other.m_context);
    other.m_context.reset();
    this->m_handle = other.m_handle;
    other.m_handle = nullptr;
}

Coroutine::Coroutine(const Coroutine& other) noexcept
{
    this->m_context = other.m_context;
    this->m_handle = other.m_handle;
}

Coroutine&
Coroutine::operator=(Coroutine&& other) noexcept
{
    this->m_context.swap(other.m_context);
    other.m_context.reset();
    this->m_handle = other.m_handle;
    other.m_handle = nullptr;
    return *this;
}

bool Coroutine::Done()
{
    return m_handle.done();
}

void Coroutine::Notify()
{
    return m_handle.resume();
}

void
Coroutine::SetContext(std::any context)
{
    *this->m_context = context;
}

std::any 
Coroutine::GetContext()
{
    return *this->m_context;
}

Awaiter_int::Awaiter_int(AsyncExecutor::ptr executor, bool suspend)
{
    this->m_executor = executor;
    this->m_suspend = suspend;
}

bool Awaiter_int::await_ready() const noexcept
{
    return !this->m_suspend;
}

bool Awaiter_int::await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) noexcept
{
    this->m_executor->AsyncExcute(handle.promise().GetCoroutine());
    return false;
}

int Awaiter_int::await_resume() const noexcept
{
    return std::any_cast<int>(this->m_handle.promise().GetCoroutine()->GetContext());
}
