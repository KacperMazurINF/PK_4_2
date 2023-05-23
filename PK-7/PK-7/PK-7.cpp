//zadania rozwiazane

#include <iostream>
#include <barrier>
#include <semaphore>
#include <thread>
#include <string>
#include<cstdlib>
#include <windows.h> //opcja dla windows
//#include <unistd.h> //opcja dla nie windows - nie testowana
using namespace std;

namespace zadanie1 {

    //ZADANIE 1
    //Twoim zadaniem jest dodac semaphory(binary_semaphore) tak aby wyswietlic napis:
    // ABABAB...

        //zaimplementuj semafory
    binary_semaphore printerSemaphoreA(1);
    binary_semaphore printerSemaphoreB(0);
    //
    void funcA() {
        int count = 10;
        while (count) {
            //miejsce na semafory
            printerSemaphoreA.acquire();
            //
            Sleep(100);
            cout << "A";
            count--;
            //miejsce na semafory
            printerSemaphoreB.release();
            //
        }
    }
    void funcB() {
        int count = 10;
        while (count) {
            //miesce na semafory
            printerSemaphoreB.acquire();
            //
            Sleep(100);
            cout << "B";
            count--;
            //miesce na semafory
            printerSemaphoreA.release();
            //
        }
    }
    void zad1() { //tu nic nie musisz zmieniac
        cout << "-------------\n";
        cout << "- Zadanie 1 -\n";
        cout << "-------------\n";
        cout << "wzor AB\n";

        thread tA(funcA);
        thread tB(funcB);
        tA.join();
        tB.join();
        cout << endl;
    }
}
namespace zadanie2 {

    //ZADANIE 2
    //Zadanie polega na tym samym co zadanie 1, tylko teraz uzyj klasy counting_semapohore i wyświetl:
    // AABC...
    // 
        //zaimplementuj semafory
    counting_semaphore<2> printerSemaphoreA(2);
    counting_semaphore<2> printerSemaphoreB(0);
    counting_semaphore<1> printerSemaphoreC(0);
    //

    void funcA() {
        int count = 10;
        while (count) {
            //miejsce na semafory
            printerSemaphoreA.acquire();
            //
            Sleep(100);
            cout << "A";
            count--;
            //miejsce na semafory
            printerSemaphoreB.release();
            //
        }
    }
    void funcB() {
        int count = 5;
        while (count) {
            //miesce na semafory
            printerSemaphoreB.acquire();
            printerSemaphoreB.acquire();
            //
            Sleep(100);
            cout << "B";
            count--;
            //miesce na semafory
            printerSemaphoreC.release();
            //
        }
    }
    void funcC() {
        int count = 5;
        while (count) {
            //miesce na semafory
            printerSemaphoreC.acquire();
            //
            Sleep(100);
            cout << "C";
            count--;
            //miesce na semafory
            printerSemaphoreA.release(2);
            //
        }
    }
    void zad2() { //tu nic nie musisz zmieniac
        cout << "-------------\n";
        cout << "- Zadanie 2 -\n";
        cout << "-------------\n";
        cout << "wzor AABC\n";

        thread tA(funcA);
        thread tB(funcB);
        thread tC(funcC);
        tA.join();
        tB.join();
        tC.join();
        cout << endl;
    }
}
//ZADANIE 3 
//uzywajac 3 semaforow, zrealizuj wyswietl w petli
//ABCAB

namespace zadanie3 {
    //zaimplementuj semafory
    counting_semaphore<2> printerSemaphoreA(1);
    counting_semaphore<2> printerSemaphoreB(0);
    counting_semaphore<3> printerSemaphoreC(0);
    //

    void funcA() {
        int count = 8;
        while (count) {
            //miejsce na semafory
            printerSemaphoreA.acquire();
            //
            Sleep(100);
            cout << "A";
            count--;
            //miejsce na semafory
            printerSemaphoreB.release();
            //
        }
    }
    void funcB() {
        int count = 8;
        while (count) {
            //miesce na semafory
            printerSemaphoreB.acquire();
            //
            Sleep(100);
            cout << "B";
            count--;
            //miesce na semafory
            printerSemaphoreC.release();
            //
        }
    }
    void funcC() {
        int count = 4;
        while (count) {
            //miesce na semafory
            printerSemaphoreC.acquire();
            //
            Sleep(100);
            cout << "C";
            count--;
            //miesce na semafory
            printerSemaphoreA.release();
            printerSemaphoreC.acquire();
            printerSemaphoreA.release();
            //
        }
    }
    void zad3() { //tu nic nie musisz zmieniac
        cout << "-------------\n";
        cout << "- Zadanie 3 -\n";
        cout << "-------------\n";
        cout << "wzor ABCAB\n";
        thread tA(funcA);
        thread tB(funcB);
        thread tC(funcC);
        tA.join();
        tB.join();
        tC.join();
        cout << endl;
    }
}

namespace zadanie4 {
    //Zadanie 4
    //spotkanie tajnych agentow odbywa sie gdy wszyscy pojawia sie w mijscu spotkania,
    //wtedy wymieniaja sie informacjami i ruszaja na kolejna misje
    //twoim zadaniem jest tak uzyc barier aby wszyscy 4 agenci czekali na siebie w bazie
    //zmieniaj tylko metody spotkanie oraz informacja_o_smierci


    //tutaj zaimplementuj barriery
    barrier iloscAgentow(4);
    //

    void spotkanie() {
        //tutaj umieszczaj kod
        iloscAgentow.arrive_and_wait();
        //
        cout << "wymiana informacji...\n";
        Sleep(5000);
        cout << "Wymiana informacji zakonczona\n";
    }
    void misjaAgent1() {
        bool zyje = true;
        while (zyje) {
            ;
            Sleep(1000); //czas trwania misji

            cout << "agent1 dotarl na spotkanie\n";
            spotkanie();
        }
    }
    void misjaAgent2() {
        bool zyje = true;
        while (zyje) {
            ;
            Sleep(5000); //czas trwania misji

            cout << "agent2 dotarl na spotkanie\n";
            spotkanie();
        }
    }
    void misjaAgent3() {
        bool zyje = true;
        while (zyje) {
            ;
            Sleep(2000); //czas trwania misji

            cout << "agent3 dotarl na spotkanie\n";
            spotkanie();
        }
    } void misjaAgent4() {
        bool zyje = true;
        while (zyje) {
            ;
            Sleep(4000); //czas trwania misji

            cout << "agent4 dotarl na spotkanie\n";
            spotkanie();
        }
    }
    void zad4() {
        cout << "-------------\n";
        cout << "- Zadanie 4 -\n";
        cout << "-------------\n";
        thread a1(misjaAgent1);
        thread a2(misjaAgent2);
        thread a3(misjaAgent3);
        thread a4(misjaAgent4);
        a1.join();
        a2.join();
        a3.join();
        a4.join();
    }
}


int main()
{
    zadanie1::zad1();
    zadanie2::zad2();
    zadanie3::zad3();
    zadanie4::zad4();
}

