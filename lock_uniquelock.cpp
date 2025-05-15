#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void process() {
    std::unique_lock<std::mutex> lock(mtx);
    shared_data += 10;
    std::cout << "Shared data: " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    // có thể unlock thủ công
    lock.unlock();
}

int main() {
    std::thread t1(process);
    std::thread t2(process);
    t1.join();
    t2.join();
    return 0;
}