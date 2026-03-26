#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm> // za obrtanje redosleda u rekonstrukciji puta
#include <stack>

const int MAX_CVOROVA = 50; // maksimalan broj cvorova

class Graf {
protected:
    int brojCvorova;
    std::string cvorovi[MAX_CVOROVA]; // niz cvorova
    double tezina[MAX_CVOROVA][MAX_CVOROVA]; // matrica tezina (ili verovatnoca)

public:
    Graf(); // Konstruktor
    ~Graf(); // Destruktor

    // Formiranje i Manipulacija Grafom
    void ucitajIzFajla(const char* imeFajla);
    void prikaziGraf() const;
    void dodajCvor(const char* cvor);
    void ukloniCvor(const char* cvor);
    void dodajGranu(const char* od, const char* do_, double tezina);
    void ukloniGranu(const char* od, const char* do_);
    void ocistiGraf();




    // Pomocne funkcije
    int nadjiIndeksCvora(const char* cvor) const;
    // Dijkstra algoritam
    void Dijkstra(int pocetniIndeks, std::vector<double>& dist, std::vector<int>& prethodni) const;
    // Rekonstrukcija puta
    void rekonstrukcijaPuta(int poslednjiCvor, const std::vector<int>& prethodni, const std::vector<std::string>& imenaCvorova) const;
    // Interakcija sa drustvenom mrezom
    void lajkujObjavu(const char* od, const char* do_);
    void azurirajTezinu(int odIndeks, int doIndeks, double tezina);
    void pronadjiNajvecuKomponentu() const;
    void ispisiNajverovatnijiPut(const char* od, const char* do_) const;
    void pronadjiKtuOsobu(int k) const;
};

#endif
