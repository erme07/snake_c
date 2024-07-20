#ifndef COLISIONES_H
#define COLISIONES_H

#include <windows.h>
#include "estructuras.h"
#include "consola.h"

BOOL colisionBola(Serpiente*, Bloque*);
BOOL colisionEscenarios(Serpiente*,int);
BOOL colisionSerpiente(Serpiente*);
BOOL colisionEscen1(Coordenadas);
BOOL colisionEscen2(Coordenadas);
BOOL colisionEscen3(Coordenadas);
BOOL colisionPortal(Serpiente*);
BOOL colisionPortalH(Serpiente*);
BOOL colisionPortalV(Serpiente*);
BOOL colisionColaH(Serpiente*);
BOOL colisionColaV(Serpiente*);
void matarSerpiente(Serpiente*,int);
void encenderPortalHorizontal();
void encenderPortalVertical();
void apagarPortalHorizontal();
void apagarPortalVertical();
void teletransportar(Serpiente*);
int detectarColisiones(Serpiente*,Bloque*,Bloque*,Bloque*,int);

#endif //COLISIONES_H