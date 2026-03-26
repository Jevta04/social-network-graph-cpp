#include "drustvenamreza.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

DrustvenaMreza::DrustvenaMreza() {
    // Inicijalizacija verovatnoca na nulu
    for (int i = 0; i < MAX_CVOROVA; ++i) {
        for (int j = 0; j < MAX_CVOROVA; ++j) {
            verovatnoće[i][j] = 0.0;
        }
    }
}

void DrustvenaMreza::lajkujObjavu(const char* od, const char* do_) {
    int odIndeks = nadjiIndeksCvora(od);
    int doIndeks = nadjiIndeksCvora(do_);

    if (odIndeks == -1 || doIndeks == -1) {
        std::cerr << "Greska: Nevalidni korisnici.\n";
        return;
    }

    // Povecavamo verovatnocu za 0.1
    azurirajVerovatnocu(odIndeks, doIndeks, verovatnoće[odIndeks][doIndeks] + 0.1);
    std::cout << od << " je lajkovao/la objavu korisnika " << do_ << ".\n";
}

void DrustvenaMreza::azurirajVerovatnocu(int odIndeks, int doIndeks, double verovatnoca) {
    if (verovatnoca > 1.0) {
        verovatnoca = 1.0; // Maksimalna verovatnoca
    }
    verovatnoće[odIndeks][doIndeks] = verovatnoca;
    verovatnoće[doIndeks][odIndeks] = verovatnoca; // Obrnuta veza (simetricna)
}

void DrustvenaMreza::pronadjiNajvecuKomponentu() const {
    std::vector<bool> poseceni(MAX_CVOROVA, false);
    int najvećiBroj = 0;
    int indeksKomponente = -1;

    for (int i = 0; i < brojCvorova; ++i) {
        if (!poseceni[i]) {
            // BFS ili DFS za pretragu
            std::queue<int> q;
            q.push(i);
            poseceni[i] = true;
            int veličina = 1;

            while (!q.empty()) {
                int cvor = q.front();
                q.pop();

                for (int j = 0; j < brojCvorova; ++j) {
                    if (matrica[cvor][j] != 0 && !poseceni[j]) {
                        poseceni[j] = true;
                        q.push(j);
                        veličina++;
                    }
                }
            }

            if (veličina > najvećiBroj) {
                najvećiBroj = veličina;
                indeksKomponente = i;
            }
        }
    }

    std::cout << "Najveca komponenta ima " << najvećiBroj << " korisnika.\n";
}

void DrustvenaMreza::ispisiNajverovatnijiPut(const char* od, const char* do_) const {
    int odIndeks = nadjiIndeksCvora(od);
    int doIndeks = nadjiIndeksCvora(do_);

    if (odIndeks == -1 || doIndeks == -1) {
        std::cerr << "Greska: Nevalidni korisnici.\n";
        return;
    }

    std::vector<double> dist(brojCvorova, std::numeric_limits<double>::infinity());
    std::vector<int> prethodni(brojCvorova, -1);
    dist[odIndeks] = 0;

    // Dijkstra's algoritam
    for (int i = 0; i < brojCvorova - 1; ++i) {
        int minIndeks = -1;
        double minVrednost = std::numeric_limits<double>::infinity();

        for (int j = 0; j < brojCvorova; ++j) {
            if (dist[j] < minVrednost) {
                minVrednost = dist[j];
                minIndeks = j;
            }
        }

        for (int j = 0; j < brojCvorova; ++j) {
            if (matrica[minIndeks][j] != 0 && dist[minIndeks] + verovatnoće[minIndeks][j] < dist[j]) {
                dist[j] = dist[minIndeks] + verovatnoće[minIndeks][j];
                prethodni[j] = minIndeks;
            }
        }
    }

    // Ispisivanje puta
    std::cout << "Najverovatniji put od " << od << " do " << do_ << ":\n";
    std::vector<std::string> put;
    for (int na = doIndeks; na != -1; na = prethodni[na]) {
        put.push_back(cvorovi[na]);
    }

    std::reverse(put.begin(), put.end());

    for (size_t i = 0; i < put.size(); ++i) {
        std::cout << put[i];
        if (i < put.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}

void DrustvenaMreza::pronadjiNajuticajnijegKorisnika() const {
    double maxUticaj = 0.0;
    int indeksNajuticajnijeg = -1;

    for (int i = 0; i < brojCvorova; ++i) {
        double uticaj = 0.0;

        for (int j = 0; j < brojCvorova; ++j) {
            if (verovatnoće[i][j] > 0) {
                uticaj += verovatnoće[i][j];
            }
        }

        if (uticaj > maxUticaj) {
            maxUticaj = uticaj;
            indeksNajuticajnijeg = i;
        }
    }

    std::cout << "Korisnik sa najvecim uticajem: " << cvorovi[indeksNajuticajnijeg] << std::endl;
}
