#include "../include/cronometro.h"

void imprimirCronometro(Tiempo *t,DWORD inicioCrono, DWORD tiempoPausa) {
		double tiempo = obtenerTiempo(inicioCrono, tiempoPausa);
		t->minutos = (int)tiempo / 60;
		t->segundos = (int)tiempo % 60;
		cambiarColorFuente(0xE);
		moverCursor(OFFSETMENUX+9,10);
		printf("%02d:%02d",t->minutos,t->segundos);
		cambiarColorFuente(0xF);
}

void iniciarCronometro(DWORD *inicioCrono) {
  *inicioCrono = GetTickCount();
}

void iniciarPausa(DWORD *inicioPausa) {
	*inicioPausa = GetTickCount();
}

void finalizarPausa(DWORD inicioPausa, DWORD *tiempoPausa) {
	DWORD finPausa = GetTickCount();
	(*tiempoPausa) += (finPausa - inicioPausa);
}

double obtenerTiempo(DWORD inicioCrono, DWORD tiempoPausa) {
  DWORD puntoActual = GetTickCount();
	return (double)(puntoActual - inicioCrono - tiempoPausa) / 1000.0;
}