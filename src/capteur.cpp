#include "capteur.hpp"

Capteur::Capteur(int interruption) {
    if (interruption != CAPT_M1 && interruption != CAPT_M2)
        this->_pin = CAPT_M1; // Si le pin définit n'est pas valide, on suppose pin M1
    this->_pin_count = 0;
    this->_last_interrupt_timestamp = 0;
    this->_moteur_associe = nullptr;
}

bool Capteur::AttacherInterruption(void (*interrupt)(void)) {
    if (this->_moteur_associe == nullptr) return false;
    attachInterrupt(digitalPinToInterrupt(this->_pin), interrupt, RISING);
    return true;
}