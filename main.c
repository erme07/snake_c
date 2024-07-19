#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "include/escenarios.h"
#include "include/consola.h"
#include "include/colisiones.h"
#include "include/estructuras.h"
#include "include/menu.h"

#define FRAMERATE 20 //60fps aprox
//#define VELOCIDAD 80

enum COLISIONES{
	COLISION_BOLA = 1,
	COLISION_ESCENARIO,
	COLISION_SERPIENTE,
	COLISION_PORTALV,
	COLISION_PORTALH,
	COLISION_COLAV,
	COLISION_COLAH
};

void imprimirBloque(Bloque*);
void limpiarBloque(int, int);
Bloque *generarBola(Serpiente*,int,int);

Serpiente *crearSerpiente(void);
Bloque *crearBloque(Coordenadas,char,int);
void liberarMemoria(Serpiente*);
void agregarBloque(Serpiente*, Bloque*);
void inicializarSerpiente(Serpiente*);
void imprimirSerpiente(Serpiente *);

Coordenadas coordenadasAleatorias(void);
void actualizarCoordenadas(Serpiente*,int);
void moverSerpiente(Serpiente*);
void comerBola(Serpiente*,Bloque*,Coordenadas);
Coordenadas posicionarCabeza(int);

int detectarColisiones(Serpiente*,Bloque*,int);
void estadisticas(Serpiente*,int,int);
int establecerVelocidad(int,int);
int definirNivel(Serpiente*);

LARGE_INTEGER inicio, fin, frecuencia;

// Función para iniciar el cronómetro
void iniciarCronometro() {
    QueryPerformanceFrequency(&frecuencia);
    QueryPerformanceCounter(&inicio);
		cambiarColorFuente(0xE);
		moverCursor(9, 10);
		printf("00:00");
}

// Función para obtener el tiempo transcurrido en segundos
double obtenerTiempo() {
    QueryPerformanceCounter(&fin);
    return (double)(fin.QuadPart - inicio.QuadPart) / frecuencia.QuadPart;
}

// Función para imprimir el tiempo transcurrido
void imprimirCronometro(int *segundos,int*minutos) {
	double tiempo = obtenerTiempo();
  *minutos = (int)tiempo / 60;
	if(*minutos>60)
		*minutos = 0;
	*segundos = (int)tiempo % 60;
	cambiarColorFuente(0xE);
	moverCursor(9,10);
  printf("%02d:%02d",*minutos,*segundos);
}


