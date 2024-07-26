#include <stdio.h>
#include <conio.h>
#include "../include/panel.h"

#define ENTER 13

int menu(){
  int opcion = 1,tecla;
  char opc1=62, opc2=' ', opc3=' ', opc4=' ';
  do{ 
    moverCursor(OFFSETMENUX+5, 8);
    if(opcion==1)
      cambiarColorFuente(DORADO);
    else
      cambiarColorFuente(BLANCO);
    printf("%c Cl%csico",opc1,160);
    moverCursor(OFFSETMENUX+5, 9);
    if(opcion==2)
      cambiarColorFuente(DORADO);
    else
      cambiarColorFuente(BLANCO);
    printf("%c Portales",opc2);
    moverCursor(OFFSETMENUX+5, 10);
    if(opcion==3)
      cambiarColorFuente(DORADO);
    else
      cambiarColorFuente(BLANCO);
    printf("%c Obst%cculos",opc3,160);
    if(opcion==4)
      cambiarColorFuente(ROJO);
    else
      cambiarColorFuente(BLANCO);
    moverCursor(OFFSETMENUX+5, 12);
    printf("%c Salir",opc4);
    moverCursor(OFFSETMENUX+4, 15);
    cambiarColorFuente(AMARILLO);
    printf("Elija una opcion,");
    moverCursor(OFFSETMENUX+5, 16);
    printf("presione ENTER");
    cambiarColorFuente(BLANCO);
    tecla = getch();
    PlaySound(TEXT("./sound/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
    if(tecla==72 && opcion>1){
      opcion--;
    }else if(tecla==80 && opcion<4){
      opcion++;
    }
    if(opcion==1){
      opc1=62;
      opc2=' ';
      opc3=' ';
      opc4=' ';
    }else if(opcion==2){
      if(opc3==62)
        limpiarEscenario();
      opc1=' ';
      opc2=62;
      opc3=' ';
      opc4=' ';
    }else if(opcion==3){
      opc1=' ';
      opc2=' ';
      opc3=62;
      opc4=' ';
    }else if(opcion==4){
      opc1=' ';
      opc2=' ';
      opc3=' ';
      opc4=62;
    }
    dibujarEscenario(opcion);
  } while (tecla != ENTER);
  return opcion;
}

int seleccionarEscenario(){
  int escenario;
  escenario = menu();
  if(escenario!=4){
    borrarLogo();
    borrarMenu();
  }
  return escenario;
}

void pintarMarco(){
  cambiarColorFuente(BLANCO);
  moverCursor(OFFSETMENUX +1, OFFSETY);
	for(int i=0;i<COLSPANEL;i++)
		printf("%c",220);
	moverCursor(OFFSETMENUX +1, ROWS-1 + OFFSETY);
	for(int i=0;i<COLSPANEL;i++)
		printf("%c",223);
	for(int i=0;i<ROWSPANEL-2;i++){
		moverCursor(OFFSETMENUX +1, i + OFFSETY + 1);
		printf("%c",219);
	}
	for(int i=0;i<ROWSPANEL-2;i++){
		moverCursor(COLSPANEL+OFFSETMENUX, i + OFFSETY + 1);
		printf("%c",219);
	}
}

void imprimirLogo(){
  cambiarColorFuente(BLANCO);
  moverCursor(18+OFFSETX, 8+OFFSETY);
	printf("%c%c%c%c %c%c%c%c %c%c%c%c %c  %c %c%c%c%c",219,219,219,220, 219,219,219,220, 219,219,219,220, 219,219 ,219,219,219,220);
  moverCursor(18+OFFSETX, 9+OFFSETY);
	printf("%c%c%c%c %c  %c %c%c%c%c %c%c%c%c %c%c%c%c",219,220,220,220, 219,219, 219,220,220,219, 219,223,223,220, 219,220,220,220);
  moverCursor(18+OFFSETX, 10+OFFSETY);
	printf("%c%c%c%c %c  %c %c  %c %c  %c %c%c%c%c",220,220,220,219, 219,219, 219,219, 219,219, 219,220,220,220 );
}

void borrarLogo(){
  cambiarColorFuente(BLANCO);
  moverCursor(18+OFFSETX, 8+OFFSETY);
	printf("                        ");
  moverCursor(18+OFFSETX, 9+OFFSETY);
	printf("                        ");
  moverCursor(18+OFFSETX, 10+OFFSETY);
	printf("                        ");
}

void borrarMenu(){
  moverCursor(OFFSETMENUX+5, 8);
  printf("         ");
  moverCursor(OFFSETMENUX+5, 9);
  printf("          ");
  moverCursor(OFFSETMENUX+5, 10);
  printf("            ");
  moverCursor(OFFSETMENUX+4, 15);
  printf("                 ");
  moverCursor(OFFSETMENUX+5, 16);
  printf("              ");
}

void imprimirGameOver(){
  moverCursor(OFFSETX+12, 6);
  printf("                                    ");
  moverCursor(OFFSETX+12, 7);
  printf(" %c%c%c %c%c%c %c%c%c%c%c %c%c%c  %c%c%c %c %c %c%c%c %c%c%c ",219,219,220, 219,219,220, 219,219,220,219,220, 219,219,220, 219,219,220, 219,219, 219,219,220, 219,219,220);
  moverCursor(OFFSETX+12, 8);
  printf(" %c%c%c %c%c%c %c %c %c %c%c%c  %c %c %c %c %c%c%c %c%c%c ",219,220,220, 219,220,219, 219,219,219, 219,220,220, 219,219, 219,219, 219,220,220, 219,220,223);
  moverCursor(OFFSETX+12, 9);
  printf(" %c%c%c %c %c %c %c %c %c%c%c  %c%c%c %c%c%c %c%c%c %c %c ",219,220,219, 219,219, 219,219,219, 219,220,220, 223,219,223, 223,219,223, 219,220,220, 219,219);
  moverCursor(OFFSETX+12, 10);
  printf("                                    ");
}

int menuGameOver(){
  int opcion = 1,tecla;
  cambiarColorFuente(BLANCO);
  moverCursor(OFFSETX+17, 12);
  printf("                          ");
  moverCursor(OFFSETX+26, 13);
  printf(" <-  -> ");
  moverCursor(OFFSETX+26, 14);
  printf("        ");
  do{
    moverCursor(OFFSETX+17, 11);
    switch(opcion) {
      case 1:
        cambiarColorFuente(DORADO);
        printf(" reiniciar ");
        cambiarColorFuente(BLANCO);
        printf("| menu | salir ");
        break;
      case 2:
        cambiarColorFuente(BLANCO);
        printf(" reiniciar | ");
        cambiarColorFuente(DORADO);
        printf("menu");
        cambiarColorFuente(BLANCO);
        printf(" | salir ");
        break;
      case 3:
        cambiarColorFuente(BLANCO);
        printf(" reiniciar | menu | ");
        cambiarColorFuente(DORADO);
        printf("salir ");
        break;
    }
    tecla = getch();
    PlaySound(TEXT("./sound/menu.wav"), NULL, SND_FILENAME | SND_ASYNC);
    if(tecla==75 && opcion>1){
      opcion--;
    }else if(tecla==77 && opcion<3){
      opcion++;
    }
  }while(tecla!=ENTER);
  return opcion;
}

void estadisticas(Serpiente*s,int puntaje,int nivel,BOOL pausa){
  cambiarColorFuente(BLANCO);
  moverCursor(OFFSETMENUX+5, 5);
  printf("Puntaje: ");
	cambiarColorFuente(AMARILLO);
	printf("%d", puntaje);
  moverCursor(OFFSETMENUX+7, 6);
	cambiarColorFuente(BLANCO);
  printf("Largo: ");
	cambiarColorFuente(AMARILLO);
	printf("%d", s->largo);
	moverCursor(OFFSETMENUX+7, 7);
	cambiarColorFuente(BLANCO);
  printf("Nivel: ");
	cambiarColorFuente(AMARILLO);
	printf("%d", nivel);
	cambiarColorFuente(BLANCO);
	moverCursor(OFFSETMENUX+5, 15);
  printf("%c: 10pts x Nvl", BOLA);
  moverCursor(OFFSETMENUX+5, 16);
  cambiarColorFuente(DORADO);
  printf("%c: 25pts x Nvl", BOLA);
  moverCursor(OFFSETMENUX+5, 17);
  cambiarColorFuente(ROJO);
  printf("%c: 50pts x Nvl", BOLA);
  cambiarColorFuente(BLANCO);
  moverCursor(OFFSETMENUX+4, 12);
  if(pausa){
    printf("pausar/");
    cambiarColorFuente(DORADO);
    printf("reanudar");
    cambiarColorFuente(BLANCO);
  }else{
    cambiarColorFuente(DORADO);
    printf("pausar");
    cambiarColorFuente(BLANCO);
    printf("/reanudar");
  }
	moverCursor(OFFSETMENUX+7, 13);
	printf("(ESPACIO)");
}