#include <iostream>
#include <thread>
#include <future>

// Hàm thực hiện tính toán và đặt kết quả vào promise
void calculateSquare(std::promise<int> prom, int value) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    int result = value * value;
    // Gửi kết quả qua promise
    prom.set_value(result);
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    int number = 66;

    // Khởi tạo thread và truyền promise vào
    std::thread t(calculateSquare, std::move(prom), number);

    // Trong thread chính, chờ kết quả từ future
    std::cout << "Waiting for the result..." << std::endl;
    int square = fut.get(); 

    std::cout << "The square of " << number << " is " << square << std::endl;
    t.join();

    return 0;
}