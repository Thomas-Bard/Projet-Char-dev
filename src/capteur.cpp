#include "capteur.hpp"

Capteur::Capteur(int interruption) {
    if (interruption != CAPT_M1 && interruption != CAPT_M2)
        this->_pin = CAPT_M1; // Si le pin définit n'est pas valide, on suppose pin M1
    this->_pin_count = 0;
    this->_dernier_tour = 0;
    this->_moteur_associe = nullptr;
    if (this->_pin == CAPT_M1) {
        this->_pin_led_associee = DEL_1;
    } else this->_pin_led_associee = DEL_2;
    this->_etat_led = 0;
}

bool Capteur::AttacherInterruption(void (*interrupt)(void)) {
    if (this->_moteur_associe == nullptr) return false;
    attachInterrupt(digitalPinToInterrupt(this->_pin), interrupt, RISING);
    return true;
}

void Capteur::_FonctionInterruption(void) {
    size_t temps_actuel = millis();
    this->_pin_count++;
    if (this->_pin_count == NOMBRE_DENTS) {
        this->_moteur_associe->_last_speed = 1/(temps_actuel / 60000 - this->_dernier_tour / 60000);
        // L'opérateur "!" est l'opération logique "non", il inverse la valeur de ce qui le suit
        // Si la valeur qui suit vaut 1, il retourne 0, si elle vaut 0, il retourne 1
        this->_etat_led = !this->_etat_led;
        digitalWrite(this->_pin_led_associee, this->_etat_led);

        this->_dernier_tour = temps_actuel;
        this->_pin_count = 0;
    }
}
