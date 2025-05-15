#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>

int shared_resource = 0;
std::shared_mutex s_mtx;

void reader(int id) {
    std::shared_lock<std::shared_mutex> lock(s_mtx); // Share
    std::cout << "Reader " << id << " reads: " << shared_resource << std::endl;
}

void writer() {
    std::unique_lock<std::shared_mutex> lock(s_mtx); // Khong Share
    shared_resource++;
    std::cout << "Writer updated resource to: " << shared_resource << std::endl;
}

int main() {
    std::thread writer1 = std::thread(writer);
    writer1.join();

    std::thread reader1 = std::thread(reader, 1);
    std::thread reader2 = std::thread(reader, 2);
    std::thread reader3 = std::thread(reader, 3);

    reader1.join();
    reader2.join();
    reader3.join();
    //Ở phần show ra sẽ thấy cout loạn -> 3 thread đang cùng làm việc

    return 0;
}