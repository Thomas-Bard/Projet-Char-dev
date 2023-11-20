#include "constantes.hpp"
#include "moteurs.hpp"
#include "capteur.hpp"
// Interruptions contient la définition des moteurs. Voir espace de nom "Interruptions"
#include "interruptions.hpp"

// Les deux moteurs sont accessibles depuis l'espace de noms INTERRUPTIONS et sont définit comme
// moteur_1 et moteur_2
// On peut y accéder grâce à la syntaxe C++ suivante :
// INTERRUPTIONS::moteur_x
// Où x représente le moteur auquel on souhaite accéder

void setup() {
  // On attache les interruptions des capteurs
  INTERRUPTIONS::AttacherInterruptions();
  // On mets en place le module Bluetooth pour la communication
  SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
}

void loop() {
  
}
