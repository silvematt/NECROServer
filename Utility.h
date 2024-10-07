#ifndef NECROSERVER_UTILITY_H
#define NECROSERVER_UTILITY_H

#include <string>
#include <ctime>

class Utility
{
public:
    static std::tm localtime_xp(std::time_t timer);
    static std::string time_stamp(const std::string& fmt = "%F %T");
};

inline std::tm Utility::localtime_xp(std::time_t timer)
{
    std::tm bt{};
#if defined(__unix__)
    localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&timer);
#endif
    return bt;
}

// "YYYY-MM-DD HH:MM:SS"
inline std::string Utility::time_stamp(const std::string& fmt)
{
    auto bt = localtime_xp(std::time(0));
    char buf[64];
    return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}

#endif
