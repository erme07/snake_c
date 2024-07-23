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
#include "include/cronometro.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

#define FRAMERATE 20 //50fps aprox

void inicializarJuego(Serpiente**,Bloque**,int);
void liberarMemoria(Serpiente*);

int establecerVelocidad(int,int);
int definirNivel(Serpiente*);

void pausarReanudarJuego(BOOL *pausa,DWORD *inicioPausa, DWORD *tiempoPausa);
void gestionarBolaTemporal(Serpiente**,Bloque**,int,BOOL*,int);
Bloque *generarBolaMovil(Serpiente**,int,BOOL*,int,int*,int*);
void actualizarPosicion(Serpiente*, int, int);
BOOL direccionValida(int direccion, int nuevadireccion);

void terminarJuego(BOOL *salir, BOOL *reiniciar);


int main(){
	int MATRIZ[ROWS][COLS];
	int ESCENARIO = ESCENARIO1, reiniciar = FALSE;
	int direccion, direccionbolamovil, VELOCIDAD, VELOCIDADBOLAMOVIL;
	int CICLOS, CICLOSMOVIL, portalH, portalV, puntaje, nivel;
	BOOL game_over,btemporal,bmovil,pause,colision3movil,salir;
	Bloque *bloque, *bolatemporal, *bolamovil;
	DWORD inicioCrono,inicioPausa,tiempoPausa;
	Serpiente *serpiente;
	Tiempo tiempo;
	Coordenadas cola;

	SetConsoleTitle("SNAKE");
	establecerTamanioConsola(740,360);
	eliminarScroll();
	dehabilitarRedimension();
	deshabilitarModoEdicionRapida();
	ocultarCursor();

	srand(time(NULL));
	
	do{
		direccion = IZQUIERDA;
		VELOCIDAD = 100;
		VELOCIDADBOLAMOVIL = 100;
		CICLOS = 0;
		CICLOSMOVIL = 0;
		portalH = 0;
		portalV = 0;
		puntaje = 0;
		nivel = 1;
		game_over = FALSE;
		salir = FALSE;
		btemporal = FALSE;
		bmovil = FALSE;
		pause = FALSE;
		colision3movil = FALSE;
		tiempoPausa = 0;

		serpiente = NULL;
		bloque = NULL;
		bolatemporal = NULL;
		bolamovil = NULL;

		system("cls");

		pintarMarco();
		moverCursor(OFFSETMENUX+9, 3);
		cambiarColorFuente(0x0A);
		printf("SNAKE!");
		cambiarColorFuente(0x0F);
		if(!reiniciar){
			imprimirLogo();
			dibujarEscenario(ESCENARIO1);
			ESCENARIO = seleccionarEscenario();
			if(ESCENARIO==4)
				break;
		}
		establecerMatriz(ESCENARIO,MATRIZ);
		dibujarEscenario(ESCENARIO);
		inicializarJuego(&serpiente,&bloque,ESCENARIO);
		iniciarCronometro(&inicioCrono);

		while(!game_over){
			cola.x = serpiente->cola->posicion.x;
			cola.y = serpiente->cola->posicion.y;

			if(GetAsyncKeyState(VK_UP) & 0x8000){
				if(direccion == ARRIBA)
					VELOCIDAD = 10;
				else if(direccion != ABAJO){
					direccion = ARRIBA;
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
					switch(detectarColisiones(serpiente, bloque,bolatemporal,bolamovil, ESCENARIO)){
						case COLISION_BOLA:
							PlaySound(TEXT("./res/sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
						case COLISION_SERPIENTE:
							PlaySound(TEXT("./res/dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
			if(GetAsyncKeyState(VK_DOWN) & 0x8000) {
				if(direccion == ABAJO)
					VELOCIDAD = 10;
				else if(direccion != ARRIBA){
					direccion = ABAJO;
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
					switch(detectarColisiones(serpiente, bloque,bolatemporal, bolamovil,ESCENARIO)){
						case COLISION_BOLA:
							PlaySound(TEXT("./res/sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
						case COLISION_SERPIENTE:
							PlaySound(TEXT("./res/dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
					switch(detectarColisiones(serpiente, bloque, bolatemporal,bolamovil,ESCENARIO)){
						case COLISION_BOLA:
							PlaySound(TEXT("./res/sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
						case COLISION_SERPIENTE:
							PlaySound(TEXT("./res/dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
			if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
				if(direccion == DERECHA)
					VELOCIDAD = 10;
				else if(direccion != IZQUIERDA){
					direccion = DERECHA;
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
					switch(detectarColisiones(serpiente, bloque,bolatemporal, bolamovil,ESCENARIO)){
						case COLISION_BOLA:
							PlaySound(TEXT("./res/sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
						case COLISION_SERPIENTE:
							PlaySound(TEXT("./res/dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
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

			// aparte -------------------
			if(CICLOS>=VELOCIDAD){
				actualizarCoordenadas(serpiente, direccion);
				moverSerpiente(serpiente);
				switch(detectarColisiones(serpiente, bloque,bolatemporal, bolamovil,ESCENARIO)){
					case COLISION_BOLA:
						PlaySound(TEXT("./res/sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
					case COLISION_SERPIENTE:
						PlaySound(TEXT("./res/dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
				if(game_over)
					continue;
				CICLOS = 0;
			}
			else if(GetAsyncKeyState(VK_SPACE) & 0x8000) {
				estadisticas(serpiente,puntaje,nivel,!pause);
				pausarReanudarJuego(&pause, &inicioPausa, &tiempoPausa);
			}

			// if(bmovil){
			// 	if(bolamovil->anterior!=NULL){
			// 		bmovil = FALSE;
			// 		CICLOSMOVIL = 0;
			// 	}
			// 	else if(CICLOSMOVIL>=VELOCIDADBOLAMOVIL){
			// 		Coordenadas c = moverBloque(direccionbolamovil);
			// 		Coordenadas b;
			// 		Bloque *aux = serpiente->cola;
			// 		bolamovil->posicion.x += c.x;
			// 		bolamovil->posicion.y += c.y;
			// 		b.x= bolamovil->posicion.x;
			// 		b.y= bolamovil->posicion.y;
					
			// 		if(!colision3movil){
			// 			//colision3movil = FALSE;
			// 			limpiarBloque(bolamovil->posicion.x-c.x,bolamovil->posicion.y-c.y);
			// 		}
					
			// 		//colision con escenario
			// 		if(b.x == OFFSETX || b.x == COLS-1+OFFSETX || b.y == OFFSETY || b.y == ROWS-1+OFFSETY){
			// 			bmovil = FALSE;
			// 			free(bolamovil);
			// 			bolamovil = NULL;
			// 		}
			// 		else{
			// 			imprimirBloque(bolamovil);
			// 		}
			// 		while(aux->anterior != NULL){
			// 			if(aux->posicion.x == b.x && aux->posicion.y == b.y){
			// 				moverCursor(b.x, b.y);
			// 				cambiarColorFuente(0x0A);
			// 				printf("O");
			// 				cambiarColorFuente(0x0F);
			// 				colision3movil = TRUE;
			// 				break;
			// 			}else  colision3movil = FALSE;
			// 			aux = aux->anterior;
			// 		}
			// 		if(ESCENARIO==ESCENARIO3){
			// 			if((b.x==9+OFFSETX || b.x==50+OFFSETX) && (b.y >= 7+OFFSETY && b.y <= 12+OFFSETY)){
			// 				cambiarColorFuente(0x0F);
			// 				moverCursor(b.x, b.y);
			// 				printf("%c", 219);
			// 				colision3movil = TRUE;
			// 			}else if((b.y==4+OFFSETY || b.y==15+OFFSETY) && (b.x >= 24+OFFSETX && b.x <= 35+OFFSETX)){
			// 				cambiarColorFuente(0x0F);
			// 				moverCursor(b.x, b.y);
			// 				printf("%c", 219);
			// 				colision3movil = TRUE;
			// 			}else if(!colision3movil)
			// 				colision3movil = FALSE;
			// 		}
					
					
			// 		CICLOSMOVIL = 0;
			// 	}
			// 	else
			// 		CICLOSMOVIL += FRAMERATE;
			// }

			imprimirBloque(bloque);
			Sleep(FRAMERATE);  // Para evitar usar el 100% de la CPU
			CICLOS += FRAMERATE;
			

			nivel = definirNivel(serpiente);
			VELOCIDAD = establecerVelocidad(direccion, nivel);
			estadisticas(serpiente,puntaje,nivel,pause);

			//double tiempoActual = obtenerTiempo();
			//if ((tiempoActual - ultimoTiempoActualizado >= intervaloActualizacion) && !pause) {
			
			imprimirCronometro(&tiempo,inicioCrono,tiempoPausa);
					//ultimoTiempoActualizado = tiempoActual;
			//}

			//si se cumplen las condiciones, se genera una bola temporal
			//gestionarBolaTemporal(&serpiente, &bolatemporal, ESCENARIO, &btemporal, segundos);
			//si se cumplen las condiciones, se genera una bola movil
			// Bloque *resultadoTemporal = generarBolaMovil(&serpiente, ESCENARIO, &bmovil, segundos, &direccionbolamovil, &VELOCIDADBOLAMOVIL);
			// if(resultadoTemporal != NULL)
			// 	bolamovil = resultadoTemporal;


		}
		liberarMemoria(serpiente);
		serpiente = NULL;
		if(bloque!=NULL)
			free(bloque);
		bloque = NULL;
		if(bolatemporal!=NULL)
			free(bolatemporal);
		bolatemporal = NULL;
		if(bolamovil!=NULL)
			free(bolamovil);
		bolamovil = NULL;
		terminarJuego(&salir, &reiniciar);
	} while (game_over && !salir);
	//Fuera del loop

	return 0;
}


// ----------- funciones -------------



void terminarJuego(BOOL *salir, BOOL *reiniciar){
	int op;
	limpiarBuffer();
	imprimirGameOver();
	op=menuGameOver();
	if(op==3){
		*salir = TRUE;
	}
	else if(op==1){
		*reiniciar = TRUE;
		*salir = FALSE;
	}
	else{
		*reiniciar = FALSE;
		*salir = FALSE;
	} 
}

void actualizarPosicion(Serpiente *s, int direccion, int VELOCIDAD) {
	actualizarCoordenadas(s, direccion);
  Sleep(VELOCIDAD);
	moverSerpiente(s); //solo imprime la cabeza
}

void gestionarDireccion(int *direccion,int nuevadireccion,int *VELOCIDAD) {
	if(*direccion==nuevadireccion)
		*VELOCIDAD = 20;//velocidad turbo
	else if (direccionValida(*direccion, nuevadireccion)) {
		*direccion = nuevadireccion;
	}
}

BOOL direccionValida(int direccion, int nuevadireccion) {
	if(nuevadireccion == ARRIBA && direccion == ABAJO)
		return FALSE;
	if(nuevadireccion == ABAJO && direccion == ARRIBA)
		return FALSE;
	if(nuevadireccion == IZQUIERDA && direccion == DERECHA)
		return FALSE;
	if(nuevadireccion == DERECHA && direccion == IZQUIERDA)
		return FALSE;
	return TRUE;
}

Bloque *generarBolaMovil(Serpiente **s, int ESCENARIO, BOOL *bmovil, int segundos, int *direccionbolamovil, int *VELOCIDADBOLAMOVIL){
	if(!(*bmovil) && (segundos == 13 || segundos == 23 || segundos == 33 || segundos == 53)){
			Bloque *bolamovil = generarBola(*s, ESCENARIO, 0x4);
			if (bolamovil == NULL) {
				printf("Error: generarBola devolvió NULL\n");
				return NULL;
			}
			Coordenadas c = {bolamovil->posicion.x,bolamovil->posicion.y};
			int distanciaderecha = COLS + OFFSETX - c.x;
			int distanciaizquierda = c.x - OFFSETX;
			int distanciarriba = c.y - OFFSETY;
			int distanciabajo = ROWS + OFFSETY - c.y;
			if(distanciarriba<3 || distanciabajo<3){
				if(distanciabajo<distanciarriba)
					*direccionbolamovil = ARRIBA;
				else *direccionbolamovil = ABAJO;
				*VELOCIDADBOLAMOVIL = 130;
			}else{
				if(distanciaderecha<distanciaizquierda)
					*direccionbolamovil=IZQUIERDA;
				else *direccionbolamovil=DERECHA;
				*VELOCIDADBOLAMOVIL = 100;
			}
			*bmovil = TRUE;
			return bolamovil;
		}else
			return NULL;
}


void gestionarBolaTemporal(Serpiente **s, Bloque **b ,int ESCEN, BOOL *btemp, int segundos){
	if(!(*btemp) && (segundos == 10 ||segundos==25 || segundos==39)){
		*b = generarBola(*s,ESCEN,0x6);
		*btemp = TRUE;
	}
	if(*btemp && (segundos == 14 ||segundos==29 || segundos==43)){
			limpiarBloque((*b)->posicion.x,(*b)->posicion.y);
			free(*b);
			*b = NULL;
			*btemp = FALSE;
		}
}

void inicializarJuego(Serpiente **s, Bloque **b, int ESCEN){
	
	*s = crearSerpiente();
	*b = generarBola(*s,ESCEN,0x0F);
	inicializarSerpiente(*s);
	imprimirSerpiente(*s);
	borrarLogo();
	cambiarColorFuente(0xE);
	moverCursor(OFFSETMENUX+9, 10);
	printf("00:00");
}

void liberarMemoria(Serpiente *serpiente){
	if(serpiente==NULL)
		return;
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

void pausarReanudarJuego(BOOL *pausa, DWORD *inicioPausa, DWORD *tiempoPausa) {
	*pausa = !(*pausa);
	iniciarPausa(inicioPausa);
	while (GetAsyncKeyState(VK_SPACE) & 0x8000) 
			Sleep(20); 
	while (*pausa) {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			finalizarPausa(*inicioPausa, tiempoPausa);
			*pausa = FALSE;
			while (GetAsyncKeyState(VK_SPACE) & 0x8000)
				Sleep(20);
		}
		Sleep(20);
	}
}