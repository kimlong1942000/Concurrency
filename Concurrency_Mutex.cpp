#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Khai báo mutex để đồng bộ truy cập
std::mutex mtx;

void Thread1() {
    for (int i = 0; i < 5; ++i) {
        // Khóa mutex trước khi truy cập dữ liệu dùng chung
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Hello from Thread 1 - iteration " << i + 1 << std::endl;
        // Mutex tự động mở khóa khi lock_guard ra khỏi phạm vi
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Thread2() {
    for (int i = 0; i < 5; ++i) {
        // Khóa mutex trước khi truy cập dữ liệu dùng chung
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Hello from Thread 2 - iteration " << i + 1 << std::endl;
        // Mutex tự động mở khóa khi lock_guard ra khỏi phạm vi
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    // Tạo các luồng
    std::thread t1(Thread1);
    std::thread t2(Thread2);

    // Đợi các luồng kết thúc
    t1.join();
    t2.join();

    std::cout << "Concurrency with mutex demonstration complete." << std::endl;
    return 0;
}