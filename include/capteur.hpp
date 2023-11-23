#pragma once
#include "constantes.hpp"
#include "moteurs.hpp"

class Capteur
{
private:
    int _pin;
    size_t _dernier_tour;
    int _pin_count;
    Moteur* _moteur_associe;
    int _pin_led_associee;
    bool _etat_led;
public:
    void _FonctionInterruption(void);
    Capteur(int);
    void DefinirMoteur(Moteur* m) { this->_moteur_associe = m; }
    
    // Attache l'interruption.
    // @warning A appeler uniquement APRES avoir définit le moteur associé !!!
    bool AttacherInterruption(void (*interrupt)(void));
};