int main(){
	int direccion = IZQUIERDA;
	int VELOCIDAD = 100;
	int ESCENARIO = ESCENARIO1;
	int CICLOS = 0;
	int segundos, minutos;
	int puntaje=0, nivel=1;
	BOOL game_over = FALSE;
	BOOL start = FALSE;
	BOOL btemporal = FALSE;
	BOOL bmovil = FALSE;
	int portalH=0,portalV=0;
	Coordenadas cola;

	srand(time(NULL));
	hideCursor();
	dibujarEscenario(ESCENARIO);
	disableQuickEditMode();
	start = iniciarJuego(&ESCENARIO);
	
	Serpiente *serpiente = crearSerpiente();
	Bloque *bloque = generarBola(serpiente,ESCENARIO,0x0F);
	Bloque *bolatemporal,*bolamovil;
	double intervaloActualizacion;
	double ultimoTiempoActualizado;

	if(start){
		inicializarSerpiente(serpiente);
		imprimirSerpiente(serpiente);
		iniciarCronometro();
		intervaloActualizacion = 0.5; // Actualiza el tiempo en pantalla cada 0.5 segundos.
  	ultimoTiempoActualizado = 0;
	}

	while(!game_over && start){
		cola.x = serpiente->cola->posicion.x;
		cola.y = serpiente->cola->posicion.y;

		if(GetAsyncKeyState(VK_UP) & 0x8000){
			if(direccion == ARRIBA)
				VELOCIDAD = 20;
			else if(direccion != ABAJO){
				direccion = ARRIBA;
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente);
				switch(detectarColisiones(serpiente, bloque, ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						break;
					case COLISION_ESCENARIO:
						game_over = TRUE;
						break;
					case COLISION_SERPIENTE:
						game_over = TRUE;
						break;
					case COLISION_PORTALV:
						encenderPortalVertical();
						portalV+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_PORTALH:
						encenderPortalHorizontal();
						portalH+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_COLAH:
						if(portalH>0)
							portalH--;
						if(portalH==0)
							apagarPortalHorizontal();
						break;
					case COLISION_COLAV:
						if(portalV>0)
							portalV--;
						if(portalV==0)
							apagarPortalVertical();
						break;
				}
				CICLOS = 0;
			}
		}
		else if(GetAsyncKeyState(VK_DOWN) & 0x8000) {
			if(direccion == ABAJO)
				VELOCIDAD = 20;
			else if(direccion != ARRIBA){
				direccion = ABAJO;
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente);
				switch(detectarColisiones(serpiente, bloque, ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						break;
					case COLISION_ESCENARIO:
						game_over = TRUE;
						break;
					case COLISION_SERPIENTE:
						game_over = TRUE;
						break;
					case COLISION_PORTALV:
						encenderPortalVertical();
						portalV+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_PORTALH:
						encenderPortalHorizontal();
						portalH+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_COLAH:
						if(portalH>0)
							portalH--;
						if(portalH==0)
							apagarPortalHorizontal();
						break;
					case COLISION_COLAV:
						if(portalV>0)
							portalV--;
						if(portalV==0)
							apagarPortalVertical();
						break;
				}
				CICLOS = 0;
			}
		}
		if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if(direccion == IZQUIERDA)
				VELOCIDAD = 10;
			else if(direccion != DERECHA){
				direccion = IZQUIERDA;
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente);
				switch(detectarColisiones(serpiente, bloque, ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						break;
					case COLISION_ESCENARIO:
						game_over = TRUE;
						break;
					case COLISION_SERPIENTE:
						game_over = TRUE;
						break;
					case COLISION_PORTALV:
						encenderPortalVertical();
						portalV+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_PORTALH:
						encenderPortalHorizontal();
						portalH+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_COLAH:
						if(portalH>0)
							portalH--;
						if(portalH==0)
							apagarPortalHorizontal();
						break;
					case COLISION_COLAV:
						if(portalV>0)
							portalV--;
						if(portalV==0)
							apagarPortalVertical();
						break;
				}
				CICLOS = 0;
			}
		}
		else if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if(direccion == DERECHA)
				VELOCIDAD = 10;
			else if(direccion != IZQUIERDA){
				direccion = DERECHA;
				actualizarCoordenadas(serpiente, direccion);
				Sleep(VELOCIDAD);
				moverSerpiente(serpiente);
				switch(detectarColisiones(serpiente, bloque, ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						break;
					case COLISION_ESCENARIO:
						game_over = TRUE;
						break;
					case COLISION_SERPIENTE:
						game_over = TRUE;
						break;
					case COLISION_PORTALV:
						encenderPortalVertical();
						portalV+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_PORTALH:
						encenderPortalHorizontal();
						portalH+=2;
						teletransportar(serpiente);
						moverSerpiente(serpiente);
						break;
					case COLISION_COLAH:
						if(portalH>0)
							portalH--;
						if(portalH==0)
							apagarPortalHorizontal();
						break;
					case COLISION_COLAV:
						if(portalV>0)
							portalV--;
						if(portalV==0)
							apagarPortalVertical();
						break;
				}
				CICLOS = 0;
			}
		}
		if(CICLOS >= VELOCIDAD){
			actualizarCoordenadas(serpiente, direccion);
			moverSerpiente(serpiente);
			switch(detectarColisiones(serpiente, bloque, ESCENARIO)){
				case COLISION_BOLA:
					comerBola(serpiente, bloque, cola);
					Sleep(VELOCIDAD);
					bloque = generarBola(serpiente,ESCENARIO,0x0F);
					break;
				case COLISION_ESCENARIO:
					game_over = TRUE;
					break;
				case COLISION_SERPIENTE:
					game_over = TRUE;
					break;
				case COLISION_PORTALV:
					encenderPortalVertical();
					portalV+=2;
					teletransportar(serpiente);
					moverSerpiente(serpiente);
					break;
				case COLISION_PORTALH:
					encenderPortalHorizontal();
					portalH+=2;
					teletransportar(serpiente);
					moverSerpiente(serpiente);
					break;
				case COLISION_COLAH:
					if(portalH>0)
							portalH--;
					if(portalH==0)
						apagarPortalHorizontal();
					break;
				case COLISION_COLAV:
					if(portalV>0)
							portalV--;
					if(portalV==0)
						apagarPortalVertical();
					break;
			}
			CICLOS = 0;
		}
		else if(GetAsyncKeyState(VK_SPACE) & 0x8000) {
			game_over = TRUE;
		}

		imprimirBloque(bloque);
		Sleep(FRAMERATE);  // Para evitar usar el 100% de la CPU
		CICLOS += FRAMERATE;

		nivel = definirNivel(serpiente);
		VELOCIDAD = establecerVelocidad(direccion, nivel);

		//puntaje = (serpiente->largo - 5) * 10 *nivel;

		estadisticas(serpiente,puntaje,nivel);
		double tiempoActual = obtenerTiempo();
		if (tiempoActual - ultimoTiempoActualizado >= intervaloActualizacion) {
				imprimirCronometro(&segundos,&minutos);
				ultimoTiempoActualizado = tiempoActual;
		}
		
		if(!btemporal && (segundos == 10 ||segundos==25)){
			bolatemporal = generarBola(serpiente,ESCENARIO,0x0E);
			btemporal = TRUE;
		}
		if(btemporal && (segundos == 14 ||segundos==29)){
			limpiarBloque(bolatemporal->posicion.x,bolatemporal->posicion.y);
			btemporal = FALSE;
			free(bolatemporal);
		}


		if(!bmovil && (segundos == 40)){
			bolamovil = generarBola(serpiente, ESCENARIO, 0x6);
			bmovil = TRUE;
		}
		if(bmovil && (segundos==50)){
			limpiarBloque(bolamovil->posicion.x,bolamovil->posicion.y);
			bmovil = FALSE;
			free(bolamovil);
		}

		
	}
	
	liberarMemoria(serpiente);
	free(bloque);
	moverCursor(2,ROWS+2);
	system("pause");
	return 0;
}


