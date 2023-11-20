#pragma once
#include "constantes.hpp"
#include "moteurs.hpp"


// Le constructeur de la classe attache l'interruption automatiquement !!
class Capteur
{
private:
    int _pin;
    size_t _last_interrupt_timestamp;
    int _pin_count;
    Moteur* _moteur_associe;
public:
    void _FonctionInterruption(void);
    Capteur(int);
    ~Capteur();
    inline void DefinirMoteur(Moteur* m) { this->_moteur_associe = m; }
    
    // Attache l'interruption.
    // @warning A appeler uniquement APRES avoir définit le moteur associé !!!
    bool AttacherInterruption(void (*interrupt)(void));
};
