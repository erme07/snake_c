#ifndef COLISIONES_H
#define COLISIONES_H

#include <windows.h>
#include "estructuras.h"
#include "consola.h"

int colisionBola(Serpiente*,int[ROWS][COLS]);
int tiempoAnimacion(int);
void animacionColision(Serpiente*,int);
void encenderPortalHorizontal(void);
void encenderPortalVertical(void);
void apagarPortalHorizontal(void);
void apagarPortalVertical(void);
void teletransportar(Serpiente*);
void establecerMatriz(int,int[ROWS][COLS]);
BOOL colisionEscenarios(Serpiente*,int);
BOOL matrizColision(Coordenadas,int);
BOOL colisionSerpiente(Serpiente*);
BOOL colisionPortal(Coordenadas);
BOOL colisionCola(Coordenadas);

#endif //COLISIONES_H