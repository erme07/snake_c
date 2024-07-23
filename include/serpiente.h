
#ifndef BLOQUE_H
#define BLOQUE_H

#include "estructuras.h"
#include "colisiones.h"
#include "consola.h"

void imprimirBloque(Bloque*);
void limpiarBloque(int, int);
Bloque *generarBola(Serpiente*,int,int);
Bloque *crearBloque(Coordenadas);
void agregarBloque(Serpiente*, Bloque*);
void comerBola(Serpiente*,Bloque*,Coordenadas);
Coordenadas coordenadasAleatorias(void);
void actualizarCoordenadas(Serpiente*,int);
Coordenadas moverBloque(int);

Serpiente *crearSerpiente(void);
void inicializarSerpiente(Serpiente*);
void imprimirSerpiente(Serpiente *);
void moverSerpiente(Serpiente*);

#endif //BLOQUE_H