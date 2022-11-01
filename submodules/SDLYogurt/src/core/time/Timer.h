#pragma once
#include <chrono>

class Timer
{
public:
    Timer() = default;

    void start()
    {
        startPoint = clock.now();
        running = true;
    }
    void stop() { running = false; }

    [[nodiscard]] int getTickMilliseconds()
    {
        refresh();
        return static_cast<int> (
            std::chrono::duration_cast<std::chrono::milliseconds> (
                (currentPoint - startPoint))
                .count());
    }

    [[nodiscard]] int getTickSeconds()
    {
        refresh();
        return static_cast<int> (
            std::chrono::duration_cast<std::chrono::seconds> (
                (currentPoint - startPoint))
                .count());
    }

    [[nodiscard]] int getDiffMilliseconds()
    {
        const auto oldPoint = currentPoint;
        refresh();
        return static_cast<int> (
            std::chrono::duration_cast<std::chrono::milliseconds> (
                (currentPoint - oldPoint))
                .count());
    }

    [[nodiscard]] bool isRunning() const { return running; }

    void reset() { startPoint = clock.now(); }

private:
    void refresh() { currentPoint = clock.now(); }

    std::chrono::steady_clock clock;
    std::chrono::time_point<std::chrono::steady_clock> startPoint;
    std::chrono::time_point<std::chrono::steady_clock> currentPoint;
    bool running = false;
};
