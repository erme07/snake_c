#include <stdio.h>
#include "../include/colisiones.h"

BOOL colisionBola(Serpiente *s, Bloque *bola){
	if(s->cabeza->x == bola->x && s->cabeza->y == bola->y){
		return TRUE;
	}
	return FALSE;
}

BOOL colisionEscenarios(Serpiente *s, int ESCENARIO){
	Coordenadas c={s->cabeza->x, s->cabeza->y};
	BOOL colision = FALSE;
	switch(ESCENARIO){
		case ESCENARIO1:
			colision = colisionEscen1(c);
			break;
		case ESCENARIO2:
			colision = colisionEscen2(c);
			break;
		case ESCENARIO3:
			colision = colisionEscen3(c);
			break;
	}
	return colision;
}

BOOL colisionEscen1(Coordenadas c){
	if(c.x == 0 || c.x == COLS-1 || c.y == 0 || c.y == ROWS-1){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		if(c.x==0 || c.x == COLS-1)
			printf("%c", 219);
		else if(c.y == 0)
			printf("%c", 220);
		else
			printf("%c", 223);
		cambiarColorFuente(0x0F);
		return TRUE;
	}
	return FALSE;
}

BOOL colisionEscen2(Coordenadas c){
	if((c.x == 0 || c.x == COLS-1) && ((c.y >=0 && c.y < 11) || (c.y > 18 && c.y <= ROWS-1))){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		printf("%c", 219);
		cambiarColorFuente(0x0F);
		return TRUE;
	}else if((c.y == 0 || c.y == ROWS-1) && ((c.x >= 0 && c.x < 35) || (c.x > 44 && c.x <= COLS-1))){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		if(c.y == 0)
			printf("%c", 220);
		else
			printf("%c", 223);
		cambiarColorFuente(0x0F);
		return TRUE;
	}
	return FALSE;
}

BOOL colisionEscen3(Coordenadas c){
	BOOL colision = colisionEscen2(c);
	if((c.x==13 || c.x==66) && (c.y >= 10 && c.y <= 19)){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		printf("%c", 219);
		cambiarColorFuente(0x0F);
		colision = TRUE;
	}else if((c.y==6 || c.y==23) && (c.x >= 27 && c.x <= 52)){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		printf("%c", 219);
		cambiarColorFuente(0x0F);
		colision = TRUE;
	}
	return colision;
}

BOOL colisionSerpiente(Serpiente *s){
	Bloque *aux = s->cola;
	BOOL colision = FALSE;
	Coordenadas c;
	c.x = s->cabeza->x;
	c.y = s->cabeza->y;
	while(aux->anterior != NULL){
		if(aux->x == c.x && aux->y == c.y){
			colision = TRUE;
			break;
		}
		aux = aux->anterior;
	}
	if(colision){
    cambiarColorFuente(0x04);
    moverCursor(c.x, c.y);
    printf("O");
    cambiarColorFuente(0x0F);
    //imprimirBloque(c,0x04);
  }
		
	return colision;
}

BOOL colisionPortal(Serpiente*s){
  Coordenadas c={s->cabeza->x, s->cabeza->y};
  if((c.x == 0 || c.x == COLS-1) && (c.y >= 11 && c.y <= 18 )){
		cambiarColorFuente(0x09);
		moverCursor(0, c.y);
		printf("%c", 219);
    moverCursor(COLS-1, c.y);
		printf("%c", 219);
		cambiarColorFuente(0x0F);
		return TRUE;
	}else if((c.y == 0 || c.y == ROWS-1) && (c.x >= 35 && c.x <= 44)){
		cambiarColorFuente(0x09);
		moverCursor(c.x, 0);
		printf("%c", 220);
		moverCursor(c.x, ROWS-1);
		printf("%c", 223);
		cambiarColorFuente(0x0F);
		return TRUE;
	}
	return FALSE;
}