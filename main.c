#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "include/escenarios.h"
#include "include/consola.h"
#include "include/colisiones.h"
#include "include/estructuras.h"
#include "include/panel.h"
#include "include/serpiente.h"

#define FRAMERATE 20 //60fps aprox
//#define VELOCIDAD 80


void liberarMemoria(Serpiente*);

int establecerVelocidad(int,int);
int definirNivel(Serpiente*);

void pausarReanudarJuego(BOOL *pausa);

LARGE_INTEGER inicio, frecuencia, tiempoPausado;
BOOL cronometroPausado = FALSE;

// Función para iniciar el cronómetro
void iniciarCronometro() {
    QueryPerformanceFrequency(&frecuencia);
    QueryPerformanceCounter(&inicio);
    tiempoPausado.QuadPart = 0;
    cronometroPausado = FALSE;
}
void pausarCronometro() {
    if (!cronometroPausado) {
        LARGE_INTEGER tiempoPausa;
        QueryPerformanceCounter(&tiempoPausa);
        tiempoPausado.QuadPart = tiempoPausa.QuadPart - inicio.QuadPart;
        cronometroPausado = TRUE;
    }
}
void reanudarCronometro() {
    if (cronometroPausado) {
        LARGE_INTEGER tiempoReanudacion;
        QueryPerformanceCounter(&tiempoReanudacion);
        inicio.QuadPart = tiempoReanudacion.QuadPart - tiempoPausado.QuadPart;
        tiempoPausado.QuadPart = 0;
        cronometroPausado = FALSE;
    }
}
// Función para obtener el tiempo transcurrido en segundos
double obtenerTiempo() {
	if (cronometroPausado) {
        return (double)tiempoPausado.QuadPart / (double)frecuencia.QuadPart;
    } else {
        LARGE_INTEGER ahora;
        QueryPerformanceCounter(&ahora);
        return (double)(ahora.QuadPart - inicio.QuadPart - tiempoPausado.QuadPart) / (double)frecuencia.QuadPart;
    }
}

// Función para imprimir el tiempo transcurrido
void imprimirCronometro(int *segundos,int *minutos) {
	double tiempo = obtenerTiempo();
  *minutos = (int)tiempo / 60;
	// if(*minutos>60)
	// 	*minutos = 0;
	*segundos = (int)tiempo % 60;
	cambiarColorFuente(0xE);
	moverCursor(OFFSETMENUX+9,10);
  printf("%02d:%02d",*minutos,*segundos);
}


