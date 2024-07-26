#include "../include/serpiente.h"
#include "../include/colisiones.h"
#include <stdlib.h>
#include <stdio.h>

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

Bloque *crearBloque (Coordenadas c){
	Bloque *bloque = (Bloque *)malloc(sizeof(Bloque));
	if (bloque == NULL) {
		// No se pudo asignar memoria para el bloque
		return NULL;
  }
	bloque->posicion.x = c.x;
	bloque->posicion.y = c.y;
	bloque->siguiente = NULL;
	bloque->anterior = NULL;
	return bloque;
}

void imprimirBloque(int tipoBloque,Coordenadas c){
	moverCursor(c.x, c.y);
	if(tipoBloque == COMUN){
		cambiarColorFuente(BLANCO);
		printf("%c", BOLA);
	}
	else if(tipoBloque == TEMPORAL){
		cambiarColorFuente(DORADO);
		printf("%c", BOLA);
	}
	else if(tipoBloque == MOVIL){
		cambiarColorFuente(ROJO);
		printf("%c", BOLA);
	}else{
		cambiarColorFuente(VERDE);
		printf("O");
	}
	cambiarColorFuente(BLANCO);
}

void generarBola(Serpiente*s, Bola *bolaComun,int matriz[ROWS][COLS]){
	Coordenadas c;
	BOOL coordenadasOcupadas;
	do{
		coordenadasOcupadas = FALSE;
		c = coordenadasAleatorias();
		Bloque *aux = s->cabeza;
		if(matriz[c.y-OFFSETY][c.x-OFFSETX]!=0){
			
			coordenadasOcupadas = TRUE;
		}
		else{
			while(aux != NULL) {
				if(aux->posicion.x == c.x && aux->posicion.y == c.y) {
					coordenadasOcupadas = TRUE;
					break; // Salir del bucle si se encuentra una coincidencia
				}
				aux = aux->siguiente;
			}
		}
	} while(coordenadasOcupadas); // Repetir si las coordenadas están ocupadas
	matriz[c.y-OFFSETY][c.x-OFFSETX] = bolaComun->tipo;
	bolaComun->posicion.x = c.x;
	bolaComun->posicion.y = c.y;
	imprimirBloque(bolaComun->tipo,bolaComun->posicion);
}

void generarBolaTemporal(Serpiente*s,Bola *bolatemp,int matriz[ROWS][COLS]){
	Coordenadas c;
	BOOL coordenadasOcupadas;
	do{
		coordenadasOcupadas = FALSE;
		c = coordenadasAleatorias();
		Bloque *aux = s->cabeza;
		if(matriz[c.y-OFFSETY][c.x-OFFSETX]!=0)
			coordenadasOcupadas = TRUE;
		else{
			while(aux != NULL) {
				if(aux->posicion.x == c.x && aux->posicion.y == c.y) {
					coordenadasOcupadas = TRUE;
					break; // Salir del bucle si se encuentra una coincidencia
				}
				aux = aux->siguiente;
			}
		}
	} while(coordenadasOcupadas); // Repetir si las coordenadas están ocupadas
	matriz[c.y-OFFSETY][c.x-OFFSETX] = bolatemp->tipo;
	bolatemp->posicion.x = c.x;
	bolatemp->posicion.y = c.y;
	imprimirBloque(bolatemp->tipo,c);
}

void generarBolaMovil(Serpiente*s,Bolamovil *bolamov,int matriz[ROWS][COLS]){
	Coordenadas c;
	BOOL coordenadasOcupadas;
	do{
		coordenadasOcupadas = FALSE;
		c = coordenadasAleatorias();
		Bloque *aux = s->cabeza;
		if(matriz[c.y-OFFSETY][c.x-OFFSETX]!=0)
			coordenadasOcupadas = TRUE;
		else{
			while(aux != NULL) {
				if(aux->posicion.x == c.x && aux->posicion.y == c.y) {
					coordenadasOcupadas = TRUE;
					break; // Salir del bucle si se encuentra una coincidencia
				}
				aux = aux->siguiente;
			}
		}
	} while(coordenadasOcupadas); // Repetir si las coordenadas están ocupadas
	matriz[c.y-OFFSETY][c.x-OFFSETX] = bolamov->bola.tipo;
	bolamov->bola.posicion.x = c.x;
	bolamov->bola.posicion.y = c.y;
	imprimirBloque(bolamov->bola.tipo,c);
}

Coordenadas coordenadasAleatorias(){
	Coordenadas c;
	c.x = rand() % (COLS-2) + (1 + OFFSETX); // posiicon aleatoria en x
	c.y = rand() % (ROWS-2) + (1 + OFFSETY); // posicion aleatoria en y
	return c;
}

void limpiarBloque(int x, int y){
	moverCursor(x, y);
	printf(" ");
}

void comerBola(Serpiente *serpiente, Coordenadas c,int matriz[ROWS][COLS]){
	Bloque*b=crearBloque(c);
	Bloque *aux = serpiente->cabeza;
	matriz[aux->posicion.y-OFFSETY][aux->posicion.x-OFFSETX] = 0;
	agregarBloque(serpiente, b);
}

Coordenadas moverBloque(int direccion){
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

void actualizarCoordenadas(Serpiente *s, int direccion){
	Bloque *aux = s->cola;
	Coordenadas c = moverBloque(direccion);
	limpiarBloque(aux->posicion.x, aux->posicion.y);
	while(aux->anterior != NULL){
		aux->posicion.x = aux->anterior->posicion.x;
		aux->posicion.y = aux->anterior->posicion.y;
		aux = aux->anterior;
	}
	s->cabeza->posicion.x += c.x;
	s->cabeza->posicion.y += c.y;
}

void moverSerpiente(Serpiente *s){
	Coordenadas c= s->cabeza->posicion;
	//imprimirSerpiente(s);
	imprimirBloque(CUERPO,c);
}

Serpiente *crearSerpiente(){
	Serpiente *serpiente = (Serpiente *)malloc(sizeof(Serpiente));
	serpiente->cabeza = NULL;
	serpiente->largo = 0;
	serpiente->cola = NULL;
	return serpiente;
}

void inicializarSerpiente(Serpiente *serpiente){
	Coordenadas c[5];
	for (int i = 0;i<5;i++){
		c[i].x = 28+i+OFFSETX;
		c[i].y = 12+OFFSETY;
		Bloque *b = crearBloque(c[i]);
		agregarBloque(serpiente, b);
	}
}

void imprimirSerpiente(Serpiente *serpiente){
	Bloque *aux = serpiente->cabeza;
	while(aux != NULL){
		imprimirBloque(CUERPO,aux->posicion);
		aux = aux->siguiente;
	}
}