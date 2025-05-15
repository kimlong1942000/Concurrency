#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutexA;
std::mutex mutexB;

void thread1() {
    std::lock_guard<std::mutex> lockA(mutexA);
    std::cout << "Thread 1: đã khóa mutexA\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::lock_guard<std::mutex> lockB(mutexB);
    std::cout << "Thread 1: đã khóa mutexB\n";

    // Thực hiện công việc
    std::cout << "Thread 1: hoàn thành công việc\n";//Không diễn ra
}

void thread2() {
    std::lock_guard<std::mutex> lockB(mutexB);
    std::cout << "Thread 2: đã khóa mutexB\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::lock_guard<std::mutex> lockA(mutexA);
    std::cout << "Thread 2: đã khóa mutexA\n";

    std::cout << "Thread 2: hoàn thành công việc\n";//Không diễn ra
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    std::cout << "Chương trình kết thúc\n"; //Không diễn ra

    return 0;
}