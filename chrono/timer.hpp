#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>

class Timer
{
  private:
    using clock = std::chrono::steady_clock;

    std::string name;
    std::chrono::time_point<clock> start;

  public:
    Timer(const std::string &name) : name(name), start(clock::now())
    {
    }

    auto durationInNanoseconds()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - start).count();
    }

    ~Timer()
    {
        std::chrono::duration<double, std::chrono::milliseconds::period> elapsed = clock::now() - start;
        std::cout << name << ":" << elapsed.count() << " ms.\n";
    }
};

#endif // TIMER_HPP
