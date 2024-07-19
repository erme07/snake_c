#ifndef CONSOLA_H
#define CONSOLA_H

#include <windows.h>

void moverCursor(int, int);
void hideCursor(void);
void cambiarColorFuente(WORD);
void disableQuickEditMode(void);

#endif //CONSOLA_H