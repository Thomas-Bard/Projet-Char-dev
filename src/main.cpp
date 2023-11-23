#include "constantes.hpp"
#include "moteurs.hpp"
#include "capteur.hpp"
// Interruptions contient la définition des moteurs. Voir espace de nom "Interruptions"
#include "interruptions.hpp"
// Contient différents types et structures utiles au fonctionnement du programme
#include "divers.hpp"

// Les deux moteurs sont accessibles depuis l'espace de noms INTERRUPTIONS et sont définit comme
// moteur_1 et moteur_2
// On peut y accéder grâce à la syntaxe C++ suivante :
// INTERRUPTIONS::moteur_x
// Où x représente le moteur auquel on souhaite accéder

// On mets en place le module Bluetooth pour la communication
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);

// Mode de fonctionnement du char suivant l'énumération :
//  - MANUEL : Pilotage Manuel (via bluetooth)
//  - PROGRAMMATION : Programmation de différents programmes de ronde
//  - EXECUTION : Exécution d'un programme de ronde
CONTROLE::Mode mode_fonctionnement = CONTROLE::Mode::MANUEL;

void ControleManuel(void);
void InterfaceProgrammation(void);
void ExecutionProgramme(void);

void setup() {
  // On attache les interruptions des capteurs
  INTERRUPTIONS::AttacherInterruptions();
  pinMode(DEL_INF, OUTPUT);
}

void loop() {
  // Tant que quelque chose est disponible sur la mémoire tampon du module bluetooth
  switch (mode_fonctionnement) {
    case CONTROLE::Mode::MANUEL: {
      ControleManuel();
      break;
    }
    case CONTROLE::Mode::PROGRAMMATION: {
      InterfaceProgrammation();
      break;
    }
    case CONTROLE::Mode::EXECUTION: {
      ExecutionProgramme();
      break;
    }
    default:
      break;
  }

}

// Code à exécuter lorsque le char est en contrôle manuel depuis le module Bluetooth
void ControleManuel(void) {
  // On allume la DEL d'information pour préciser le mode manuel
  digitalWrite(DEL_INF, 1);
  bluetooth.println("Mode manuel active !");
  // On arrête les deux moteurs au cas où ils étaient précédemment allumés
  INTERRUPTIONS::moteur_1.SortieBrute(0);
  INTERRUPTIONS::moteur_2.SortieBrute(0);
  // On rentre dans une boucle infinie où on attends une commande depuis le module bluetooth
  while (true) {
    // On a reçu quelque chose une commande
    if (bluetooth.available()) {
      String commande = bluetooth.readString();
      if (commande == ACCELERATION_MOTEUR_1) {
        INTERRUPTIONS::moteur_1.AccelerationRampeBrute(255, 1500);
        bluetooth.flush();
        continue;
      }
      if (commande == ACCELERATION_MOTEUR_2) {
        INTERRUPTIONS::moteur_2.AccelerationRampeBrute(255, 1500);
        bluetooth.flush();
        continue;
      }
      if (commande == ACCELERATION_GLOBALE) {
        INTERRUPTIONS::moteur_1.SortieBrute(255);
        INTERRUPTIONS::moteur_2.SortieBrute(255);
      }
    }
  }
}