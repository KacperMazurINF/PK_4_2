#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <string>


// Zadanie 1
// Za pomocą algorytmu transform, sort i biblioteki ranges wykonaj następujące operacje:
// - Zmień w wektorze "liczby" ujemne na dodatnie,
// - Podnieś do kwadratu liczby parzyste,
// - Posortuj dane w wektorze.
// Po wykonaniu zadania należy wyświetlić wektor.


void Zadanie1()
{
    std::vector<int> liczby{ -1, 8, 5, -3, 0, 2, 11, -13, -21 };
    std::ranges::transform(liczby, begin(liczby), [](int i) {return abs(i); });
    std::ranges::transform(liczby, begin(liczby), [](int i) {return i % 2 == 0 ? i*i : i; });
    std::ranges::sort(liczby, std::ranges::less{}, [](int i) {return i;});
    for (auto el : liczby) {
        std::cout << el << std::endl;
    }
    // Rozwiązanie
   
}


// Zadanie 2
// Dany jest wektor struktur Person, które zawierają imiona i nazwiska pewnej grupy ludzi.
// Za pomocą projekcji oraz funkcji sort posortuj tę listę:
// a) wg imion za pomocą składowej struktury,
// b) wg nazwisk za pomocą lambdy.
// Po wykonaniu zadania należy wyświetlić dane.

void Zadanie2()
{
    struct Person
    {
        std::string imie;
        std::string nazwisko;
    };

    std::vector<Person> people{
        { "Kamil",  "Kubina"   }, { "Dawid",  "Jeziorski" },
        { "Marcin", "Jesien"   }, { "Jerzy",  "Jezyk"     },
        { "Juan",   "Alla"     }, { "Alicja", "Czech"     }
    };

    // Rozwiązanie
    std::ranges::sort(people, std::ranges::less{}, & Person::imie);
    for (auto el : people) {
        std::cout << el.imie << " " << el.nazwisko << std::endl;
    }
    std::cout << std::endl;

    std::ranges::sort(people, std::ranges::less{}, [](auto const& p) {return p.nazwisko; });
    for (auto el : people) {
        std::cout << el.imie << " " << el.nazwisko << std::endl;
    }
    

}

// Zadanie 3
// Za pomocą kaskadowego połączenia widoków połącz wektory w jeden wektor,
// a następnie wykonaj odpowiednie operacje, aby wyświetlić kolejno liczby:
// 309 306 303 300
// Należy zwrócić uwagę na to, czym cechują się podane liczby,
// na ilość tych liczb oraz kolejność, w której zostają wypisywane.

void Zadanie3()
{
    std::vector<std::vector<int>> vector{ {300,301,302},{303,304,305},{306,307,308},{309,310,311} };

    //Rozwiązanie
    for (int i : vector | std::views::join | std::views::filter([](int i) {return i % 3 == 0; }) | std::views::reverse) {
        std::cout << i << std::endl;
   }
}


// Zadanie 4
// Osoby w różnych sklepach kupowały diody do projektu na SMIF.
// Dany jest wektor tupli, zawierający informacje o osobie, 
// ilości zakupionych diód oraz ile dana osoba zapłaciła.
// Za pomocą std::views znajdź średnią cenę za jedną diodę.

void Zadanie4()
{
    std::vector<std::tuple<std::string, int, double>> dane{
        {"Kamil", 20, 21.30},
        {"Jan",   13, 15.99},
        {"Pawel", 5,  6.49},
        {"Dawid", 11, 12.29},
        {"Marek", 23, 24.63},
        {"Karol", 16, 18.10}
    };

    //Rozwiązanie
    auto count = dane | std::views::transform([](std::tuple<std::string, int, double> x) {return get<1>(x); });
    auto price = dane | std::views::transform([](std::tuple<std::string, int, double> x) {return get<2>(x); });

    int c = 0;
    double p = 0;
    for (auto el : count) {
        c += el;
    }

    for (auto el : price) {
        p += el;
    }

    std::cout << p / c << std::endl;
}


// Zadanie 5
// Za pomocą std::views:
// - wygeneruj ciąg liczb od 0 do 99,
// - usuń liczby parzyste,
// - podnieś do 2. potęgi wszystkie liczby,
// - usuń liczby mniejsze od 1000,
// - wypisz rozwiązanie i sumę tych liczb.
bool nieparzysta(int i) {
    return i % 2 != 0;
}

bool cap(int i) {
    return i > 1000;
}

void Zadanie5()
{
    // Rozwiązanie
    for (int i : std::views::iota(0, 100) 
        | std::views::filter(nieparzysta) 
        | std::views::transform([](int n) {return pow(n, 2); })
        | std::views::filter(cap)) {
        std::cout << i << std::endl;
        
    }
}


int main()
{
    std::cout << "Zadanie 1:" << std::endl;
    Zadanie1();

    std::cout << "\n\nZadanie 2:" << std::endl;
    Zadanie2();

    std::cout << "\n\nZadanie 3:" << std::endl;
    Zadanie3();

    std::cout << "\n\nZadanie 4:" << std::endl;
    Zadanie4();

    std::cout << "\n\nZadanie 5:" << std::endl;
    Zadanie5();

    std::cout << "\n\n";
    system("pause");
    return 0;
}