int main(){

	int direccion = IZQUIERDA, direccionbolamovil, ESCENARIO = ESCENARIO1;
	int VELOCIDAD = 100, VELOCIDADBOLAMOVIL = 100;
	int CICLOS = 0, CICLOSMOVIL = 0;
	int segundos, minutos, portalH=0, portalV=0;
	int puntaje=0, nivel=1;
	BOOL game_over = FALSE;
	BOOL start = FALSE;
	BOOL btemporal = FALSE;
	BOOL bmovil = FALSE;
	BOOL pause = FALSE;
	BOOL colision3movil = FALSE;
	Serpiente *serpiente = NULL;
	Bloque *bloque = NULL;
	Bloque *bolatemporal=NULL, *bolamovil=NULL;
	double intervaloActualizacion;
	double ultimoTiempoActualizado;
	Coordenadas cola;

	SetConsoleTitle("SNAKE");
	establecerTamanioConsola(740,360);
	eliminarScroll();
	dehabilitarRedimension();
	deshabilitarModoEdicionRapida();
	ocultarCursor();

	srand(time(NULL));
	dibujarEscenario(ESCENARIO);
	
	start = iniciarJuego(&ESCENARIO);
	
	if(start){
		serpiente = crearSerpiente();
		bloque = generarBola(serpiente,ESCENARIO,0x0F);
		inicializarSerpiente(serpiente);
		imprimirSerpiente(serpiente);
		iniciarCronometro();
		cambiarColorFuente(0xE);
		moverCursor(OFFSETMENUX+9, 10);
		printf("00:00");
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
				switch(detectarColisiones(serpiente, bloque,bolatemporal,bolamovil, ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						puntaje += 10 * nivel;
						break;
					case COLISION_BOLATEMP:
						comerBola(serpiente, bolatemporal, cola);
						Sleep(VELOCIDAD);
						btemporal = FALSE;
						puntaje += 25 * nivel;
						break;
					case COLISION_BOLAMOVIL:
						comerBola(serpiente, bolamovil, cola);
						Sleep(VELOCIDAD);
						bmovil = FALSE;
						puntaje += 50 * nivel;
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
				switch(detectarColisiones(serpiente, bloque,bolatemporal, bolamovil,ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						puntaje += 10 * nivel;
						break;
					case COLISION_BOLATEMP:
						comerBola(serpiente, bolatemporal, cola);
						Sleep(VELOCIDAD);
						btemporal = FALSE;
						puntaje += 25 * nivel;
						break;
					case COLISION_BOLAMOVIL:
						comerBola(serpiente, bolamovil, cola);
						Sleep(VELOCIDAD);
						bmovil = FALSE;
						puntaje += 50 * nivel;
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
				switch(detectarColisiones(serpiente, bloque, bolatemporal,bolamovil,ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						puntaje += 10 * nivel;
						break;
					case COLISION_BOLATEMP:
						comerBola(serpiente, bolatemporal, cola);
						Sleep(VELOCIDAD);
						btemporal = FALSE;
						puntaje += 25 * nivel;
						break;
					case COLISION_BOLAMOVIL:
						comerBola(serpiente, bolamovil, cola);
						Sleep(VELOCIDAD);
						bmovil = FALSE;
						puntaje += 50 * nivel;
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
				switch(detectarColisiones(serpiente, bloque,bolatemporal, bolamovil,ESCENARIO)){
					case COLISION_BOLA:
						comerBola(serpiente, bloque, cola);
						Sleep(VELOCIDAD);
						bloque = generarBola(serpiente,ESCENARIO,0x0F);
						puntaje += 10 * nivel;
						break;
					case COLISION_BOLATEMP:
						comerBola(serpiente, bolatemporal, cola);
						Sleep(VELOCIDAD);
						btemporal = FALSE;
						puntaje += 25 * nivel;
						break;
					case COLISION_BOLAMOVIL:
						comerBola(serpiente, bolamovil, cola);
						Sleep(VELOCIDAD);
						bmovil = FALSE;
						puntaje += 50 * nivel;
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
			switch(detectarColisiones(serpiente, bloque,bolatemporal, bolamovil,ESCENARIO)){
				case COLISION_BOLA:
					comerBola(serpiente, bloque, cola);
					Sleep(VELOCIDAD);
					bloque = generarBola(serpiente,ESCENARIO,0x0F);
					puntaje += 10 * nivel;
					break;
				case COLISION_BOLATEMP:
						comerBola(serpiente, bolatemporal, cola);
						Sleep(VELOCIDAD);
						btemporal = FALSE;
						puntaje += 25 * nivel;
						break;
				case COLISION_BOLAMOVIL:
					comerBola(serpiente, bolamovil, cola);
					Sleep(VELOCIDAD);
					bmovil = FALSE;
					puntaje += 50 * nivel;
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
			pausarReanudarJuego(&pause);
			if(pause)
				pausarCronometro();
			else reanudarCronometro();
		}

		if(bmovil){
			if(bolamovil->anterior!=NULL){
				bmovil = FALSE;
				CICLOSMOVIL = 0;
			}
			else if(CICLOSMOVIL>=VELOCIDADBOLAMOVIL){
				Coordenadas c = moverBloque(direccionbolamovil);
				Coordenadas b;
				Bloque *aux = serpiente->cola;
				bolamovil->posicion.x += c.x;
				bolamovil->posicion.y += c.y;
				b.x= bolamovil->posicion.x;
				b.y= bolamovil->posicion.y;
				
				if(!colision3movil){
					//colision3movil = FALSE;
					limpiarBloque(bolamovil->posicion.x-c.x,bolamovil->posicion.y-c.y);
				}
				
				//colision con escenario
				if(b.x == OFFSETX || b.x == COLS-1+OFFSETX || b.y == OFFSETY || b.y == ROWS-1+OFFSETY){
					bmovil = FALSE;
					free(bolamovil);
					bolamovil = NULL;
				}
				else{
					imprimirBloque(bolamovil);
				}
				while(aux->anterior != NULL){
					if(aux->posicion.x == b.x && aux->posicion.y == b.y){
						moverCursor(b.x, b.y);
						cambiarColorFuente(0x0A);
						printf("O");
						cambiarColorFuente(0x0F);
						colision3movil = TRUE;
						break;
					}else  colision3movil = FALSE;
					aux = aux->anterior;
				}
				if((b.x==9+OFFSETX || b.x==50+OFFSETX) && (b.y >= 7+OFFSETY && b.y <= 12+OFFSETY)){
					cambiarColorFuente(0x0F);
					moverCursor(b.x, b.y);
					printf("%c", 219);
					colision3movil = TRUE;
				}else if((b.y==4+OFFSETY || b.y==15+OFFSETY) && (b.x >= 24+OFFSETX && b.x <= 35+OFFSETX)){
					cambiarColorFuente(0x0F);
					moverCursor(b.x, b.y);
					printf("%c", 219);
					colision3movil = TRUE;
				}else if(!colision3movil)
					colision3movil = FALSE;
				
				
				CICLOSMOVIL = 0;
			}
			else
				CICLOSMOVIL += FRAMERATE;
		}

		imprimirBloque(bloque);
		Sleep(FRAMERATE);  // Para evitar usar el 100% de la CPU
		CICLOS += FRAMERATE;
		

		nivel = definirNivel(serpiente);
		VELOCIDAD = establecerVelocidad(direccion, nivel);

		estadisticas(serpiente,puntaje,nivel);
		double tiempoActual = obtenerTiempo();
		if ((tiempoActual - ultimoTiempoActualizado >= intervaloActualizacion) && !pause) {
				imprimirCronometro(&segundos,&minutos);
				ultimoTiempoActualizado = tiempoActual;
		}
		
		if(!btemporal && (segundos == 10 ||segundos==25 || segundos==39)){
			bolatemporal = generarBola(serpiente,ESCENARIO,0x6);
			btemporal = TRUE;
		}
		if(btemporal && (segundos == 14 ||segundos==29 || segundos==43)){
			limpiarBloque(bolatemporal->posicion.x,bolatemporal->posicion.y);
			free(bolatemporal);
			bolatemporal = NULL;
			btemporal = FALSE;
		}


		if(!bmovil && (segundos == 53)){
			bolamovil = generarBola(serpiente, ESCENARIO, 0x4);
			
			Coordenadas c = {bolamovil->posicion.x,bolamovil->posicion.y};
			int distanciaderecha = COLS + OFFSETX - c.x;
			int distanciaizquierda = c.x - OFFSETX;
			int distanciarriba = c.y - OFFSETY;
			int distanciabajo = ROWS + OFFSETY - c.y;
			if(distanciarriba<3 || distanciabajo<3){
				if(distanciabajo<distanciarriba)
					direccionbolamovil = ARRIBA;
				else direccionbolamovil = ABAJO;
				VELOCIDADBOLAMOVIL = 130;
			}else{
				if(distanciaderecha<distanciaizquierda)
					direccionbolamovil=IZQUIERDA;
				else direccionbolamovil=DERECHA;
				VELOCIDADBOLAMOVIL = 100;
			}
			bmovil = TRUE;
		}
		


	}
	
	liberarMemoria(serpiente);
	serpiente = NULL;
	free(bloque);
	bloque = NULL;
	moverCursor(2,ROWS+2);
	system("pause");
	return 0;
}


// ----------- funciones -------------

void liberarMemoria(Serpiente *serpiente){
	Bloque *aux = serpiente->cabeza;
	while(aux != NULL){
		Bloque *temp = aux;
		aux = aux->siguiente;
		free(temp);
	}
	free(serpiente);
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

void pausarReanudarJuego(BOOL *pausa) {
	*pausa = !pausa;
	while (GetAsyncKeyState(VK_SPACE) & 0x8000) 
			Sleep(20); 
	while (pausa) {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			pausa = FALSE;
			while (GetAsyncKeyState(VK_SPACE) & 0x8000)
				Sleep(20);
		}
		Sleep(20);
	}
}