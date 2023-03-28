module;
#include <iostream>
export module Zadanie3:Pokoj;

	
export struct Pokoj {
	int szerokosc;
	int dlugosc;
	int okna;

	Pokoj(int s, int d, int o) {
		szerokosc = s;
		dlugosc = d;
		okna = o;
	}

	int pole_pokoju () {
		return szerokosc * dlugosc;
	}

	void ile_okien() {
		std::cout << okna;
	}
};

