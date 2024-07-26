#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>
#include "include/escenarios.h"
#include "include/consola.h"
#include "include/colisiones.h"
#include "include/estructuras.h"
#include "include/panel.h"
#include "include/serpiente.h"
#include "include/cronometro.h"

void inicializarJuego(Serpiente**,Bola*,int[ROWS][COLS]);
void pausarReanudarJuego(BOOL*,DWORD*,DWORD*);
void terminarJuego(BOOL*,BOOL*);
void liberarMemoria(Serpiente*);
int establecerVelocidad(int);
int definirNivel(Serpiente*);
void actualizarPosicion(Serpiente*,int,int);
void gestionarBolaTemporal(Serpiente**,int,Bola*);
void habilitarBolaMovil(Serpiente **,int,Bolamovil*);
void gestionarBolaMovil(Serpiente**,Bolamovil*,int*,Coordenadas);
void gestionarPortales(Serpiente**,int*,int*);
void detectarBola(Serpiente**,Coordenadas,Bola*,Bola*,Bolamovil*);

//variables globales
int MATRIZ[ROWS][COLS];
int ESCENARIO = ESCENARIO1;
int PUNTAJE = 0, NIVEL = 1;
int VELOCIDAD;

int main(){
	
	int direccion;
	int CICLOS, CICLOSMOVIL, portalH, portalV;
	BOOL game_over,pause,salir,reiniciar = FALSE;
	DWORD inicioCrono,inicioPausa,tiempoPausa;
	Serpiente *serpiente;
	Tiempo tiempo;
	Coordenadas cola;
	Bola bolaComun = {{0,0},COMUN,BLANCO,10,TRUE};
	Bola bolaTemporal = {{0,0},TEMPORAL,DORADO,25,FALSE};
	Bolamovil bolaMovil = {{{0,0},MOVIL,ROJO,50,FALSE},100,0};
	
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
		NIVEL = 1;
		PUNTAJE = 0;
		VELOCIDAD = 100;
		CICLOS = 0;
		CICLOSMOVIL = 0;
		portalH = 0;
		portalV = 0;
		game_over = FALSE;
		salir = FALSE;
		pause = FALSE;
		tiempoPausa = 0;
		serpiente = NULL;

		system("cls");
		pintarMarco();
		moverCursor(OFFSETMENUX+9, 3);
		cambiarColorFuente(AMARILLO);
		printf("SNAKE!");
		cambiarColorFuente(BLANCO);
		if(!reiniciar){
			imprimirLogo();
			dibujarEscenario(ESCENARIO1);
			ESCENARIO = seleccionarEscenario();
			if(ESCENARIO==4)
				break;
		}
		establecerMatriz(ESCENARIO,MATRIZ);
		dibujarEscenario(ESCENARIO);
		inicializarJuego(&serpiente,&bolaComun,MATRIZ);
		iniciarCronometro(&inicioCrono);

		while(!game_over){
			cola.x = serpiente->cola->posicion.x;
			cola.y = serpiente->cola->posicion.y;
			if(bolaMovil.bola.estado)
				gestionarBolaMovil(&serpiente, &bolaMovil, &CICLOSMOVIL,cola);
			
			if(GetAsyncKeyState(FLECHA_ARRIBA) & PRESIONADA){
				if(direccion == ARRIBA)
					VELOCIDAD = 20;
				else if(direccion != ABAJO){
					direccion = ARRIBA;
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
					game_over = (colisionEscenarios(serpiente, ESCENARIO) || colisionSerpiente(serpiente)) ? TRUE : FALSE;
					if(game_over)
						continue;
					if(ESCENARIO == ESCENARIO2 || ESCENARIO == ESCENARIO3)
						gestionarPortales(&serpiente,&portalH,&portalV);
					detectarBola(&serpiente,cola,&bolaComun,&bolaTemporal, &bolaMovil);
					CICLOS = 0;
				}
			}
			if(GetAsyncKeyState(FLECHA_ABAJO) & PRESIONADA) {
				if(direccion == ABAJO)
					VELOCIDAD = 20;
				else if(direccion != ARRIBA){
					direccion = ABAJO;
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
					game_over = (colisionEscenarios(serpiente, ESCENARIO) || colisionSerpiente(serpiente)) ? TRUE : FALSE;
					if(game_over)
						continue;
					if(ESCENARIO == ESCENARIO2 || ESCENARIO == ESCENARIO3)
						gestionarPortales(&serpiente,&portalH,&portalV);
					detectarBola(&serpiente,cola,&bolaComun,&bolaTemporal, &bolaMovil);
					CICLOS = 0;
				}
			}
			if(GetAsyncKeyState(FLECHA_IZQUIERDA) & PRESIONADA) {
				if(direccion == IZQUIERDA)
					VELOCIDAD = 20;
				else if(direccion != DERECHA){
					direccion = IZQUIERDA;
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
					game_over = (colisionEscenarios(serpiente, ESCENARIO) || colisionSerpiente(serpiente)) ? TRUE : FALSE;
					if(game_over)
						continue;
					if(ESCENARIO == ESCENARIO2 || ESCENARIO == ESCENARIO3)
						gestionarPortales(&serpiente,&portalH,&portalV);
					detectarBola(&serpiente,cola,&bolaComun,&bolaTemporal, &bolaMovil);
					CICLOS = 0;
				}
			}
			if(GetAsyncKeyState(FLECHA_DERECHA) & PRESIONADA) {
				if(direccion == DERECHA)
					VELOCIDAD = 20;
				else if(direccion != IZQUIERDA){
					direccion = DERECHA;
					actualizarPosicion(serpiente,direccion,VELOCIDAD);
				game_over = (colisionEscenarios(serpiente, ESCENARIO) || colisionSerpiente(serpiente)) ? TRUE : FALSE;
				if(game_over)
						continue;
				if(ESCENARIO == ESCENARIO2 || ESCENARIO == ESCENARIO3)
					gestionarPortales(&serpiente,&portalH,&portalV);
				detectarBola(&serpiente,cola,&bolaComun,&bolaTemporal, &bolaMovil);
					CICLOS = 0;
				}
			}
			if(CICLOS>=VELOCIDAD){
				actualizarCoordenadas(serpiente, direccion);
				moverSerpiente(serpiente);
				game_over = (colisionEscenarios(serpiente, ESCENARIO) || colisionSerpiente(serpiente)) ? TRUE : FALSE;
				if(game_over)
						continue;
				if(ESCENARIO == ESCENARIO2 || ESCENARIO == ESCENARIO3)
					gestionarPortales(&serpiente,&portalH,&portalV);
				detectarBola(&serpiente,cola,&bolaComun,&bolaTemporal, &bolaMovil);
				CICLOS = 0;
			}
			else if(GetAsyncKeyState(TECLA_ESPACIO) & PRESIONADA) {
				estadisticas(serpiente,PUNTAJE,NIVEL,!pause);
				pausarReanudarJuego(&pause, &inicioPausa, &tiempoPausa);
			}

			Sleep(FRAMERATE);
			CICLOS += FRAMERATE;
			NIVEL = definirNivel(serpiente);
			VELOCIDAD = establecerVelocidad(direccion);

			estadisticas(serpiente,PUNTAJE,NIVEL,pause);
			imprimirCronometro(&tiempo,inicioCrono,tiempoPausa);
			gestionarBolaTemporal(&serpiente, tiempo.segundos ,&bolaTemporal);
			habilitarBolaMovil(&serpiente, tiempo.segundos ,&bolaMovil);
		}

		liberarMemoria(serpiente);
		serpiente = NULL;
		terminarJuego(&salir, &reiniciar);
	} while (game_over && !salir);

	return 0;
}

