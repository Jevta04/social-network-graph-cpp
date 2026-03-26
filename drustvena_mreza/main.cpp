#include "graf.h"

// Funkcija za prikaz menija; static
static void Meni() {
    std::cout << "\nMeni funkcija:\n";
    std::cout << "1 - Ucitaj graf iz fajla\n";
    std::cout << "2 - Prikazi graf\n";
    std::cout << "3 - Dodaj cvor\n";
    std::cout << "4 - Ukloni cvor\n";
    std::cout << "5 - Dodaj granu\n";
    std::cout << "6 - Ukloni granu\n";
    std::cout << "7 - Ocisti graf\n";
    std::cout << "8 - Lajkuj objavu\n";
    std::cout << "9 - Pronadji najvecu povezanu komponentu\n";
    std::cout << "10 - Ispisi najverovatniji put\n";
    std::cout << "11 - Pronadji k-tog najuticajnijeg korisnika\n";
    std::cout << "12 - Izlaz\n";
    std::cout << "Unesite broj opcije: ";
}

int main() {
    Graf graf;  // Kreiramo objekat klase Graf

    int izbor;
    
    do { // moze i while(true) sve jedno je
        Meni();  // Prikaz menija
        std::cin >> izbor;
        

        switch (izbor) {
            // Formiranje i Manipulacija Grafom
        case 1: {
            char imeFajla[100];
            std::cout << "Unesite ime fajla: ";
            std::cin >> imeFajla;
            graf.ucitajIzFajla(imeFajla);
            break;
        }
        case 2:
            graf.prikaziGraf();
            break;
        case 3: {
            char cvor[21];
            std::cout << "Unesite cvor za dodavanje u graf: ";
            std::cin >> cvor;
            graf.dodajCvor(cvor);
            break;
        }
        case 4: {
            char cvor[21];
            std::cout << "Unesite cvor za brisanje: ";
            std::cin >> cvor;
            graf.ukloniCvor(cvor);
            break;
        }
        case 5: { // Dodaj granu (input iz 3 puta)
            char odCvor[21], doCvor[21];
            double tezina;
            std::cout << "Unesite odCvor: ";
            std::cin >> odCvor;
            std::cout << "Unesite doCvor: ";
            std::cin >> doCvor;
            std::cout << "Unesite tezinu: ";
            std::cin >> tezina;
            graf.dodajGranu(odCvor, doCvor, tezina);
            break;
        }
        case 6: { // Ukloni granu (input iz 2 puta)
            char odCvor[21], doCvor[21];
            std::cout << "Unesite odCvor: ";
            std::cin >> odCvor;
            std::cout << "Unesite doCvor: ";
            std::cin >> doCvor;
            graf.ukloniGranu(odCvor, doCvor);
            break;
        }
        case 7:
            graf.ocistiGraf();
            std::cout << "Graf je ociscen.\n";
            break;

            // Interakcija sa drustvenom mrezom
        case 8: {
            char odCvor[21], doCvor[21];
            std::cout << "Unesite korisnika koji lajkuje objavu: ";
            std::cin >> odCvor;
            std::cout << "Unesite korisnika ciju objavu lajkujete: ";
            std::cin >> doCvor;
            graf.lajkujObjavu(odCvor, doCvor);
            break;
        }
        case 9:
            graf.pronadjiNajvecuKomponentu();
            break;
        case 10: {
            char odCvor[21], doCvor[21];
            std::cout << "Unesite pocetnog korisnika: ";
            std::cin >> odCvor;
            std::cout << "Unesite krajnjeg korisnika: ";
            std::cin >> doCvor;
            graf.ispisiNajverovatnijiPut(odCvor, doCvor);
            break;
        }
        case 11: {  // Najuticajniji korisnik
            int k;
            std::cout << "Unesite k: ";
            std::cin >> k;
            graf.pronadjiKtuOsobu(k);
            break;
        }
        case 12:
            std::cout << "Poz poz poz\n";
            break;
        default:
            //pogresan upis, upis stringa itd, koji ubacuje program u beskoncanu petlju
            if (std::cin.fail()) {
                std::cin.clear();  // Resetuje stanje cin-a
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ovaj red zaustavlja citanje inputa, sto omogucava prekid beskonacne petlje i ubacuje nas u novi red
                std::cout << "Pogresan Izbor. Izaberite izmedju 1 i 12.\n";
                continue;  // idemo u novu iteraciju
            }
        }
    } while (izbor != 12);

    return 0;
}
