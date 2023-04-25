#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <queue>

/* ZADANIE 1
Napisz program, który uruchamia dwa wątki.
Jeden wątek wyświetla komunikat "Watek 1 dziala" co 1 sekundę,
drugi wątek wyświetla komunikat "Watek 2 dziala" co 2 sekundy.
Zastosuj obiekt klasy std::mutex,
aby uniknąć równoczesnego dostępu do standardowego wyjścia.
*/


//Tu możesz zadeklarować zmienne
std::mutex mtx;

void thread1Function() {
    for (int i = 0; i < 5; i++) {
        // Dodaj kod poniżej
        mtx.lock();
        std::cout << "Watek 1 dziala" << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void thread2Function() {
    for (int i = 0; i < 5; i++) {
        // Dodaj kod poniżej
        mtx.lock();
        std::cout << "Watek 2 dziala" << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void Zadanie1() {
    // Dodaj kod poniżej
    std::thread t1(thread1Function);
    std::thread t2(thread2Function);
    t1.join();
    t2.join();
}

/* ZADANIE 2
Napisz program, który uruchamia dwa wątki.
Jeden z wątków zwiększa wartość zmiennej "x" oraz zmniejsza wartość zmiennej "y" 2 miliony razy,
a drugi z wątków zmniejsza wartość zmiennej "x" oraz zwiększa wartość zmiennej "y" 3 miliony razy.
Zastosuj klasę std::atomic do uniknięcia problemów związanych z dostępem wielu wątków do tych samych zmiennych.
Po wykonaniu wszystkich operacji wypisz wartości zmiennych.
*/

//Tu możesz zadeklarować zmienne
std::atomic<int> x(0);
std::atomic<int> y(0);

void thread3Function() {
    // Dodaj kod poniżej
    for (int i = 0; i < 2000000; i++) {
        x++;
        y--;
    }
}

void thread4Function() {
    // Dodaj kod poniżej
    for (int i = 0; i < 3000000; i++) {
        x--;
        y++;
    }
}

void Zadanie2() {
    // Dodaj kod poniżej
    std::thread t1(thread3Function);
    std::thread t2(thread4Function);
    t1.join();
    t2.join();
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}

/* ZADANIE 3
Napisz program który w osobnym wątku obliczy silnie z 10.
Zmodyfikuj te funkcje tak, żeby informowała o rozpoczęciu,
zakończeniu pracy przez wątek i wypisywały przyjęty parametr.
Użyj klasy jthread.
*/

void factorial(int n)
{
    // Dodaj kod poniżej
    std::cout << "Start" << std::endl;
    int x = 1;
    for (int i = 1; i <= n; i++) {
        x *= i;
    }
    std::cout << x << std::endl;
}

void Zadanie3()
{
    // Dodaj kod poniżej
    std::jthread t(factorial, 10);
}

/* ZADANIE 4
Funkcja producer dodaje do kolejki liczby od 1 do 10,
a funkcja consumer je z niej pobiera i wyświetla na ekranie
Zsynchronizuj działania tak, by proces producer wyprodukował 5 pierwszych liczb,
a następnie proces consumer je wypisał i by ten proces powtórzył się ponownie
dla liczb od 6 do 10 gdy kolejka będzie pusta.
Skorzystaj z klasy condition_variable.
*/

//Tu możesz zadeklarować zmienne
std::mutex m;
std::condition_variable cv;
std::queue<int> q;

void producer()
{
    // Dodaj kod poniżej
    for (int i = 1; i <= 10; i++) {
        std::unique_lock<std::mutex> lock(m);
        while (q.size() >= 5) {
            cv.wait(lock);
        }

        q.push(i);
        std::cout << "P: " << i << std::endl;
        cv.notify_one();
    }
}

void consumer()
{
    // Dodaj kod poniżej    
    while (!q.empty()) {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty()) {
            cv.wait(lock);
        }

        int x = q.front();
        q.pop();
        std::cout << "C: " << x << std::endl;
        cv.notify_one();
    }
}

void Zadanie4()
{
    // Dodaj kod poniżej
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join();
    t2.join();
}

int main() {
    std::cout << "Zadanie 1:" << std::endl;
    Zadanie1();
    std::cout << std::endl;
    std::cout << "Zadanie 2:" << std::endl;
    Zadanie2();
    std::cout << std::endl;
    std::cout << "Zadanie 3:" << std::endl;
    Zadanie3();
    std::cout << std::endl;
    std::cout << "Zadanie 4:" << std::endl;
    Zadanie4();
    std::cout << std::endl;
}