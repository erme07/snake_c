#ifndef CRONOMETRO_H
#define CRONOMETRO_H

#include <windows.h>
#include <stdio.h>
#include "estructuras.h"
#include "consola.h"

void iniciarCronometro(DWORD*);
void iniciarPausa(DWORD*);
void finalizarPausa(DWORD,DWORD*);
double obtenerTiempo(DWORD,DWORD);
void imprimirCronometro(Tiempo *, DWORD, DWORD);

#endif //CRONOMETRO_H