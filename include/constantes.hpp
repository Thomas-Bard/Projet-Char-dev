#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>


// Fichier contenant les macros et constantes ainsi que les fichiers includes nécessaires


// Pins relatifs aux moteurs

#define DIRECTION_CONTROL_M1 4
#define DIRECTION_CONTROL_M2 7

#define PWM_M1 5
#define PWM_M2 6

// Pins relatifs aux capteurs (interruptions)

#define CAPT_M1 2
#define CAPT_M2 3

// Pins relatifs à l'émetteur bluetooth (rx,tx)

#define BLUETOOTH_RX 10
#define BLUETOOTH_TX 11

// Pins relatifs aux DELs d'affichage de la vitesse
#define DEL_1 12
#define DEL_2 13
#define DEL_INF 9

// Constantes liées aux chenilles et roues
#define DIAMETRE_ROUE 57
#define NOMBRE_DENTS 18

// Commandes globales
#define CHANGER_MODE "CHG"

// Commandes mode manuel
#define ACCELERATION_MOTEUR_1 "M1A"
#define ACCELERATION_MOTEUR_2 "M2A"

#define DECELERATION_MOTEUR_1 "M1D"
#define DECELERATION_MOTEUR_2 "M2D"

#define ACCELERATION_GLOBALE "MGA"
#define DECELERATION_GLOBALE "MGD"


// Commandes pour le changement de mode
#define COMMANDE_MODE_MANUEL "MANUEL"
#define COMMANDE_MODE_PROGRAMME "PROGRAMME"