// ----------- funciones -------------

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
	bloque->posicion.x = c.x;
	bloque->posicion.y = c.y;
	bloque->color = 0x0A;
	bloque->valor = 'O';
	agregarBloque(serpiente, bloque);
}

void actualizarCoordenadas(Serpiente *s, int direccion){
	Bloque *aux = s->cola;
	Coordenadas c = posicionarCabeza(direccion);
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

void limpiarBloque(int x, int y){
	moverCursor(x, y);
	printf(" ");
}

Coordenadas coordenadasAleatorias(){
	Coordenadas c;
	c.x = rand() % (COLS-2) + (1 + OFFSETX); // posiicon aleatoria en x
	c.y = rand() % (ROWS-2) + (1 + OFFSETY); // posicion aleatoria en y
	return c;
}

Bloque *generarBola(Serpiente*s,int ESCEN,int color){
	Bloque *aux = s->cola;
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
			aux = aux->anterior;
		}
	} while(coordenadasOcupadas); // Repetir si las coordenadas están ocupadas
	Bloque *bola = crearBloque(c,254,color); //254 craracter ascii
	imprimirBloque(bola);
	return bola;
}


void imprimirBloque(Bloque *b){
	cambiarColorFuente(b->color);
	moverCursor(b->posicion.x, b->posicion.y);
	printf("%c", b->valor);
	cambiarColorFuente(0x0F);
}


Serpiente *crearSerpiente(){
	Serpiente *serpiente = (Serpiente *)malloc(sizeof(Serpiente));
	serpiente->cabeza = NULL;
	serpiente->largo = 0;
	serpiente->cola = NULL;
	return serpiente;
}

Bloque *crearBloque (Coordenadas c,char caracter,int color){
	Bloque *bloque = (Bloque *)malloc(sizeof(Bloque));
	bloque->posicion.x = c.x;
	bloque->posicion.y = c.y;
	bloque->valor = caracter;
	bloque->color = color;
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

int detectarColisiones(Serpiente *s, Bloque* b, int ESCEN){
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
	else if(colisionEscenarios(s, ESCEN))
		return COLISION_ESCENARIO;
	else if(colisionSerpiente(s))
		return COLISION_SERPIENTE;
	else 
		return 0;
}

void imprimirGameOver(){
	printf("███▄ ███▄ ██▄█▄ ███▄  ███▄ █  █ ███▄ ███▄");
	printf("█▄▄▄ █▄▄█ █ █ █ █▄▄▄  █  █ █  █ █▄▄▄ █▄▄▀ ");
	printf("█▄▄█ █  █ █   █ █▄▄▄  ▀██▀ ▀██▀ █▄▄▄ █  █");
}

void estadisticas(Serpiente*s,int puntaje,int nivel){
  cambiarColorFuente(0x0F);
  moverCursor(5, 5);
  printf("Puntaje: ");
	cambiarColorFuente(0xE);
	printf("%d", puntaje);
  moverCursor(7, 6);
	cambiarColorFuente(0x0F);
  printf("Largo: ");
	cambiarColorFuente(0xE);
	printf("%d", s->largo);
	moverCursor(7, 7);
	cambiarColorFuente(0xF);
  printf("Nivel: ");
	cambiarColorFuente(0xE);
	printf("%d", nivel);
	cambiarColorFuente(0xF);
	moverCursor(5, 15);
  printf("%c: 10pts x Nvl", 254);
  moverCursor(5, 16);
  cambiarColorFuente(0xE);
  printf("%c: 25pts x Nvl", 254);
  moverCursor(5, 17);
  cambiarColorFuente(0x6);
  printf("%c: 50pts x Nvl", 254);
  cambiarColorFuente(0xF);
	moverCursor(4, 12);
	printf("pausar/reanudar");
	moverCursor(7, 13);
	printf("(ESPACIO)");
}

int establecerVelocidad(int direccion,int nivel){
	if(nivel==1){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 120;
		else return 100;
	}
	if(nivel==2){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 100;
		else return 80;
	}
	if(nivel==3){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 80;
		else return 60;
	}
	if(nivel==4){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 70;
		else return 40;
	}
	if(nivel==5){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 40;
		else return 20;
	}
	return 100;
}

int definirNivel(Serpiente*s){
	if(s->largo>=100)
		return 5;
	if(s->largo>=90)
		return 4;
	if(s->largo>=60)
		return 3;
	if(s->largo>=30)
		return 2;
	return 1;
}