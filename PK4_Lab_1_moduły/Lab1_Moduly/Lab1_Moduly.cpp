/*
Zadanie 1. Zadanie1.h jest plikiem nagłówkowym, którego zadeklarowaną funkcję implementuje plik Zadanie1.cpp. Zamiast pliku .h utwórz plik modułu oraz 
odpowiednio zmodyfikuj plik .cpp tak, aby działanie programu się nie zmieniło.

Zadanie 2. Zmodyfikuj plik Zadanie2.ixx tak, aby main miał dostęp do obydwu funkcji, korzystając tylko z jednej instrukcji export (dwóch, jeśli liczyć 
export module). Wywołaj obydwie funkcje w main.

Zadanie 3. Utwórz plik Zadanie3.ixx, który będzie podstawową jednostką interfejsu modułu. Następnie stwórz w osobnych plikach jego partycje:
-Partycja Pokoj, która zawiera strukturę o elementach określających szerokość i długość pokoju w metrach, oraz ilość okien. Do struktury odwoływać 
się ma funkcja pole_pokoju, która zwraca jego pole powierzchni oraz funkcja ile_okien, która wypisuje do konsoli liczbę okien. Wykorzystaj tylko jedną 
instrukcję export (dwie, jeśli liczyć export module).
-Partycja Dom, która zawiera strukturę o następujących elementach: wektor pokoi znajdujących się w domu oraz cena za metr kwadratowy. Funkcja cena_domu 
ma zwracać całkowitą cenę domu, to jest iloczyn pól powierzchni wszystkich pokoi przez cenę za metr kwadratowy.

Do pliku main zaimportuj moduł Zadanie3. Utwórz strukturę Pokoj o dowolnych elementach i wypisz do konsoli jego pole powierzchni oraz ilość okien. 
Następnie utwórz strukturę opisującą dom o co najmniej 3 pokojach. Wypisz do konsoli cenę domu.


*/

#include <iostream>
#include <vector>
import Zadanie1;
import Zadanie2;
import Zadanie3;

int main()
{
    hello();
    std::cout << Zad2::f_zewn() << std::endl;
    std::cout << Zad2::f_wewn() << std::endl;

    Pokoj pokoj1(20, 20, 2);
    Pokoj pokoj2(60, 20, 5);
    Pokoj pokoj3(50, 30, 9);
    std::vector<Pokoj> v;
    v.push_back(pokoj1);
    v.push_back(pokoj2);
    v.push_back(pokoj3);

    Dom dom(v, 10);
    std::cout << dom.cena_domu();




}

