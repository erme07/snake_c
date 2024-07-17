#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "include/escenarios.h"
#include "include/consola.h"
#include "include/colisiones.h"
#include "include/estructuras.h"

#define FRAMERATE 16 //60fps aprox
//#define VELOCIDAD 80

void imprimirBloque(Bloque*,int);
void limpiarBloque(int, int);
Bloque *generarBola(Serpiente*);

Serpiente *crearSerpiente(void);
Bloque *crearBloque(Coordenadas,char);
void liberarMemoria(Serpiente*);
void agregarBloque(Serpiente*, Bloque*);
void inicializarSerpiente(Serpiente*);
void imprimirSerpiente(Serpiente *);

Coordenadas coordenadasAleatorias(void);
void actualizarCoordenadas(Serpiente*,int);
void moverSerpiente(Serpiente*,int);
void comerBola(Serpiente*,Bloque*,Coordenadas);
Coordenadas posicionarCabeza(int);



int main(){
	int direccion = IZQUIERDA,T=0;
	int VELOCIDAD = 80;
	int ESCENARIO = ESCENARIO2;
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
			if( (ESCENARIO == ESCENARIO2 || ESCENARIO == ESCENARIO3 ) && colisionPortal(serpiente)){
				if(serpiente->cabeza->x == 0)
					serpiente->cabeza->x = COLS-2;
				else if(serpiente->cabeza->x == COLS-1)
					serpiente->cabeza->x = 1;
				else if(serpiente->cabeza->y == 0)
					serpiente->cabeza->y = ROWS-2;
				else if(serpiente->cabeza->y == ROWS-1)
					serpiente->cabeza->y = 1;
			}
			else
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
	Bloque *bola = crearBloque(c,'O');
	imprimirBloque(bola,0x0C);
	return bola;
}

void imprimirBloque(Bloque *b, int color){
	cambiarColorFuente(color);
	moverCursor(b->x, b->y);
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

Bloque *crearBloque (Coordenadas c,char caracter){
	Bloque *bloque = (Bloque *)malloc(sizeof(Bloque));
	bloque->x = c.x;
	bloque->y = c.y;
	bloque->valor = caracter;
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
	Coordenadas c[5];
	for (int i = 0;i<5;i++){
		c[i].x = 38+i;
		c[i].y = 16;
		Bloque *b = crearBloque(c[i],'O');
		agregarBloque(serpiente, b);
	}
}

void imprimirSerpiente(Serpiente *serpiente){
	Bloque *aux = serpiente->cabeza;
	while(aux != NULL){
		imprimirBloque(aux,0x0A);
		aux = aux->siguiente;
	}
}

