#include "graf.h"
#include <fstream>
#include <iostream>
#include <cstring>

// Konstruktor
Graf::Graf() : brojCvorova(0) {
    for (int i = 0; i < MAX_CVOROVA; ++i) {
        for (int j = 0; j < MAX_CVOROVA; ++j) {
            tezina[i][j] = 0.0;
        }
    }
}

// Destruktor
Graf::~Graf() {}

// Ucitavanje grafa iz fajla
void Graf::ucitajIzFajla(const char* imeFajla) {
    std::ifstream fajl(imeFajla);
    if (!fajl.is_open()) {
        std::cerr << "Greska: Nemoguce otvoriti fajl " << imeFajla << "\n";
        return;
    }

    int brojGrana;
    fajl >> brojCvorova >> brojGrana;

    for (int i = 0; i < brojCvorova; ++i) {
        fajl >> cvorovi[i];
    }

    for (int i = 0; i < brojGrana; ++i) {
        char od[21], do_[21];
        double tezina;
        fajl >> od >> do_ >> tezina;

        int odIndeks = nadjiIndeksCvora(od);
        int doIndeks = nadjiIndeksCvora(do_);

        if (odIndeks != -1 && doIndeks != -1) {
            this->tezina[odIndeks][doIndeks] = tezina;
        }
    }

    fajl.close();
}

