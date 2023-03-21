#pragma once
#include <regex>
#include <iostream>
#include <string>

/*
Pracuj¹c w lokalnym sklepie spo¿ywczym zlecono Ci, zrobiæ inwentaryzacjê
wszystkich produktów sumuj¹c ich cenê. Znaj¹c jednak dzia³anie funkcji
regex_iterator() postanawiasz wykorzystaæ j¹ do zsumowania cen produktów.

Do wykonania zadania bêdzie Ci równie¿ potrzebna funkcja std::stod(),
s³u¿¹ca do zamiany typu string na typ double
*/

struct Zadanie5 {

	void result() {
        std::regex reg("\\d+\\.\\d+");
        std::sregex_iterator it(lista.begin(), lista.end(), reg);
        std::sregex_iterator end;

        double cena = 0;

        while (it != end) {
            std::smatch match = *it;
            cena += std::stod(match.str());
            it++;
        }

        std::cout << cena;
	}

	std::string lista =   "Kawa Lavazza Crema e Gusto - 28.50 z³"
                          "Mleko UHT 3,2% - 2.75 z³"
                          "Ser gouda tarty - 11.90 z³"
                          "Chleb pszenny razowy - 4.50 z³"
                          "Mas³o ekstra - 8.20 z³"
                          "Jajka klasy L - 0.50 z³/szt."
                          "Kie³basa wiejska z dzika - 23.70 z³"
                          "Jogurt naturalny 2,0% - 2.60 z³"
                          "Twaróg pó³t³usty - 6.90 z³"
                          "Kabanosy ostra wêdka - 15.50 z³"
                          "Piwo jasne pe³ne - 3.80 z³"
                          "Makaron spaghetti - 3.20 z³"
                          "Czekolada mleczna - 4.99 z³"
                          "Filet z ³ososia - 34.90 z³/kg"
                          "Szynka parmeñska - 99.99 z³/kg"
                          "Serek wiejski - 3.50 z³"
                          "Ketchup ³agodny - 4.80 z³"
                          "D¿em truskawkowy - 6.20 z³"
                          "Oliwa z oliwek extra virgin - 18.50 z³";
};

