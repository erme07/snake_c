#ifndef MENU_H
#define MENU_H

#include "escenarios.h"
#include "estructuras.h"

#define COLSPANEL 22
#define ROWSPANEL 20

int menu(void);
int seleccionarEscenario(void);
int menuGameOver(void);
void pintarMarco(void);
void imprimirLogo(void);
void borrarLogo(void);
void borrarMenu(void);
void imprimirGameOver(void);
void estadisticas(Serpiente*,int,int,BOOL);


#endif //MENU_H