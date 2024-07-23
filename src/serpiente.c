#include "../include/serpiente.h"
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

Bloque *crearBloque (Coordenadas c,char caracter,int color){
	Bloque *bloque = (Bloque *)malloc(sizeof(Bloque));
	if (bloque == NULL) {
		// No se pudo asignar memoria para el bloque
		return NULL;
  }
	bloque->posicion.x = c.x;
	bloque->posicion.y = c.y;
	bloque->valor = caracter;
	bloque->color = color;
	bloque->siguiente = NULL;
	bloque->anterior = NULL;
	return bloque;
}

void imprimirBloque(Bloque *b){
	cambiarColorFuente(b->color);
	moverCursor(b->posicion.x, b->posicion.y);
	printf("%c", b->valor);
	cambiarColorFuente(0x0F);
}

// Bloque *generarBola(Serpiente*s,int ESCEN,int color){
// 	Bloque *aux = s->cola;
// 	Coordenadas c = coordenadasAleatorias();
// 	BOOL coordenadasOcupadas;
// 	do{
// 		coordenadasOcupadas = FALSE;
// 		c = coordenadasAleatorias();
// 		aux = s->cola;
// 		while(aux != NULL) {
// 			if(aux->posicion.x == c.x && aux->posicion.y == c.y) {
// 				coordenadasOcupadas = TRUE;
// 				break; // Salir del bucle si se encuentra una coincidencia
// 			}
// 			if(ESCEN == ESCENARIO3 && colisionEscen3(c)){
// 				coordenadasOcupadas = TRUE;
// 				break;
// 			}
// 			aux = aux->anterior;
// 		}
// 	} while(coordenadasOcupadas); // Repetir si las coordenadas están ocupadas
// 	Bloque *bola = crearBloque(c,254,color); //254 craracter ascii
// 	imprimirBloque(bola);
// 	return bola;
// }


void generarBola(Serpiente*s,int ESCEN,int color){
	Bloque *aux = s->cabeza;
	Coordenadas c = coordenadasAleatorias();
	BOOL coordenadasOcupadas;
	do{
		coordenadasOcupadas = FALSE;
		c = coordenadasAleatorias();
		aux = s->cola;
		while(aux != NULL) {
			if(aux->posicion.x == c.x && aux->posicion.y == c.y) {
				coordenadasOcupadas = TRUE;
				break; // Salir del bucle si se encuentra una coincidencia
			}
			if(ESCEN == ESCENARIO3 && colisionEscen3(c)){
				coordenadasOcupadas = TRUE;
				break;
			}
			aux = aux->siguiente;
		}
	} while(coordenadasOcupadas); // Repetir si las coordenadas están ocupadas
	Bloque *bola = crearBloque(c,254,color); //254 craracter ascii
	imprimirBloque(bola);
	return bola;
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

void comerBola(Serpiente *serpiente, Bloque *bloque, Coordenadas c){
	bloque->posicion.x = c.x;
	bloque->posicion.y = c.y;
	bloque->color = 0x0A;
	bloque->valor = 'O';
	agregarBloque(serpiente, bloque);
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
	//imprimirSerpiente(s);
	imprimirBloque(s->cabeza);
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
		Bloque *b = crearBloque(c[i],'O',0x0A);
		agregarBloque(serpiente, b);
	}
}

void imprimirSerpiente(Serpiente *serpiente){
	Bloque *aux = serpiente->cabeza;
	while(aux != NULL){
		imprimirBloque(aux);
		aux = aux->siguiente;
	}
}