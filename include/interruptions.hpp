#pragma once
#include "capteur.hpp"
#include "moteurs.hpp"

// Ce fichier regroupe toutes les variables relatives aux interruptions
// Il est contenu dans un espace de nom pour éviter les variables globales

namespace INTERRUPTIONS {
    Capteur capteur_moteur_1(CAPT_M1);
    Capteur capteur_moteur_2(CAPT_M2);

    Moteur moteur_1(TypeMoteur::MOTEUR_1);
    Moteur moteur_2(TypeMoteur::MOTEUR_2);

    void interruption_capteur_1(void) {
        capteur_moteur_1._FonctionInterruption();
    }
    void interruption_capteur_2(void) {
        capteur_moteur_2._FonctionInterruption();
    }

    void AttacherInterruptions(void) {
        capteur_moteur_1.AttacherInterruption(interruption_capteur_1);
        capteur_moteur_2.AttacherInterruption(interruption_capteur_2);
    }
}