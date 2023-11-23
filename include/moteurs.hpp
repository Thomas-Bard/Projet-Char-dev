#pragma once
#include "constantes.hpp"

enum TypeMoteur {MOTEUR_1, MOTEUR_2};


// Fichier contenant une librairie simple pour intéragir avec les moteurs
class Moteur
{
public:
    Moteur(TypeMoteur);
    // Procède à l'accélération jusqu'une certaine vitesse
    // @param vitesse Vitesse à atteindre
    // @param temps Temps d'accélération
    // @return true si la vitesse a pu être atteinte en temps voulu, false sinon
    bool AccelerationRampe(float, int);

    //Procède à une décélération jusqu'à une certaine vitesse
    // @param vitesse Vitesse à atteindre
    // @param temps Temps de décélération
    // @return true si la vitesse a pu être atteinte, false sinon
    bool DecelerationRampe(float, int);

    void DefinirControlDirection(bool etat = true) { digitalWrite(this->_dc_pin, 1); }

    // Envoie une valeur PWM brute au moteur.
    // @warning Provoque une accélération instantanée, de ce fait les chenilles peuvent patiner
    void SortieBrute(uint8_t valeur);

    // Accélère en un temps max donné le moteur, réglage par valeur brute PWM
    bool AccelerationRampeBrute(uint8_t valeur, int temps);

    // Décélère en un temps max donné le moteur, réglage par valeur brute PWM
    bool DecelerationRampeBrute(uint8_t valeur, int temps);
    friend class Capteur;
private:
    int _dc_pin;
    int _pwm_pin;
    TypeMoteur _type_moteur;
    int _valeur_sortie;
protected:
    float _last_speed;
};

