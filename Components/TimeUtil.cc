/* Author: Jemmy
 * Date: 2020-03-25 */

#include <iostream>
#include <sstream>

#include <chrono>
#include <ctime>
#include <iomanip>

#include <random>

std::string getCurrentTime() {
    auto nowPoint = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(nowPoint);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S");

    return ss.str();
}


template<typename Size = int>
Size getRandom(Size min, Size max) {
    std::random_device dev;
    std::default_random_engine engine(dev());
    std::uniform_int_distribution<Size> distribution(min, max);

    return distribution(engine);
}

int main() {

    return 0;
}