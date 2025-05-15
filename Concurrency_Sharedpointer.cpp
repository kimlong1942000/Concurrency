#include <iostream>
#include <thread>
#include <memory>
#include <chrono>

class Worker {
public:
    Worker(int id) : id_(id) {
        std::cout << "Worker " << id_ << " tạo\n";
    }
    ~Worker() {
        std::cout << "Worker " << id_ << " hủy\n";
    }
    void doWork() {
        std::cout << "Worker " << id_ << " đang làm việc\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "Worker " << id_ << " hoàn thành công việc\n";
    }
private:
    int id_;
};

void threadFunction(std::shared_ptr<Worker> worker) {
    worker->doWork();
}

int main() {
    // Tạo đối tượng Worker và quản lý bằng shared_ptr
    auto workerPtr = std::make_shared<Worker>(1);

    // Tạo 3 luồng riêng biệt, mỗi luồng dùng chung shared_ptr
    std::thread t1(threadFunction, workerPtr);
    std::thread t2(threadFunction, workerPtr);
    std::thread t3(threadFunction, workerPtr);

    t1.join();
    t2.join();
    t3.join();

    // Sau khi các luồng kết thúc, shared_ptr tự động giải phóng nếu không còn tham chiếu
    return 0;
}