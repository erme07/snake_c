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

#endif //COLISIONES_H