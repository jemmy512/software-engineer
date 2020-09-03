#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

inline constexpr long long Zero = 0;

void time(const std::chrono::system_clock::time_point& timePoint) {
    auto timet = std::chrono::system_clock::to_time_t(timePoint);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&timet), "%Y-%m-%d %H:%M:%S");
    std::cout << ss.str() << "| ";
}

class LeakyBucket {
public:
    LeakyBucket(long long cap, long long rt) : capacity(rt), rate(rt) { }

    bool grant() {
        auto now = std::chrono::system_clock::now();
        time(now);
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - timeStamp);
        water = std::max(Zero, water - duration.count() * rate);
        timeStamp = std::chrono::system_clock::now();
        if (water + 1 < capacity) {
            ++water;

            return true;
        } else {
            return false;
        }
    }

private:
    std::chrono::system_clock::time_point timeStamp;
    long long capacity;
    long long rate;
    long long water;
};
/**
 * Because the outflow speed is constant, it can resist burst traffic,
 * achieve smoother current limiting, and do not allow traffic bursts. */


class TokenBucket {
public:
    TokenBucket(long long cap, long long rt) : capacity(rt), rate(rt) { }

    bool grant() {
        auto now = std::chrono::system_clock::now();
        time(now);
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - timeStamp);
        token = std::min(capacity, token + duration.count() * rate);
        timeStamp = std::chrono::system_clock::now();

        if (token < 1) {
            return false;
        } else {
            --token;

            return true;
        }
    }

private:
    std::chrono::system_clock::time_point timeStamp;
    long long capacity;
    long long rate;
    long long token = 0;
};
/**
 * 1. Can resist burst traffic, because the number of tokens in the bucket will not exceed the given maximum.
 * 2. A smoother current limit can be achieved, because the token is put in at a uniform speed.
 * 3. The token bucket algorithm allows a certain degree of traffic burst. (Compared to leaky bucket algorithm) */

int main() {
    LeakyBucket leaky(10, 10);
    for (auto i = 0; i < 100; ++i) {
        std::cout << i << ", " << (int)leaky.grant() << std::endl;
    }

    TokenBucket token(10, 10);
    for (auto i = 0; i < 100; ++i) {
        std::cout << i << ", " << (int)token.grant() << std::endl;
    }
    return 0;
}