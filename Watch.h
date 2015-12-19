#pragma once
#include <chrono>
class Watch
{
public:
    Watch();

    void Start();
    float Lap();
    void Stop();
    float Elapsed();
    ~Watch();

protected:
    std::chrono::time_point<std::chrono::system_clock> start, end;
};

