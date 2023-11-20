#pragma once
#include "constantes.hpp"
#include "capteur.hpp"

typedef enum TypeMoteur {MOTEUR_1, MOTEUR_2};


// Fichier contenant une librairie simple pour intéragir avec les moteurs
class Moteur
{
public:
    Moteur(TypeMoteur, Capteur*);
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

    Capteur* PointeurCapteur(void) { return this->_capteur_associe; }


    // Envoie une valeur PWM brute au moteur.
    // @warning Provoque une accélération instantanée, de ce fait les chenilles peuvent patiner
    void SortieBrute(uint8_t valeur);

    friend class Capteur;
private:
    int _dc_pin;
    int _pwm_pin;
    Capteur* _capteur_associe;
    TypeMoteur _type_moteur;
    int _valeur_sortie;
protected:
    float _last_speed;
};

