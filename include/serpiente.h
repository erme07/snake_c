#ifndef BLOQUE_H
#define BLOQUE_H

#include "estructuras.h"
#include "colisiones.h"
#include "consola.h"

void imprimirBloque(int,Coordenadas);
void limpiarBloque(int, int);
void generarBola(Serpiente*,Bola*,int[ROWS][COLS]);
void generarBolaTemporal(Serpiente*,Bola*,int[ROWS][COLS]);
void generarBolaMovil(Serpiente*,Bolamovil*,int[ROWS][COLS]);
void actualizarCoordenadas(Serpiente*,int);
void agregarBloque(Serpiente*, Bloque*);
void comerBola(Serpiente*,Coordenadas,int[ROWS][COLS]);
void inicializarSerpiente(Serpiente*);
void imprimirSerpiente(Serpiente*);
void moverSerpiente(Serpiente*);
Coordenadas coordenadasAleatorias(void);
Coordenadas moverBloque(int);
Bloque *crearBloque(Coordenadas);
Serpiente *crearSerpiente(void);

#endif //BLOQUE_H