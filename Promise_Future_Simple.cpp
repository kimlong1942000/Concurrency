#include <iostream>
#include <thread>
#include <future>

// Hàm thực hiện tính toán và đặt kết quả vào promise
void calculateSquare(std::promise<int> prom, int value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    int result = value * value;
    prom.set_value(result);
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    int number = 66;

    std::thread t(calculateSquare, std::move(prom), number);

    // Chờ tối đa 1 giây
    auto status = fut.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::ready) {
        int result = fut.get();
        std::cout << "Main: Nhận được kết quả: " << result << "\n";
    } else {
        std::cout << "Main: Timeout! Chưa nhận được kết quả.\n";
    }

    t.join();

    return 0;
}