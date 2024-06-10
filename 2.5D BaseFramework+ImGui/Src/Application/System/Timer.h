#pragma once
class Timer
{
public:
    Timer () noexcept : m_isRunning(false) {}
	~Timer() noexcept = default;

    void Start();

    void Stop();

    void Restart();

    void Resume();

    int ElapsedSeconds();

private:
    std::chrono::steady_clock::time_point m_startTime;
    std::chrono::steady_clock::time_point m_stopTime;
    bool m_isRunning;
};
