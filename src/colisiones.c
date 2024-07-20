#include <stdio.h>
#include "../include/colisiones.h"

BOOL colisionBola(Serpiente *s, Bloque *bola){
	if(bola==NULL)
		return FALSE;
	else if(s->cabeza->posicion.x == bola->posicion.x && s->cabeza->posicion.y == bola->posicion.y){
		return TRUE;
	}
	return FALSE;
}

BOOL colisionEscenarios(Serpiente *s, int ESCENARIO){
	Coordenadas c={s->cabeza->posicion.x, s->cabeza->posicion.y};
	int tiempo;
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
	if(colision){
		if(s->largo > 40)
			tiempo = 10;
		else if(s->largo > 30)
			tiempo = 30;
		else if(s->largo > 20)
			tiempo = 40;
		else if(s->largo > 10)
			tiempo = 50;
		else
			tiempo = 60;
		matarSerpiente(s,tiempo);
	}
	return colision;
}

BOOL colisionEscen1(Coordenadas c){
	if(c.x == OFFSETX || c.x == COLS-1+OFFSETX || c.y == OFFSETY || c.y == ROWS-1+OFFSETY){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		if(c.x==OFFSETX || c.x == COLS-1+OFFSETX)
			printf("%c", 219);
		else if(c.y == OFFSETY)
			printf("%c", 220);
		else
			printf("%c", 223);
		cambiarColorFuente(0x0F);
		return TRUE;
	}
	return FALSE;
}

