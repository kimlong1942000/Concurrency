#include <iostream>
#include <thread>
#include <chrono>

void Thread1() {
    for(int i = 0; i < 5; ++i) {
        std::cout << "Thread 1" << i + 1 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Thread2() {
    for(int i = 0; i < 5; ++i) {
        std::cout << "Thread 2" << i + 1 << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    // Tạo các luồng chạy song song
    std::thread t1(Thread1);
    std::thread t2(Thread2);

    // Đợi các luồng kết thúc
    t1.join();
    t2.join();

    std::cout << "Concurrency demonstration complete." << std::endl;
    return 0;
}