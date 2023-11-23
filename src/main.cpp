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
void ExecutionProgramme(void);

void ChangementMode(void);

void setup() {
  INTERRUPTIONS::capteur_moteur_1.DefinirMoteur(&INTERRUPTIONS::moteur_1);
  INTERRUPTIONS::capteur_moteur_2.DefinirMoteur(&INTERRUPTIONS::moteur_2);
  // On attache les interruptions des capteurs
  INTERRUPTIONS::AttacherInterruptions();
  pinMode(DEL_INF, OUTPUT);
}

void loop() {
  // On regarde le mode de fonctionnement actuel, et effectuons les action appropriées
  switch (mode_fonctionnement) {
    case CONTROLE::Mode::MANUEL: {
      ControleManuel();
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
    // On a reçu quelque chose, une commande sûrement
    if (bluetooth.available()) {
      // On récupère la commande depuis le module bluetooth
      String commande = bluetooth.readString();

      // On compare la commande reçue avec les commandes existantes, pour savoir quelle action exécuter

      // Accélération du moteur numéro 1 au maximum en 1500ms
      if (commande == ACCELERATION_MOTEUR_1) {
        INTERRUPTIONS::moteur_1.AccelerationRampeBrute(255, 1500);
        bluetooth.flush();
        continue;
      }
      // Accélération du moteur numéro 2 au maximum en 1500ms
      if (commande == ACCELERATION_MOTEUR_2) {
        INTERRUPTIONS::moteur_2.AccelerationRampeBrute(255, 1500);
        bluetooth.flush();
        continue;
      }
      // Pas d'accélération pour éviter au char de tourner, sachant que l'accélération d'un moteur est bloquante
      if (commande == ACCELERATION_GLOBALE) {
        INTERRUPTIONS::moteur_1.SortieBrute(255);
        INTERRUPTIONS::moteur_2.SortieBrute(255);
        bluetooth.flush();
        continue;
      }
      // Pas de décélération pour éviter au char de tourner, sachant que la décélération d'un moteur est bloquante
      if (commande == DECELERATION_GLOBALE) {
        INTERRUPTIONS::moteur_1.SortieBrute(0);
        INTERRUPTIONS::moteur_2.SortieBrute(0);
        bluetooth.flush();
        continue;
      }
      // Décélération du moteur 1 au minimum en 1500ms
      if (commande == DECELERATION_MOTEUR_1) {
        INTERRUPTIONS::moteur_1.DecelerationRampe(0, 1500);
        bluetooth.flush();
        continue;
      }
      // Décélération du moteur 2 au minimum en 1500ms
      if (commande == DECELERATION_MOTEUR_2) {
        INTERRUPTIONS::moteur_2.DecelerationRampe(0, 1500);
        bluetooth.flush();
        continue;
      }
      // Changement de mode
      if (commande == CHANGER_MODE) {
        INTERRUPTIONS::moteur_1.SortieBrute(0);
        INTERRUPTIONS::moteur_2.SortieBrute(0);
        bluetooth.flush();
        ChangementMode();
        return;
      }
    }
  }
}

// Permet de changer de mode, contient tout le code nécessaire au changement de mode de pilotage de l'arduino
void ChangementMode(void) {
  bluetooth.println("== Entrez un mode de contrôle ==");
  bluetooth.println("Les modes valides sont le suivants :");
  bluetooth.println("MANUEL - Permet l'exécution du mode de pilotage manuel");
  bluetooth.println("PROGRAMME - Permet l'exécution d'un programme de ronde enregistré dans la mémoire");
  bluetooth.println("PROGRAMMATION - Permet l'ajout d'un nouveau programme de ronde");
  bluetooth.println("Entrez un mode :");
  // Tant que l'on ne reçoit rien, on ne fait rien
ATTENTE_COMMANDE:
  while (!bluetooth.available()) {
    ;;
  }
  // On récupère la commande depuis le module bluetooths
  String mode = bluetooth.readString();
  if (mode == COMMANDE_MODE_MANUEL) {
    mode_fonctionnement = CONTROLE::Mode::MANUEL;
    bluetooth.flush();
    return;
  }
  if (mode == COMMANDE_MODE_PROGRAMME) {
    mode_fonctionnement = CONTROLE::Mode::EXECUTION;
    bluetooth.flush();
    return;
  }
  bluetooth.flush();
  bluetooth.println("Mode non reconnu !");
  bluetooth.println("Retour au menu");
  // Instruction goto permet de traverser toute une partie du code pour revenir à l'endroit du label
  goto ATTENTE_COMMANDE;
}

void ExecutionProgramme(void) {
  while (!bluetooth.available()) {
    INTERRUPTIONS::moteur_1.SortieBrute(255);
    INTERRUPTIONS::moteur_2.SortieBrute(255);
    delay(1000);
    INTERRUPTIONS::moteur_2.DecelerationRampeBrute(100, 1500);
    INTERRUPTIONS::moteur_2.AccelerationRampeBrute(255, 1500);
    delay(1000);
  }
  ChangementMode();
}
