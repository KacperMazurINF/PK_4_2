#pragma once
#include <regex>
#include <iostream>

/*
Ktoś pozamieniał niektóre słowa z początku książki na ananasy!

Używając biblioteki <regex> usuń slowa "ananasa", "Ananasa", "ANANASA" z podanego tekstu.
*/

struct Zadanie1 {
	
	void result() {
		std::regex reg("ananasa|Ananasa|ANANASA");
		std::cout << std::regex_replace(text, reg, "GIT");
	}

	std::string text = "Przychodzisz do mojego domu w dzien slubu mojego Ananasa" 
						"i prosisz mnie o dokonanie ananasa, i mowisz - tu glos ananasa" 
						"stal sie szyderczym przedrzeznianiem - zaplace, ile Ananasa zechce." 
						"Nie, nie jestem obrazony, ale co ja zrobilem, ze mnie traktujesz tak bez ANANASA?";
};
