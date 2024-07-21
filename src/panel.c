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
      cambiarColorFuente(0x0C);
    else
      cambiarColorFuente(0x0A);
    printf("%c Cl%csico",opc1,160);
    moverCursor(OFFSETMENUX+5, 9);
    if(opcion==2)
      cambiarColorFuente(0x0C);
    else
      cambiarColorFuente(0x0A);
    printf("%c Portales",opc2);
    moverCursor(OFFSETMENUX+5, 10);
    if(opcion==3)
      cambiarColorFuente(0x0C);
    else
      cambiarColorFuente(0x0A);
    printf("%c Obst%cculos",opc3,160);
    if(opcion==4)
      cambiarColorFuente(0x0C);
    else
      cambiarColorFuente(0x0A);
    moverCursor(OFFSETMENUX+5, 12);
    printf("%c Salir",opc4);
    moverCursor(OFFSETMENUX+4, 15);
    cambiarColorFuente(0x0A);
    printf("Elija una opcion,");
    moverCursor(OFFSETMENUX+5, 16);
    printf("presione ENTER");
    cambiarColorFuente(0x0F);
    tecla = getch();
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
  pintarMarco();
  moverCursor(OFFSETMENUX+9, 3);
  cambiarColorFuente(0x0A);
  printf("SNAKE!");
  imprimirLogo();
  escenario = menu();
  if(escenario!=4){
    borrarLogo();
    borrarMenu();
  }
  return escenario;
}

void pintarMarco(){
  cambiarColorFuente(0x0F);
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
  cambiarColorFuente(0x0F);
  moverCursor(18+OFFSETX, 8+OFFSETY);
	printf("%c%c%c%c %c%c%c%c %c%c%c%c %c  %c %c%c%c%c",219,219,219,220, 219,219,219,220, 219,219,219,220, 219,219 ,219,219,219,220);
  moverCursor(18+OFFSETX, 9+OFFSETY);
	printf("%c%c%c%c %c  %c %c%c%c%c %c%c%c%c %c%c%c%c",219,220,220,220, 219,219, 219,220,220,219, 219,223,223,220, 219,220,220,220);
  moverCursor(18+OFFSETX, 10+OFFSETY);
	printf("%c%c%c%c %c  %c %c  %c %c  %c %c%c%c%c",220,220,220,219, 219,219, 219,219, 219,219, 219,220,220,220 );
}

void borrarLogo(){
  cambiarColorFuente(0x0F);
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
	printf("██▄ ██▄ ██▄█▄ ██▄  ██▄ █ █ ██▄ ██▄");
	printf("█▄▄ █▄█ █ █ █ █▄▄  █ █ █ █ █▄▄ █▄▀ ");
	printf("█▄█ █ █ █   █ █▄▄  ▀█▀ ▀█▀ █▄▄ █ █");
}

void estadisticas(Serpiente*s,int puntaje,int nivel){
  cambiarColorFuente(0x0F);
  moverCursor(OFFSETMENUX+5, 5);
  printf("Puntaje: ");
	cambiarColorFuente(0xE);
	printf("%d", puntaje);
  moverCursor(OFFSETMENUX+7, 6);
	cambiarColorFuente(0x0F);
  printf("Largo: ");
	cambiarColorFuente(0xE);
	printf("%d", s->largo);
	moverCursor(OFFSETMENUX+7, 7);
	cambiarColorFuente(0xF);
  printf("Nivel: ");
	cambiarColorFuente(0xE);
	printf("%d", nivel);
	cambiarColorFuente(0xF);
	moverCursor(OFFSETMENUX+5, 15);
  printf("%c: 10pts x Nvl", 254);
  moverCursor(OFFSETMENUX+5, 16);
  cambiarColorFuente(0x6);
  printf("%c: 25pts x Nvl", 254);
  moverCursor(OFFSETMENUX+5, 17);
  cambiarColorFuente(0x4);
  printf("%c: 50pts x Nvl", 254);
  cambiarColorFuente(0xF);
	moverCursor(OFFSETMENUX+4, 12);
	printf("pausar/reanudar");
	moverCursor(OFFSETMENUX+7, 13);
	printf("(ESPACIO)");
}