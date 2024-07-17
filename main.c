#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "include/escenarios.h"
#include "include/consola.h"
#include "include/colisiones.h"

#define SUP_IZQ 201
#define SUP_DER 187
#define INF_IZQ 200
#define INF_DER 188
#define VERTICAL 186
#define HORIZONTAL 205

#define FRAMERATE 16 //60fps aprox
//#define VELOCIDAD 80

enum DIRECCIONES{
	ARRIBA, 
	ABAJO, 
	IZQUIERDA, 
	DERECHA
};

typedef struct coordenadas{
	int x;
	int y;
}Coordenadas;

typedef struct bloque{
	int x;
	int y;
	struct bloque *siguiente;
	struct bloque *anterior;
}Bloque;

typedef struct serpiente{
	Bloque *cabeza;
	int largo;
	Bloque *cola;
}Serpiente;



void imprimirBloque(Coordenadas,int);
void limpiarBloque(int, int);
Bloque *generarBola(Serpiente*);

Serpiente *crearSerpiente(void);
Bloque *crearBloque(int,int);
void liberarMemoria(Serpiente*);
void agregarBloque(Serpiente*, Bloque*);
void inicializarSerpiente(Serpiente*);
void imprimirSerpiente(Serpiente *);

Coordenadas coordenadasAleatorias(void);
void actualizarCoordenadas(Serpiente*,int);
void moverSerpiente(Serpiente*,int);
void comerBola(Serpiente*,Bloque*,Coordenadas);
Coordenadas posicionarCabeza(int);

BOOL colisionBola(Serpiente*, Bloque*);
BOOL colisionEscenarios(Serpiente*,int);
BOOL colisionSerpiente(Serpiente*);
BOOL colisionEscen1(Coordenadas);
BOOL colisionEscen2(Coordenadas);
BOOL colisionEscen3(Coordenadas);

int main(){
	int direccion = IZQUIERDA,T=0;
	int VELOCIDAD = 80;
	int ESCENARIO = ESCENARIO1;
	BOOL game_over = FALSE;
	Coordenadas cola;

	srand(time(NULL));
	hideCursor();
	dibujarEscenario(ESCENARIO);
	
	Serpiente *serpiente = crearSerpiente();
	Bloque *bloque = generarBola(serpiente);
	inicializarSerpiente(serpiente);
	imprimirSerpiente(serpiente);


	while(!game_over){
		cola.x = serpiente->cola->x;
		cola.y = serpiente->cola->y;
		if(GetAsyncKeyState(VK_UP) & 0x8000) {
			if(direccion == ARRIBA)
				VELOCIDAD = 15;
			else if(direccion != ABAJO){
				direccion = ARRIBA;
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente,direccion);
				
				if(colisionBola(serpiente, bloque)){
					agregarBloque(serpiente, bloque);
					bloque = generarBola(serpiente);
				}
				else if(colisionEscenarios(serpiente, ESCENARIO)){
					game_over = TRUE;
				}
				else if(colisionSerpiente(serpiente)){
					game_over = TRUE;
				}
				T = 0;
			}
		}
		else if(GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if(direccion == ABAJO)
				VELOCIDAD = 15;
			else if(direccion != ARRIBA){
				direccion = ABAJO;
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente,direccion);
				if(colisionBola(serpiente, bloque)){
					agregarBloque(serpiente, bloque);
					bloque = generarBola(serpiente);
				}
				else if(colisionEscenarios(serpiente, ESCENARIO)){
					game_over = TRUE;
				}
				else if(colisionSerpiente(serpiente)){
					game_over = TRUE;
				}
				T = 0;
			}
		}
		if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if(direccion == IZQUIERDA)
				VELOCIDAD = 10;
			else if(direccion != DERECHA){
				direccion = IZQUIERDA;
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente,direccion);
				if(colisionBola(serpiente, bloque)){
					agregarBloque(serpiente, bloque);
					bloque = generarBola(serpiente);
				}
				else if(colisionEscenarios(serpiente, ESCENARIO)){
					game_over = TRUE;
				}
				else if(colisionSerpiente(serpiente)){
					game_over = TRUE;
				}
				T = 0;
			}
		}
		else if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if(direccion == DERECHA)
				VELOCIDAD = 10;
			else if(direccion != IZQUIERDA){
				direccion = DERECHA;
				
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente,direccion);
				if(colisionBola(serpiente, bloque)){
					agregarBloque(serpiente, bloque);
					bloque = generarBola(serpiente);
				}
				else if(colisionEscenarios(serpiente, ESCENARIO)){
					game_over = TRUE;
				}
				else if(colisionSerpiente(serpiente)){
					game_over = TRUE;
				}
				T = 0;
			}
		}
		else if(GetAsyncKeyState('0') & 0x8000) {
			game_over = TRUE;
		}
		
		if(T>=VELOCIDAD){
			
			actualizarCoordenadas(serpiente, direccion);
			moverSerpiente(serpiente,direccion);
			if(colisionBola(serpiente, bloque)){
					comerBola(serpiente, bloque, cola);
					Sleep(VELOCIDAD);
					bloque = generarBola(serpiente);
			}
			else if(colisionEscenarios(serpiente, ESCENARIO)){
					game_over = TRUE;
			}
			else if(colisionSerpiente(serpiente)){
					game_over = TRUE;
			}
			
			T = 0;
		}
		
		Sleep(FRAMERATE);  // Para evitar usar el 100% de la CPU
		T += FRAMERATE;
		//VELOCIDAD = 80;
		if(direccion == ARRIBA || direccion == ABAJO)
			VELOCIDAD = 100;
		else VELOCIDAD = 80;
	}
	liberarMemoria(serpiente);
	moverCursor(2,ROWS);
	system("pause");
	return 0;
}

