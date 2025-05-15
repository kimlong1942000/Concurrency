#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int globalVar = 0; // Biến chia sẻ giữa các luồng

void threadA() {
    globalVar = 1900;
}
void threadB()
{
    globalVar = 1904;
}

int main() {
    // Tạo hai luồng chạy hàm 
    std::thread t1(threadB);
    std::thread t2(threadA);

    // Chờ cho hai luồng hoàn thành
    t1.join();
    t2.join();

    std::cout << "GlobalVar: " << globalVar << std::endl; //1900 ? 1904 ? or ....???

    return 0;
}