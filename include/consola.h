#ifndef CONSOLA_H
#define CONSOLA_H

#include <windows.h>

#define IDI_ICON1 101

void moverCursor(int, int);
void ocultarCursor(void);
void cambiarColorFuente(WORD);
void deshabilitarModoEdicionRapida(void);
void establecerTamanioConsola(int,int);
void dehabilitarRedimension();
void eliminarScroll();
void cambiarIcono();

#endif //CONSOLA_H