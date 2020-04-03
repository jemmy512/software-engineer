#include <iostream>
#include <chrono>

inline constexpr long long Zero = 0;

class LeakyBucket {
public:
    LeakyBucket(long long cap, long long rt) : capacity(rt), rate(rt) { }

    bool grant() {
        auto now = std::chrono::system_clock::now();
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

class TokenBucket {
public:
    TokenBucket(long long cap, long long rt) : capacity(rt), rate(rt) { }

    bool grant() {
        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - timeStamp);
        token = std::min(capacity, token - duration.count() * rate);
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

int main() {

    return 0;
}