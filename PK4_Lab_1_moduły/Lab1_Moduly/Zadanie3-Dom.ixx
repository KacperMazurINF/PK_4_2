module;
#include <vector>

export module Zadanie3:Dom;
import :Pokoj;

export struct Dom {
	std::vector<Pokoj> ilosc;
	int cena;

	Dom(std::vector<Pokoj> v, int c) {
		ilosc = v;
		cena = c;

	}

	int cena_domu() {
		int wartosc = 0;
		for (int i = 0; i < ilosc.size(); i++) {
			wartosc += ilosc[i].pole_pokoju() * cena;
		}
		return wartosc;
	}
};