module;
#include <iostream>
#include <string>

export module Zadanie2;

export namespace Zad2 {

	std::string f_wewn() {
		return "Wywoluje funkcje wewnetrzna...";
	}

	export std::string f_zewn() {
		std::string s = f_wewn();
		s += " z poziomu funkcji zewnetrznej";
		return s;
	}

}