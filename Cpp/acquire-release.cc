#include <atomic>
#include <thread>
#include <string>
#include <iostream>

// Ref: https://www.modernescpp.com/index.php/acquire-release-fences

namespace atomic {
std::atomic<std::string*> atoString;
std::atomic<int> atoInt = 10;
int rowInt = 10;

void release() {
    rowInt = 1;
    atoInt.store(1, std::memory_order_relaxed);
    atoString.store(new std::string("Hello world"), std::memory_order_release);
}

void acquire() {
    std::string* str;
    while (!(str = atoString.load(std::memory_order_acquire)));
    std::cout << "Atomic string:    " << *str << std::endl;
    std::cout << "Atomic int:       " << atoInt.load(std::memory_order_relaxed) << std::endl;
    std::cout << "Row    int:       " << rowInt << std::endl;
    delete str;
}

void main() {
    std::cout << " ****** atomic ********" << std::endl;

    std::thread acquireThread(acquire);
    std::thread releaseThread(release);

    releaseThread.join();
    acquireThread.join();
}
} // namespace atomic

namespace fence {
std::atomic<std::string*> atoString;
std::atomic<int> atoInt = 100;
int rowInt = 100;

void release() {
    rowInt = 0;
    atoInt.store(0, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    atoString.store(new std::string("Hi"), std::memory_order_relaxed);
}

void acquire() {
    std::string* str;
    while (!(str = atoString.load(std::memory_order_relaxed)));
    std::atomic_thread_fence(std::memory_order_acquire);
    std::cout << "Atomic string:    " << *str << std::endl;
    std::cout << "Atomic int:       " << atoInt.load(std::memory_order_relaxed) << std::endl;
    std::cout << "Row    int:       " << rowInt << std::endl;
    delete str;
}

void main() {
    std::cout << " ****** atomic thread fence ********" << std::endl;

    std::thread acquireThread(acquire);
    std::thread releaseThread(release);

    releaseThread.join();
    acquireThread.join();
}
} // namespace fence

int main() {
    atomic::main();
    fence::main();
}