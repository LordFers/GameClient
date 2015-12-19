#include "Watch.h"

Watch::Watch()
{}

Watch::~Watch()
{}

void Watch::Start()
{
    this->start = std::chrono::system_clock::now();
}

float Watch::Lap()
{
    std::chrono::time_point<std::chrono::system_clock> lap;
    lap = std::chrono::system_clock::now();
    std::chrono::duration<float> elapsed_seconds = lap - this->start;
    return elapsed_seconds.count();
}

void Watch::Stop()
{
    this->end = std::chrono::system_clock::now();
}

float Watch::Elapsed()
{
    Stop();
    std::chrono::duration<double> elapsed_seconds = (this->end - this->start) * 1000;
    Start();
    return static_cast<float>(elapsed_seconds.count());
}