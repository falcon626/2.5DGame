#include "timer.h"

void Timer::Start()
{
    if (!m_isRunning) {
        auto now = std::chrono::steady_clock::now();
        if (m_startTime != std::chrono::steady_clock::time_point()) m_startTime += (now - m_stopTime);
        else m_startTime = now;
        m_isRunning       = true;
    }
}

void Timer::Stop()
{
    if (m_isRunning) {
        m_stopTime = std::chrono::steady_clock::now();
        m_isRunning = false;
    }
}

void Timer::Restart()
{
    Stop();
    m_startTime = std::chrono::steady_clock::now();
    m_isRunning  = true;
}

void Timer::Resume()
{
    if (!m_isRunning) {
        m_startTime += (std::chrono::steady_clock::now() - m_stopTime);
        m_isRunning   = true;
    }
}

int Timer::ElapsedSeconds()
{
    std::chrono::steady_clock::time_point endTime = m_isRunning ? std::chrono::steady_clock::now() : m_stopTime;
    return std::chrono::duration_cast<std::chrono::seconds>(endTime - m_startTime).count();
}