Coordenadas posicionarCabeza(int direccion){
	Coordenadas c={0,0};
	switch(direccion){
			case ARRIBA: //arriba
				c.y--;
				break;
			case ABAJO: //abajo
				c.y++;
				break;
			case IZQUIERDA: //izquierda
				c.x--;
				break;
			case DERECHA: //derecha
				c.x++;
				break;
	}
	return c;
}

void comerBola(Serpiente *serpiente, Bloque *bloque, Coordenadas c){

	bloque->x = c.x;
	bloque->y = c.y;
	agregarBloque(serpiente, bloque);
}

void actualizarCoordenadas(Serpiente *s, int direccion){
	Bloque *aux = s->cola;
	Coordenadas c = posicionarCabeza(direccion);
	limpiarBloque(aux->x, aux->y);
	while(aux->anterior != NULL){
		aux->x = aux->anterior->x;
		aux->y = aux->anterior->y;
		aux = aux->anterior;
	}
	s->cabeza->x += c.x;
	s->cabeza->y += c.y;
}

void moverSerpiente(Serpiente *s,int direccion){
	cambiarColorFuente(0x0A);
	//imprimirBloque(s->cabeza->x, s->cabeza->y);
	imprimirSerpiente(s);
	cambiarColorFuente(0x0F);
}

void limpiarBloque(int x, int y){
	moverCursor(x, y);
	printf(" ");
}

Coordenadas coordenadasAleatorias(){
	Coordenadas c;
	c.x = rand() % (COLS-2) + 1; // posiicon aleatoria en x
	c.y = rand() % (ROWS-2) + 1; // posicion aleatoria en y
	return c;
}

Bloque *generarBola(Serpiente*s){
	Bloque *aux = s->cola;
	Coordenadas c = coordenadasAleatorias();
	BOOL coordenadasOcupadas;
	do{
		coordenadasOcupadas = FALSE;
		c = coordenadasAleatorias();
		aux = s->cola;
		while(aux != NULL) {
			if(aux->x == c.x && aux->y == c.y) {
				coordenadasOcupadas = TRUE;
				break; // Salir del bucle si se encuentra una coincidencia
			}
			aux = aux->anterior;
		}
	} while(coordenadasOcupadas); // Repetir si las coordenadas están ocupadas
	Bloque *bola = crearBloque(c.x, c.y);
	imprimirBloque(c,0x0C);
	return bola;
}

void imprimirBloque(Coordenadas c, int color){
	cambiarColorFuente(color);
	moverCursor(c.x, c.y);
	printf("O");
	cambiarColorFuente(0x0F);
}


Serpiente *crearSerpiente(){
	Serpiente *serpiente = (Serpiente *)malloc(sizeof(Serpiente));
	serpiente->cabeza = NULL;
	serpiente->largo = 0;
	serpiente->cola = NULL;
	return serpiente;
}

Bloque *crearBloque (int x, int y){
	Bloque *bloque = (Bloque *)malloc(sizeof(Bloque));
	bloque->x = x;
	bloque->y = y;
	bloque->siguiente = NULL;
	bloque->anterior = NULL;
	return bloque;
}

void agregarBloque(Serpiente *serpiente, Bloque *bloque){
	if(serpiente->cabeza == NULL){
		serpiente->cabeza = bloque;
		serpiente->cola = bloque;
	}else{
		//agregar al final
		serpiente->cola->siguiente = bloque;
		bloque->anterior = serpiente->cola;
		serpiente->cola = bloque;
	}
	serpiente->largo++;
}

void liberarMemoria(Serpiente *serpiente){
	Bloque *aux = serpiente->cabeza;
	while(aux != NULL){
		Bloque *temp = aux;
		aux = aux->siguiente;
		free(temp);
	}
	free(serpiente);
}

void inicializarSerpiente(Serpiente *serpiente){
	Bloque *b1 = crearBloque(42,16);
	Bloque *b2 = crearBloque(41,16);
	Bloque *b3 = crearBloque(40,16);
	Bloque *b4 = crearBloque(39,16);
	Bloque *b5 = crearBloque(38,16);
	agregarBloque(serpiente, b5);
	agregarBloque(serpiente, b4);
	agregarBloque(serpiente, b3);
	agregarBloque(serpiente, b2);
	agregarBloque(serpiente, b1);
}

void imprimirSerpiente(Serpiente *serpiente){
	Bloque *aux = serpiente->cabeza;
	Coordenadas c;
	while(aux != NULL){
		c.x = aux->x;
		c.y = aux->y;
		imprimirBloque(c,0x0A);
		aux = aux->siguiente;
	}
}

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
	if(colision)
		imprimirBloque(c,0x04);
	return colision;
}