#include "moteurs.hpp"

Moteur::Moteur(TypeMoteur type_moteur) {
    this->_type_moteur = type_moteur;
    
    switch (type_moteur)
    {
    case MOTEUR_1:
        this->_dc_pin = DIRECTION_CONTROL_M1;
        this->_pwm_pin = PWM_M1;
        break;
    case MOTEUR_2:
        this->_dc_pin = DIRECTION_CONTROL_M2;
        this->_pwm_pin = PWM_M2;
        break;
    default:                                            // Si le type n'est pas reconnu, on suppose M1 par défaut
        this->_dc_pin = DIRECTION_CONTROL_M1;
        this->_pwm_pin = PWM_M1;
        break;
        break;
    }
    pinMode(this->_dc_pin, OUTPUT);
    pinMode(this->_pwm_pin, OUTPUT);
    this->_valeur_sortie = 0;
    analogWrite(this->_pwm_pin, 0);
    digitalWrite(this->_dc_pin, 0);
}

bool Moteur::AccelerationRampe(float vitesse, int temps) {
    if (vitesse <= this->_last_speed) return false;
    
    size_t temps_initie = millis();
    size_t temps_fin = temps + temps_initie;
    
    while (this->_last_speed != vitesse && millis() != temps_fin && this->_valeur_sortie < 255) {
        this->_valeur_sortie++;
        analogWrite(this->_pwm_pin, this->_valeur_sortie);
        delay((vitesse - this->_last_speed)/(temps*1000));
    }
    return abs(vitesse-this->_last_speed) <= 0.1;
}

bool Moteur::DecelerationRampe(float vitesse, int temps) {
    if (vitesse >= this->_last_speed) return false;
    
    size_t temps_initie = millis();
    size_t temps_fin = temps + temps_initie;
    
    while (this->_last_speed != vitesse && millis() != temps_fin && this->_valeur_sortie < 255) {
        this->_valeur_sortie--;
        analogWrite(this->_pwm_pin, this->_valeur_sortie);
        delay((this->_last_speed-vitesse)/(temps*1000));
    }
    return abs(vitesse-this->_last_speed) <= 0.1;
}

void Moteur::SortieBrute(uint8_t valeur) {
    analogWrite(this->_pwm_pin, valeur);
}

bool Moteur::AccelerationRampeBrute(uint8_t valeur, int temps) {
    if (this->_valeur_sortie >= valeur) return false;
    size_t temps_actuel = millis();
    while (this->_valeur_sortie < valeur && temps_actuel + temps < millis()) {
        this->_valeur_sortie++;
        analogWrite(this->_pwm_pin, this->_valeur_sortie);
        delay(temps / valeur);
    }
    return this->_valeur_sortie == valeur;
}

bool Moteur::DecelerationRampeBrute(uint8_t valeur, int temps) {
    if (this->_valeur_sortie >= valeur) return false;
    size_t temps_actuel = millis();
    while (this->_valeur_sortie < valeur && temps_actuel + temps < millis() && this->_valeur_sortie != 0) {
        this->_valeur_sortie--;
        analogWrite(this->_pwm_pin, this->_valeur_sortie);
        delay(temps / valeur);
    }
    return this->_valeur_sortie == valeur;
}
