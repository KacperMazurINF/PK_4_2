#pragma once
#include <regex>
#include <iostream>

/*
Przeglądając zlecone Ci zadania, natrafiasz na zagadkę:

Jest to coś, czego używasz każdego dnia, ale nie zwracasz na to uwagi.
Można to znaleźć w wielu miejscach, ale zwykle jest to niewidoczne dla oka.
Nawet pomimo tego że jest to niewidoczne, jest w stanie rozdzielić dwa słowa.
Odnaleźć to musisz wykorzystując na raz dwa z przydatnych znaków z biblioteki <regex>
Co to jest?
*/

struct Zadanie4 {
	
	void result() {
		std::regex reg("\\d|\\s");
		std::cout << std::regex_replace(zadanie, reg, "");
	} 

	std::string zadanie = "1113 p223431 37u71532374 s71  43374t7372  16 1 54y67 16722 73132 z 4 n 6 2a 8771 k";
};

