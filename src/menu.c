#include <stdio.h>
#include <conio.h>
#include "../include/menu.h"

#define ENTER 13

int menu(){
  int opcion = 1,tecla;
  char opc1=62, opc2=' ', opc3=' ';
  do{ 
    moverCursor(5, 7);
    if(opcion==1)
      cambiarColorFuente(0x0C);
    else
      cambiarColorFuente(0x0A);
    printf("%c Cl%csico",opc1,160);
    moverCursor(5, 8);
    if(opcion==2)
      cambiarColorFuente(0x0C);
    else
      cambiarColorFuente(0x0A);
    printf("%c Portales",opc2);
    moverCursor(5, 9);
    if(opcion==3)
      cambiarColorFuente(0x0C);
    else
      cambiarColorFuente(0x0A);
    printf("%c Obst%cculos",opc3,160);
    moverCursor(5, 13);
    cambiarColorFuente(0x0A);
    printf("Presione ENTER");
    moverCursor(6, 14);
    printf("para iniciar");
    cambiarColorFuente(0x0F);
    tecla = getch();
    if(tecla==72 && opcion>1){
      opcion--;
    }else if(tecla==80 && opcion<3){
      opcion++;
    }
    if(opcion==1){
      opc1=62;
      opc2=' ';
      opc3=' ';
    }else if(opcion==2){
      opc1=' ';
      opc2=62;
      opc3=' ';
    }else if(opcion==3){
      opc1=' ';
      opc2=' ';
      opc3=62;
    }
    limpiarEscenario();
    dibujarEscenario(opcion);
  } while (tecla != ENTER);
  return opcion;
}

BOOL iniciarJuego(int *escenario){
  int opcion=1;
  pintarMarco();
  moverCursor(9, 3);
  cambiarColorFuente(0x0A);
  printf("SNAKE!");
  imprimirLogo();
  opcion = menu();
  *escenario=opcion;
  borrarLogo();
  borrarMenu();
  return TRUE;
}

void pintarMarco(){
  cambiarColorFuente(0x0F);
  moverCursor(1, OFFSETY);
	for(int i=0;i<COLSPANEL;i++)
		printf("%c",220);
	moverCursor(1, ROWS-1 + OFFSETY);
	for(int i=0;i<COLSPANEL;i++)
		printf("%c",223);
	for(int i=0;i<ROWSPANEL-2;i++){
		moverCursor(1, i + OFFSETY + 1);
		printf("%c",219);
	}
	for(int i=0;i<ROWSPANEL-2;i++){
		moverCursor(COLSPANEL, i + OFFSETY + 1);
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
  moverCursor(5, 7);
  printf("         ");
  moverCursor(5, 8);
  printf("          ");
  moverCursor(5, 9);
  printf("            ");
  moverCursor(5, 13);
  printf("              ");
  moverCursor(6, 14);
  printf("            ");
}