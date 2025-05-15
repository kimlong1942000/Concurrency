#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void calculateSquare(std::promise<int> prom, int value) {
    std::this_thread::sleep_for(std::chrono::seconds(5));
    int result = value * value;
    prom.set_value(result);
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    int number = 10;
    std::thread t(calculateSquare, std::move(prom), number);

    // Chờ trong 3 giây, kiểm tra trạng thái của future
    std::chrono::milliseconds timeout(1000); // 3 giây
    if (fut.wait_for(timeout) == std::future_status::ready) {
        // Nếu đã sẵn sàng, lấy kết quả
        int result = fut.get();
        std::cout << "Result is ready: " << result << std::endl;
    } else {
        // Chưa sẵn sàng, có thể thực hiện các công việc khác
        std::cout << "Result not ready after 3 second, doing other work..." << std::endl;
        int result = fut.get();
        std::cout << "Now result is: " << result << std::endl;
    }

    t.join();
    return 0;
}