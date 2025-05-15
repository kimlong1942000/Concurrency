#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int shared_data = 0;

void worker() {
    std::lock_guard<std::mutex> lock(mtx); // tự động khóa
    shared_data++;
    std::cout << "Shared data: " << shared_data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // unlock tự động khi ra khỏi phạm vi
}

int main() {
    std::thread t1(worker);
    std::thread t2(worker);
    t1.join();
    t2.join();
    return 0;
}