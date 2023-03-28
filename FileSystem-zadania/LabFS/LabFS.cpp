#include <iostream>
#include <filesystem>


// Zadanie 1
// Dla podanej ścieżki "c:/programowanie/zadanie/plik.cpp" (podana 
// ścieżka nie musi istnieć)
// a) Wypisz wszystkie elementy ścieżki korzystając z iteratora
// b) Wypisz elementy ścieżki korzystając z odpowiedniej funkcji 
//  dla każdego elementu:
// - root path
// - relative path
// - parent path
// - filename
// - stem
// - extention
// Na koniec sprawdź czy istnieje plik o podanej ścieżce.

void zadanie1() {
    std::filesystem::path path("C:/programowanie/zadanie/plik.cpp");
    for (auto itr = path.begin(); itr != path.end(); itr++) {
        std::cout << *itr << std::endl;
     }
}



// Zadanie 2 
// Utwórz folder o nazwie "ZmianaNazwy" w dowolnej 
// lokalizacji innej niż folder projektu.  
// Następnie zmień jego nazwę na "ZmienionaNazwa" 
// korzystając z funkcji z biblioteki <filesystem>.
// Po każdej operacji sprawdź czy foldery 
// ("ZmianaNazwy" i "ZmienionaNazwa") istnieją.

//                !!!!!!UWAGA!!!!!!
// Jeśli folder już istnieje, funkcja nie będzie działać.
// W celu rozwiązania problemu należy usunąć utworzony folder.

void zadanie2() {
    std::filesystem::path source("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\ZmianaNazwy"); //<- dodać ścieżkę do folderu w którym
    // zostanie utworzony folder z zadania (najlepiej pusty)
    //Rozwiązanie
    std::filesystem::path source2("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\ZmienionaNazwa"); //<- dodać ścieżkę do folderu w którym

    std::cout << std::filesystem::exists(source) << std::endl;
    std::cout << std::filesystem::exists(source2) << std::endl;

    std::filesystem::create_directory(source);

    std::cout << std::filesystem::exists(source) << std::endl;
    std::cout << std::filesystem::exists(source) << std::endl;

    std::filesystem::rename(source, source2);
}

// Zadanie 3
// Do folderu utworzonego w zadaniu 2 dodaj podfolder o nazwie "NowyFolder".
// Skopiuj oba foldery pod lokalizację "./Foldery/Kopia". 
// Następnie usuń folder znajdujący się w miejscu początkowym.

void zadanie3() {

    std::filesystem::path source("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\ZmienionaNazwa"); //<- dodać sieżkę do folderu z zadania 2

    std::filesystem::create_directory("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\ZmienionaNazwa\\NowyFolder");

    std::filesystem::copy(source, "C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\LabFS\\Foldery\\Kopia", std::filesystem::copy_options::recursive);

    std::filesystem::remove_all(source);
    //rozwiązanie
}



// Zadanie 4
// Dla dołaczonego do projektu folderu o nazwie TestIteratora 
// porównaj różnicę w działaniu różnych typów iteratorów (zwykłego i rekurencyjnego)
// wypisując wszystkie jego pliki i podfoldery. 

void zadanie4() {
    //Rozwiązanie 
    std::filesystem::path source("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\LabFS\\TestIteratora");
    for (auto item : std::filesystem::directory_iterator(source)) {
        std::cout << item << std::endl;
    }
    for (auto item : std::filesystem::recursive_directory_iterator(source)) {
        std::cout << item << std::endl;
    }
}



// Zadanie 5 
// Dla dwóch plików z projektu (LabFS.cpp oraz LabFS.sln) porównaj 
// ich rozmiar, a następnie skopiuj plik o mniejszym rozmiarze
// pod lokalizaję "./Foldery/Mniejszy". Wypisz za pomocą iteratora
// nazwę oraz rozmiar skopiownego pliku. Następnie pliki z projektu 
// znajdujące się pod lokalizacją "./Foldery/Czas" (plik_graficzny.bmp 
// oraz plik_tekstowy.txt) porównaj pod kątem ostatniego czasu modyfikacji,
// a następnie plik o późniejszej dacie modyfikacji skopiuj pod lokalizację
// "./Foldery/Nowszy". Wypisz za pomocą iteratora nazwę oraz datę ostatniej 
// modyfikacji skopiowanego pliku 

//                !!!!!!UWAGA!!!!!!
// Jeśli folder już istnieje, funkcja nie będzie działać.
// W celu rozwiązania problemu należy usunąć utworzony folder.

void zadanie5() {
    std::filesystem::path plik1("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\LabFS\\LabFS.cpp");
    std::filesystem::path plik2("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\LabFS\\LabFS.sln");
    std::filesystem::path plik3("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\LabFS\\Foldery\\Mniejszy");
    std::filesystem::path plik4("C:\\Users\\SuperStudent.PL\\Desktop\\FileSystem-zadania\\LabFS\\Foldery\\Nowszy");

    if (std::filesystem::file_size(plik1) < std::filesystem::file_size(plik2)) {
        std::filesystem::copy(plik1, plik3);
    }
    else {
        std::filesystem::copy(plik2, plik3);
    }
    // Rozwiązanie

}


int main()
{
    std::cout << "Zadanie 1: " << std::endl;
    zadanie1();

    std::cout << "\n\nZadanie 2: " << std::endl;
    zadanie2();
   
    std::cout << "\n\nZadanie 3: " << std::endl;
    zadanie3();

    std::cout << "\n\nZadanie 4: " << std::endl;
    zadanie4();

    std::cout << "\n\nZadanie 5: " << std::endl;
    zadanie5();
}