#include <stdio.h>
#include "../include/escenarios.h"

void escenario_1(){
	moverCursor(OFFSETX, OFFSETY);
	for(int i=0;i<COLS;i++)
		printf("%c",220);
	moverCursor(OFFSETX, ROWS-1 + OFFSETY);
	for(int i=0;i<COLS;i++)
		printf("%c",223);
	for(int i=0;i<ROWS-2;i++){
		moverCursor(OFFSETX, i + OFFSETY + 1);
		printf("%c",219);
	}
	for(int i=0;i<ROWS-2;i++){
		moverCursor(OFFSETX + COLS-1, i + OFFSETY + 1);
		printf("%c",219);
	}
}

void escenario_2(){
	escenario_1();
	moverCursor(25+OFFSETX,OFFSETY);
	cambiarColorFuente(0x1);
	for (int i=0;i<10;i++)
		printf("%c",220);
	moverCursor(25+OFFSETX,ROWS-1 + OFFSETY);
	for (int i=0;i<10;i++)
		printf("%c",223);
	for(int i=0;i<6;i++){
		moverCursor(OFFSETX,i+7+OFFSETY);
		printf("%c",219);
	}
	for(int i=0;i<6;i++){
		moverCursor(COLS-1 + OFFSETX,i+7+OFFSETY);
		printf("%c",219);
	}
	cambiarColorFuente(0x0F);
}

void escenario_3(){
	escenario_2();
	for(int i=0;i<6;i++){
		moverCursor(9+OFFSETX,i+7+OFFSETY);
		printf("%c",219);
	}
	for(int i=0;i<6;i++){
		moverCursor(50+OFFSETX,i+7+OFFSETY);
		printf("%c\n",219);
	}
	moverCursor(24+OFFSETX,4+OFFSETY);
	for(int i=0;i<12;i++)
		printf("%c",219);
	moverCursor(24+OFFSETX,15+OFFSETY);
	for(int i=0;i<12;i++)
		printf("%c",219);
}

void limpiarEscenario(){
	cambiarColorFuente(0x0F);
	moverCursor(25+OFFSETX,OFFSETY);
	//for (int i=0;i<10;i++)
		printf("%c%c%c%c%c%c%c%c%c%c",220,220,220,220,220,220,220,220,220,220);
	moverCursor(25+OFFSETX,ROWS-1 + OFFSETY);
	printf("%c%c%c%c%c%c%c%c%c%c",223,223,223,223,223,223,223,223,223,223);
	for(int i=0;i<6;i++){
		moverCursor(OFFSETX,i+7+OFFSETY);
		printf("%c",219);
	}
	for(int i=0;i<6;i++){
		moverCursor(COLS-1 + OFFSETX,i+7+OFFSETY);
		printf("%c",219);
	}
	for(int i=0;i<6;i++){
		moverCursor(9+OFFSETX,i+7+OFFSETY);
		printf(" ");
		moverCursor(50+OFFSETX,i+7+OFFSETY);
		printf(" ");
	}
	moverCursor(24+OFFSETX,4+OFFSETY);
	//for(int i=0;i<12;i++)
		printf("            ");
	moverCursor(24+OFFSETX,15+OFFSETY);
	//for(int i=0;i<12;i++)
		printf("            ");
}

void dibujarEscenario(int escenario){
	switch(escenario){
		case ESCENARIO1:
			escenario_1();
			break;
		case ESCENARIO2:
			escenario_2();
			break;
		case ESCENARIO3:
			escenario_3();
			break;
	}
}