BOOL colisionEscen2(Coordenadas c){
	if((c.x == OFFSETX || c.x == COLS-1+OFFSETX) && ((c.y >=OFFSETY && c.y < 8+OFFSETY) || (c.y >= 13+OFFSETY && c.y <= ROWS-1+OFFSETY))){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		printf("%c", 219);
		cambiarColorFuente(0x0F);
		return TRUE;
	}else if((c.y == OFFSETY || c.y == ROWS-1+OFFSETY) && ((c.x >= OFFSETX && c.x <= 24+OFFSETX) || (c.x >= 35+OFFSETX && c.x <= COLS-1+OFFSETX))){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		if(c.y == OFFSETY)
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
	if((c.x==9+OFFSETX || c.x==50+OFFSETX) && (c.y >= 7+OFFSETY && c.y <= 12+OFFSETY)){
		cambiarColorFuente(0x04);
		moverCursor(c.x, c.y);
		printf("%c", 219);
		cambiarColorFuente(0x0F);
		colision = TRUE;
	}else if((c.y==4+OFFSETY || c.y==15+OFFSETY) && (c.x >= 24+OFFSETX && c.x <= 35+OFFSETX)){
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
	int tiempo;
	Coordenadas c;
	c.x = s->cabeza->posicion.x;
	c.y = s->cabeza->posicion.y;
	while(aux->anterior != NULL){
		if(aux->posicion.x == c.x && aux->posicion.y == c.y){
			colision = TRUE;
			break;
		}
		aux = aux->anterior;
	}
	if(colision){
		if(s->largo > 40)
			tiempo = 10;
		else if(s->largo > 30)
			tiempo = 30;
		else if(s->largo > 20)
			tiempo = 50;
		else if(s->largo > 10)
			tiempo = 80;
		else
			tiempo = 100;
		matarSerpiente(s,tiempo);
	}
	return colision;
}

void matarSerpiente(Serpiente*s,int tiempo){
	Bloque *aux = s->cabeza;
	cambiarColorFuente(0x04);
	while(aux!=NULL){
		if(aux->anterior!=NULL){
			moverCursor(aux->posicion.x, aux->posicion.y);
			printf("X");
			Sleep(tiempo);
		}
		aux = aux->siguiente;
	}
	cambiarColorFuente(0x0F);
}

// BOOL colisionPortal(Serpiente*s){
//   Coordenadas c={s->cabeza->posicion.x, s->cabeza->posicion.y};
//   if((c.x == 0 || c.x == COLS-1) && (c.y >= 11 && c.y <= 18 )){
//     //encenderPortalHorizontal();
//     cambiarColorFuente(0x01);
//     moverCursor(c.x, c.y);
//     printf("%c\n",219);
// 		return TRUE;
// 	}else if((c.y == 0 || c.y == ROWS-1) && (c.x >= 35 && c.x <= 44)){
//     //encenderPortalVertical();
//     cambiarColorFuente(0x01);
//     moverCursor(c.x, c.y);
//     if(c.y==0)
//       printf("%c",220);
//     if (c.y==ROWS-1)
//       printf("%c",223);
// 		return TRUE;
// 	}
// 	return FALSE;
// }
BOOL colisionPortalH(Serpiente*s){
  Coordenadas c={s->cabeza->posicion.x, s->cabeza->posicion.y};
  if((c.x == OFFSETX || c.x == COLS-1+OFFSETX) && (c.y >= 7+OFFSETY && c.y <= 12+OFFSETY )){
		return TRUE;
	}
	return FALSE;
}

BOOL colisionPortalV(Serpiente*s){
  Coordenadas c={s->cabeza->posicion.x, s->cabeza->posicion.y};
  if((c.y == OFFSETY || c.y == ROWS-1+OFFSETY) && (c.x >= 25+OFFSETX && c.x <= 34+OFFSETX)){
		return TRUE;
	}
	return FALSE;
}

BOOL colisionColaH(Serpiente*s){
  Coordenadas c={s->cola->posicion.x, s->cola->posicion.y};
  if((c.x == 1+OFFSETX || c.x == COLS-2+OFFSETX) && (c.y >= 7+OFFSETY && c.y <= 12+OFFSETY )){
		return TRUE;
	}
	return FALSE;
}

BOOL colisionColaV(Serpiente*s){
  Coordenadas c={s->cola->posicion.x, s->cola->posicion.y};
  if((c.y == 1+OFFSETY || c.y == ROWS-2+OFFSETY) && (c.x >= 25+OFFSETX && c.x <= 34+OFFSETX)){
		return TRUE;
	}
	return FALSE;
}

void encenderPortalHorizontal(){
  cambiarColorFuente(0x09);
  for(int i=0;i<6;i++){
		moverCursor(OFFSETX,7+i+OFFSETY);
    printf("%c",219);
		moverCursor(COLS-1+OFFSETX,7+i+OFFSETY);
		printf("%c",219);
	}
  cambiarColorFuente(0x0F);
}

void apagarPortalHorizontal(){
  cambiarColorFuente(0x01);
  for(int i=0;i<6;i++){
		moverCursor(OFFSETX,7+i+OFFSETY);
    printf("%c",219);
		moverCursor(COLS-1+OFFSETX,7+i+OFFSETY);
		printf("%c",219);
	}
  cambiarColorFuente(0x0F);
}

void encenderPortalVertical(){
  cambiarColorFuente(0x09);
  moverCursor(25+OFFSETX,OFFSETY);
  for (int i=0;i<10;i++)
    printf("%c",220);
  moverCursor(25+OFFSETX,ROWS-1+OFFSETY);
  for (int i=0;i<10;i++)
    printf("%c",223);
  cambiarColorFuente(0x0F);
}

void apagarPortalVertical(){
  cambiarColorFuente(0x01);
  moverCursor(25+OFFSETX,OFFSETY);
  for (int i=0;i<10;i++)
    printf("%c",220);
  moverCursor(25+OFFSETX,ROWS-1+OFFSETY);
  for (int i=0;i<10;i++)
    printf("%c",223);
  cambiarColorFuente(0x0F);
}

void teletransportar(Serpiente *s){
  if(s->cabeza->posicion.x == OFFSETX)
    s->cabeza->posicion.x = COLS-2+OFFSETX;
  else if(s->cabeza->posicion.x == COLS-1+OFFSETX)
    s->cabeza->posicion.x = 1+OFFSETX;
  else if(s->cabeza->posicion.y == OFFSETY)
    s->cabeza->posicion.y = ROWS-2+OFFSETY;
  else if(s->cabeza->posicion.y == ROWS-1+OFFSETY)
    s->cabeza->posicion.y = 1+OFFSETY;
}

int detectarColisiones(Serpiente *s, Bloque *b,Bloque *bt,Bloque*bm, int ESCEN){
	if( (ESCEN == ESCENARIO2 || ESCEN == ESCENARIO3 )){
		if(colisionPortalV(s)){
			return COLISION_PORTALV;
		}else if(colisionPortalH(s)){
			return COLISION_PORTALH;
		}
		if(colisionColaH(s)){
			return COLISION_COLAH;
		}else if(colisionColaV(s)){
			return COLISION_COLAV;
		}
	}
	if(colisionBola(s, b))
		return COLISION_BOLA;
	else if(colisionBola(s, bt))
			return COLISION_BOLATEMP;
	else if(colisionBola(s, bm))
			return COLISION_BOLAMOVIL;
	else if(colisionEscenarios(s, ESCEN))
		return COLISION_ESCENARIO;
	else if(colisionSerpiente(s))
		return COLISION_SERPIENTE;
	else 
		return 0;
}