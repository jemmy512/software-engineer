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


template<typename sizeT>
sizeT getRandom(sizeT maxSize, double probability = 0.5) {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto engine = std::default_random_engine(seed);
    auto distribution = std::binomial_distribution<sizeT>(maxSize, probability);

    return distribution(engine);
}

int main() {

    return 0;
}