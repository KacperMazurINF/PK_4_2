#include <future>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>



// Zadanie 1

void task1(int x) {
    std::cout << "Watek 1: Rozpoczynam zadanie 1" << std::endl;
    std::cout << "Argumenty watku 1: " << x << std::endl;
    // Symulacja pracy przez 5 sekund
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Watek 1: Zakonczylem zadanie 1" << std::endl;
}

void task2(int x) {
    std::cout << "Watek 2: Rozpoczynam zadanie 2" << std::endl;
    std::cout << "Argumenty watku: " << x << std::endl;
    // Symulacja pracy przez 3 sekundy
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Watek 2: Zakonczylem zadanie 2" << std::endl;
}

int Zadanie1() {
    std::cout << "Glowny watek: Rozpoczynam program" << std::endl;

    // Tworzenie wątku 1 i wątku 2
    std::thread watek1(task1, 5);
    std::thread watek2(task2, 5);

    // Oczekiwanie na zakończenie pracy wątków
    watek1.join();
    watek2.join();

    std::cout << "Glowny watek: Zakonczono program" << std::endl;
    return 0;
}


// Zadanie 2

void math_operation(std::promise<int>&& result_promise) {
    std::cout << "second thread is working" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    int value = 55;
    std::cout << "second thread ended work" << std::endl;
    result_promise.set_value(value);
}

void Zadanie2() {
    std::cout << "main thread is working" << std::endl;

    std::promise<int> result_promise;
    std::future<int> result_future = result_promise.get_future();

    std::thread math_thread(math_operation, std::move(result_promise));

    std::cout << "Result of math operation: " << result_future.get() << std::endl;

    math_thread.join();
}



// Zadanie 3
int dodawanie(std::vector<int> liczby) {
    int suma = 0;
    for (int liczba : liczby) {
        suma += liczba;
    }
    std::cout << "zwraca sume wszystkich liczb" << std::endl;
    return suma;
}

int odejmowanie(std::vector<int> liczby) {
    int różnica = 0;
    for (int liczba : liczby) {
        różnica -= liczba;
    }
    std::cout << "zwraca roznice wszystkich liczb" << std::endl;
    return różnica;
}

void Zadanie3() {
    std::vector<int> liczby = { 1770, -3675, 4914, 4866, 1174, -4439, -4685, -4647, -4525, -1571, -3627, -1636, -2229, 1778, 2782, 2207, 1108, 1330, 1719, -2696, -4698, -4303, -2368, -2737, 4263, 2280, 1803, 3642, 1032, 2221, 1174, -4439, -4685, -4647 };


    std::future<int> wynikDodawania = std::async(std::launch::async, dodawanie, liczby);
    std::future<int> wynikOdejmowania = std::async(std::launch::async, odejmowanie, liczby);

    wynikOdejmowania.wait();
    wynikDodawania.wait();
    std::cout << wynikDodawania.get() << std::endl;
    std::cout << wynikOdejmowania.get() << std::endl;
}



// Zadanie 4
bool fileLoader() {
    size_t bytesLoaded = 0;
    while (bytesLoaded < 20000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bytesLoaded += 1000;
    }
    return true;
}

void Zadanie4() {

    std::future<bool> backgroundThread = std::async(std::launch::async,
        fileLoader);

    std::future_status status;
    std::cout << "Waiting for data";
    while (true) {
        std::cout << ".";
        status = backgroundThread.wait_for(std::chrono::milliseconds(500));
        if (status == std::future_status::ready) {
            std::cout << std::endl;
            std::cout << "Our data is ready..." << std::endl;
            break;
        }

    }

    std::cout << "Program is complete" << std::endl;
}


/// Zadanie 5

int main() {

    std::cout << "Zadanie 1: " << std::endl;
    Zadanie1();
    std::cout << std::endl;

    std::cout << "Zadanie 2: " << std::endl;
    Zadanie2();
    std::cout << std::endl;

    std::cout << "Zadanie 3: " << std::endl;
    Zadanie3();
    std::cout << std::endl;

    std::cout << "Zadanie 4: " << std::endl;
    Zadanie4();
    std::cout << std::endl;
}