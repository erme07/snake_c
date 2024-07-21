#ifndef MENU_H
#define MENU_H

//#include "consola.h"
#include "escenarios.h"
#include "estructuras.h"

#define COLSPANEL 22
#define ROWSPANEL 20

int menu();
int seleccionarEscenario();
void pintarMarco();
void imprimirLogo();
void borrarLogo();
void borrarMenu();
void imprimirGameOver();
void estadisticas(Serpiente*,int,int);

#endif //MENU_H