// ----------- funciones -------------

void inicializarJuego(Serpiente **s,Bola *bolaComun,int MATRIZ[ROWS][COLS]){
	*s = crearSerpiente();
	borrarLogo();
	generarBola(*s,bolaComun,MATRIZ);
	inicializarSerpiente(*s);
	imprimirSerpiente(*s);
	cambiarColorFuente(AMARILLO);
	moverCursor(OFFSETMENUX+9, 10);
	printf("00:00");
}

void pausarReanudarJuego(BOOL *pausa, DWORD *inicioPausa, DWORD *tiempoPausa) {
	*pausa = !(*pausa);
	PlaySound(TEXT("./sound/pausa.wav"), NULL, SND_FILENAME | SND_ASYNC);
	iniciarPausa(inicioPausa);
	while (GetAsyncKeyState(TECLA_ESPACIO) & PRESIONADA) 
			Sleep(20); 
	while (*pausa) {
		if (GetAsyncKeyState(TECLA_ESPACIO) & PRESIONADA) {
			finalizarPausa(*inicioPausa, tiempoPausa);
			*pausa = FALSE;
			while (GetAsyncKeyState(TECLA_ESPACIO) & PRESIONADA)
				Sleep(20);
		}
		Sleep(20);
	}
	PlaySound(TEXT("./sound/pausa.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

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

int establecerVelocidad(int direccion){
	if(NIVEL==1){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 120;
		else return 100;
	}
	if(NIVEL==2){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 100;
		else return 80;
	}
	if(NIVEL==3){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 80;
		else return 60;
	}
	if(NIVEL==4){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 70;
		else return 40;
	}
	if(NIVEL==5){
		if(direccion == ARRIBA || direccion == ABAJO)
			return 40;
		else return 20;
	}
	return 100;
}

int definirNivel(Serpiente*s){
	if(s->largo>=100)
		return 5;
	if(s->largo>=75)
		return 4;
	if(s->largo>=50)
		return 3;
	if(s->largo>=25)
		return 2;
	return 1;
}

void actualizarPosicion(Serpiente *s, int direccion, int VELOCIDAD) {
	actualizarCoordenadas(s, direccion);
  Sleep(VELOCIDAD);
	moverSerpiente(s); //solo imprime la cabeza
}

void gestionarBolaTemporal(Serpiente **s, int segundos,Bola *bola){
	if(!(bola->estado) && (segundos == 10 || segundos==39)){
		generarBolaTemporal(*s,bola,MATRIZ);
		bola->estado = TRUE;
	}
	if(bola->estado && (segundos == 14 || segundos==43)){
		limpiarBloque(bola->posicion.x,bola->posicion.y);
		bola->posicion.x = 0;
		bola->posicion.y = 0;
		MATRIZ[bola->posicion.y-OFFSETY][bola->posicion.x-OFFSETX] = 0;
		bola->estado = FALSE;
	}
}

void habilitarBolaMovil(Serpiente **s, int segundos, Bolamovil *bolamov){
	if(!(bolamov->bola.estado) && (segundos==25||segundos==53)){
		generarBolaMovil(*s,bolamov,MATRIZ);
		Coordenadas c = {bolamov->bola.posicion.x,bolamov->bola.posicion.y};
		int distanciaderecha = COLS + OFFSETX - c.x;
		int distanciaizquierda = c.x - OFFSETX;
		int distanciarriba = c.y - OFFSETY;
		int distanciabajo = ROWS + OFFSETY - c.y;
		if(distanciarriba<3 || distanciabajo<3){
			if(distanciabajo<distanciarriba)
				bolamov->direccion = ARRIBA;
			else bolamov->direccion = ABAJO;
			bolamov->velocidad = 130;
		}else{
			if(distanciaderecha<distanciaizquierda)
				bolamov->direccion=IZQUIERDA;
			else bolamov->direccion=DERECHA;
			bolamov->velocidad = 100;
		}
		bolamov->bola.estado = TRUE;
	}
}

void gestionarBolaMovil(Serpiente **serpiente, Bolamovil *bolaMovil, int *cicloMov,Coordenadas cola){
	if(*cicloMov >= bolaMovil->velocidad){
					Coordenadas c = moverBloque(bolaMovil->direccion);
					BOOL colisionSerpiente = FALSE;
					Coordenadas b;
					Bloque *aux = (*serpiente)->cola;
					if(MATRIZ[bolaMovil->bola.posicion.y-OFFSETY][bolaMovil->bola.posicion.x-OFFSETX] == MOVIL){
						MATRIZ[bolaMovil->bola.posicion.y-OFFSETY][bolaMovil->bola.posicion.x-OFFSETX] = 0;
						limpiarBloque(bolaMovil->bola.posicion.x,bolaMovil->bola.posicion.y);
					}
					bolaMovil->bola.posicion.x += c.x;
					bolaMovil->bola.posicion.y += c.y;
					b.x= bolaMovil->bola.posicion.x;
					b.y= bolaMovil->bola.posicion.y;
					while(aux->anterior != NULL){
						if(aux->posicion.x == b.x && aux->posicion.y == b.y){
							colisionSerpiente = TRUE;
							break;
						}
						aux = aux->anterior;
					}
					if(matrizColision(b,ESCENARIO1)){
						//colision con escenario
						bolaMovil->bola.estado = FALSE;
						bolaMovil->bola.posicion.x = 0;
						bolaMovil->bola.posicion.y = 0;
					}
					else if(b.x == (*serpiente)->cabeza->posicion.x && b.y == (*serpiente)->cabeza->posicion.y){
						//colision con cabeza de la serpiente
						PUNTAJE += bolaMovil->bola.puntos * NIVEL;
						comerBola(*serpiente,cola,MATRIZ);
						PlaySound(TEXT("./sound/movil.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Sleep(VELOCIDAD);
						bolaMovil->bola.estado = FALSE;
						bolaMovil->bola.posicion.x = 0;
						bolaMovil->bola.posicion.y = 0;
					}
					else if(!(ESCENARIO==ESCENARIO3 && matrizColision(b,ESCENARIO3)) && !colisionSerpiente){
						if(MATRIZ[b.y-OFFSETY][b.x-OFFSETX]!=TEMPORAL && MATRIZ[b.y-OFFSETY][b.x-OFFSETX]!=COMUN){
							//si no hay colision, se imprime en la nueva posisicon
							MATRIZ[b.y-OFFSETY][b.x-OFFSETX] = bolaMovil->bola.tipo;
							imprimirBloque(bolaMovil->bola.tipo,b);
						}
					}
					*cicloMov = 0;
				}
				else
					*cicloMov += FRAMERATE;
}

void gestionarPortales(Serpiente**s,int*portalH,int*portalV){
	if(colisionPortal((*s)->cabeza->posicion)){
		if((*s)->cabeza->posicion.x == OFFSETX || (*s)->cabeza->posicion.x == COLS-1+OFFSETX){
			encenderPortalHorizontal();
			(*portalH)+=2;
		}
		else{
			encenderPortalVertical();
			(*portalV)+=2;
		}
		PlaySound(TEXT("./sound/portal.wav"), NULL, SND_FILENAME | SND_ASYNC);
		teletransportar(*s);
		moverSerpiente(*s);
	}
	if(colisionCola((*s)->cola->posicion)){
		if((*s)->cola->posicion.x == OFFSETX+1 || (*s)->cola->posicion.x == COLS-2+OFFSETX){
			if(*portalH>0)
				(*portalH)--;
			if(*portalH==0)
				apagarPortalHorizontal();
		}
		else{
			if(*portalV>0)
				(*portalV)--;
			if(*portalV==0)
				apagarPortalVertical();
		}
	}
}

void detectarBola(Serpiente**s,Coordenadas cola,Bola *bComun,Bola *bTemp, Bolamovil *bMovil){
	int tipoBola = colisionBola(*s,MATRIZ);
	if(tipoBola==COMUN){
		bComun->estado = FALSE;
		bComun->posicion.x = 0;
		bComun->posicion.y = 0;
		PUNTAJE += bComun->puntos * NIVEL;
		PlaySound(TEXT("./sound/comun.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else if(tipoBola==TEMPORAL){
		PUNTAJE += bTemp->puntos * NIVEL;
		bTemp->estado = FALSE;
		bTemp->posicion.x = 0;
		bTemp->posicion.y = 0;
		PlaySound(TEXT("./sound/temporal.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else if(tipoBola==MOVIL){
		PUNTAJE += bMovil->bola.puntos * NIVEL;
		bMovil->bola.estado = FALSE;
		bMovil->bola.posicion.x = 0;
		bMovil->bola.posicion.y = 0;
		PlaySound(TEXT("./sound/movil.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	if(tipoBola==COMUN || tipoBola==TEMPORAL || tipoBola==MOVIL){
		comerBola(*s,cola,MATRIZ);
		Sleep(VELOCIDAD);
	}
	if(tipoBola==COMUN)
		generarBola(*s,bComun,MATRIZ);
}