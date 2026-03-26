#ifndef DRUSTVENA_MREZA_H
#define DRUSTVENA_MREZA_H

#include "graf.h"

class DrustvenaMreza : public Graf {
private:
    double verovatnoće[MAX_CVOROVA][MAX_CVOROVA]; // Verovatnoće između korisnika

public:
    DrustvenaMreza();
    void lajkujObjavu(const char* od, const char* do_);
    void pronadjiNajvecuKomponentu() const;
    void ispisiNajverovatnijiPut(const char* od, const char* do_) const;
    void pronadjiNajuticajnijegKorisnika() const;
    void azurirajVerovatnocu(int odIndeks, int doIndeks, double verovatnoća);
};

#endif