// Ispis grafa
void Graf::prikaziGraf() const {
    std::cout << "Matrica susednosti:\n";
    for (int i = 0; i < brojCvorova; ++i) {
        for (int j = 0; j < brojCvorova; ++j) {
            std::cout << tezina[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Dodavanje cvora
void Graf::dodajCvor(const char* cvor) {
    if (brojCvorova >= MAX_CVOROVA) {
        std::cerr << "Greska: Graf je pun.\n";
        return;
    }
    if (nadjiIndeksCvora(cvor) != -1) {
        std::cerr << "Greska: Cvor vec postoji.\n";
        return;
    }

    cvorovi[brojCvorova] = cvor;
    ++brojCvorova;

    for (int i = 0; i < brojCvorova; ++i) {
        tezina[brojCvorova - 1][i] = 0.0;
        tezina[i][brojCvorova - 1] = 0.0;
    }
}

// Uklanjanje cvora
void Graf::ukloniCvor(const char* cvor) {
    int indeks = nadjiIndeksCvora(cvor);
    if (indeks == -1) {
        std::cerr << "Greska: Cvor nije pronadjen.\n";
        return;
    }

    for (int i = indeks; i < brojCvorova - 1; ++i) {
        cvorovi[i] = cvorovi[i + 1];
        for (int j = 0; j < brojCvorova; ++j) {
            tezina[i][j] = tezina[i + 1][j];
            tezina[j][i] = tezina[j][i + 1];
        }
    }

    --brojCvorova;
}

// Dodavanje grane
void Graf::dodajGranu(const char* od, const char* do_, double tezina) {
    int odIndeks = nadjiIndeksCvora(od);
    int doIndeks = nadjiIndeksCvora(do_);

    if (odIndeks == -1 || doIndeks == -1) {
        std::cerr << "Greska: Lose izabrani cvorovi.\n";
        return;
    }

    this->tezina[odIndeks][doIndeks] = tezina;
    std::cout << "Grana izmedju " << od << " i " << do_ << " sa tezinom " << tezina << " je uspesno dodata.\n";
}

// Uklanjanje grane
void Graf::ukloniGranu(const char* od, const char* do_) {
    int odIndeks = nadjiIndeksCvora(od);
    int doIndeks = nadjiIndeksCvora(do_);

    if (odIndeks == -1 || doIndeks == -1) {
        std::cerr << "Greska: Lose izabrani cvorovi.\n";
        return;
    }

    tezina[odIndeks][doIndeks] = 0;
    std::cout << "Grana izmedju " << od << " i " << do_ << " je uspesno uklonjena.\n";
}

// Ciscenje grafa
void Graf::ocistiGraf() {
    brojCvorova = 0;
    for (int i = 0; i < MAX_CVOROVA; ++i) {
        for (int j = 0; j < MAX_CVOROVA; ++j) {
            tezina[i][j] = 0;
        }
    }
}

// Pomocna funkcija za pronalazenje indeksa cvora
int Graf::nadjiIndeksCvora(const char* cvor) const {
    for (int i = 0; i < brojCvorova; ++i) {
        if (cvorovi[i] == cvor) {
            return i;  // Cvor je pronadjen, vracamo njegov indeks
        }
    }
    return -1;  // Cvor nije pronadjen
}

// Funkcionalnosti za drustvenu mrezu

void Graf::lajkujObjavu(const char* od, const char* do_) {
    int odIndeks = nadjiIndeksCvora(od);
    int doIndeks = nadjiIndeksCvora(do_);

    if (odIndeks == -1 || doIndeks == -1) {
        std::cerr << "Greska: Nevalidni korisnici.\n";
        return;
    }

    azurirajTezinu(odIndeks, doIndeks, tezina[odIndeks][doIndeks] + 0.1);
    std::cout << od << " je lajkovao/la objavu korisnika " << do_ << ".\n";
}

void Graf::azurirajTezinu(int odIndeks, int doIndeks, double tezina) {
    if (tezina > 1.0) {
        tezina = 1.0; // Maksimalna tezina
    }
    this->tezina[odIndeks][doIndeks] = tezina;
}

// preko conn-comp, dfs i 4 koraka u knjizi
void Graf::pronadjiNajvecuKomponentu() const {
    // 1. korak iz knjige
    std::vector<bool> poseceni(brojCvorova, false);
    int zavrsetak[MAX_CVOROVA];
    int zavrsetakIndex = 0;

    for (int i = 0; i < brojCvorova; ++i) {
        if (!poseceni[i]) {
            std::stack<int> stek;
            std::stack<int> zavrsavanje; // Stek za pracenje zavrsavanja
            stek.push(i);

            while (!stek.empty()) {
                int cvor = stek.top();
                if (!poseceni[cvor]) {
                    poseceni[cvor] = true;
                    zavrsavanje.push(cvor);

                    // susedni cvorovi na stek
                    for (int j = 0; j < brojCvorova; ++j) {
                        if (tezina[cvor][j] != 0 && !poseceni[j]) {
                            stek.push(j);
                        }
                    }
                }
                else {
                    stek.pop();
                    if (!zavrsavanje.empty() && zavrsavanje.top() == cvor) {
                        zavrsavanje.pop();
                        zavrsetak[zavrsetakIndex++] = cvor; // zavrsavanje != zavrsetak; zavrsetak tek kad je cvor poptpuno predjen
                    }
                }
            }
        }
    }

    // 2. korak iz knjige
    double tezinaTransponovana[MAX_CVOROVA][MAX_CVOROVA] = { 0 };
    for (int i = 0; i < brojCvorova; ++i) {
        for (int j = 0; j < brojCvorova; ++j) {
            tezinaTransponovana[j][i] = tezina[i][j];
        }
    }

    // 3. korak iz knjige
    std::fill(poseceni.begin(), poseceni.end(), false);
    int najvecaVelicina = 0;

    for (int i = zavrsetakIndex - 1; i >= 0; --i) {
        int cvor = zavrsetak[i];
        if (!poseceni[cvor]) {
            int velicina = 0;
            std::stack<int> stek;
            stek.push(cvor);

            while (!stek.empty()) {
                int trenutni = stek.top();
                stek.pop();

                if (!poseceni[trenutni]) {
                    poseceni[trenutni] = true;
                    velicina++;
                    // deo koji salje opet na proveru (4. korak)
                    for (int j = 0; j < brojCvorova; ++j) {
                        if (tezinaTransponovana[trenutni][j] != 0 && !poseceni[j]) {
                            stek.push(j);
                        }
                    }
                }
            }

            // najveca komponenta
            if (velicina > najvecaVelicina) {
                najvecaVelicina = velicina;
            }
        }
    }

    // Ispis
    std::cout << "Najveca povezana komponenta ima " << najvecaVelicina << " cvorova.\n";
}


void Graf::Dijkstra(int pocetniIndeks, std::vector<double>& dist, std::vector<int>& prethodni) const {
    dist.assign(brojCvorova, 0.0); // postavljamo udaljenosti na 0
    prethodni.assign(brojCvorova, -1); // prethodni cvorovi sa sa -1
    dist[pocetniIndeks] = 1.0; // udaljenost pocetnog cvora sa 1

    std::vector<bool> obradjeni(brojCvorova, false); // obradjeni cvor

    for (int i = 0; i < brojCvorova - 1; ++i) {
        // pronadji cvor sa najmanjom vrednoscu
        int minIndeks = -1;
        double minVrednost = -1.0;

        for (int j = 0; j < brojCvorova; ++j) {
            if (!obradjeni[j] && (minVrednost < dist[j])) {
                minVrednost = dist[j];
                minIndeks = j;
            }
        }

        if (minIndeks == -1) break;

        obradjeni[minIndeks] = true;

        // provera svih suseda i azuriranje vrednosti
        for (int j = 0; j < brojCvorova; ++j) {
            if (tezina[minIndeks][j] != 0 && !obradjeni[j]) {
                double novaDist = dist[minIndeks] * tezina[minIndeks][j];
                if (novaDist > dist[j]) {
                    dist[j] = novaDist;
                    prethodni[j] = minIndeks;
                }
            }
        }
    }
}


// Rekonstrukcija puta
void Graf::rekonstrukcijaPuta(int poslednjiCvor, const std::vector<int>& prethodni, const std::vector<std::string>& imenaCvorova) const {
    std::stack<int> s;
    s.push(poslednjiCvor);

    while (prethodni[s.top()] != -1) {
        s.push(prethodni[s.top()]);
    }

    std::cout << "Najverovatniji put:\n";

    // ispis prvog cvora
    int prethodniCvor = s.top();
    s.pop();
    std::cout << imenaCvorova[prethodniCvor];

    // ispis
    while (!s.empty()) {
        int trenutniCvor = s.top();
        s.pop();

        std::cout << " (" << tezina[prethodniCvor][trenutniCvor] << ") -> " << imenaCvorova[trenutniCvor];
        prethodniCvor = trenutniCvor;
    }

    std::cout << std::endl;
}

void Graf::ispisiNajverovatnijiPut(const char* od, const char* do_) const {
    int odIndeks = -1, doIndeks = -1;

    // Pronadji indekse za zadate cvorove
    for (int i = 0; i < brojCvorova; ++i) {
        if (cvorovi[i] == od) odIndeks = i;
        if (cvorovi[i] == do_) doIndeks = i;
    }

    if (odIndeks == -1 || doIndeks == -1) {
        std::cerr << "Greska: Nevalidni korisnici.\n";
        return;
    }

    std::vector<double> dist;
    std::vector<int> prethodni;

    // Dijkstra algoritam
    Dijkstra(odIndeks, dist, prethodni);

    // rekonstrukcija i ispis
    rekonstrukcijaPuta(doIndeks, prethodni, std::vector<std::string>(cvorovi, cvorovi + brojCvorova));
}


void Graf::pronadjiKtuOsobu(int k) const {
    if (k <= 0 || k > brojCvorova) {
        std::cerr << "Greska: Unos za k mora biti izmedju 1 i " << brojCvorova << ".\n";
        return;
    }

    // tezinaMod nije const
    double tezinaMod[MAX_CVOROVA][MAX_CVOROVA];
    for (int i = 0; i < brojCvorova; ++i) {
        for (int j = 0; j < brojCvorova; ++j) {
            tezinaMod[i][j] = tezina[i][j];
        }
    }

    // Floyd-Warshall algoritam
    for (int p = 0; p < brojCvorova; ++p) {
        for (int i = 0; i < brojCvorova; ++i) {
            for (int j = 0; j < brojCvorova; ++j) {
                tezinaMod[i][j] = std::max(tezinaMod[i][j], tezinaMod[i][p] * tezinaMod[p][j]);
            }
        }
    }

    double uticaji[MAX_CVOROVA] = { 0.0 };
    int indeksi[MAX_CVOROVA];

    // Izracunavanje uticaja
    for (int i = 0; i < brojCvorova; ++i) {
        indeksi[i] = i;
        for (int j = 0; j < brojCvorova; ++j) {
            if (i != j) {
                uticaji[j] += tezinaMod[i][j];
            }
        }
    }

    // Sortiranje uticaja i indeksa (opadajuce)
    for (int i = 0; i < brojCvorova - 1; ++i) {
        for (int j = i + 1; j < brojCvorova; ++j) {
            if (uticaji[i] < uticaji[j]) {
                double tempUticaj = uticaji[i];
                uticaji[i] = uticaji[j];
                uticaji[j] = tempUticaj;
                int tempIndeks = indeksi[i];
                indeksi[i] = indeksi[j];
                indeksi[j] = tempIndeks;
            }
        }
    }

    // Pronalazak k-te osobe
    int indeksKteOsobe = indeksi[k - 1];
    std::cout << "K-ta osoba sa najvecim uticajem: " << cvorovi[indeksKteOsobe] << ".";
}