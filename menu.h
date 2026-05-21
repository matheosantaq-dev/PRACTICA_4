#ifndef MENU_H
#define MENU_H

#include "Red.h"

//funcion principal del menu
void iniciarMenu(Red& red);
void inicializarRed(Red& red);
//opciones
void opcionAgregarEnrutador(Red& red);
void opcionConectar(Red& red);
void opcionEliminarConexion(Red& red);
void opcionEliminarEnrutador(Red& red);
void opcionVerCamino(Red& red);

#endif
