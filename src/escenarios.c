#include <stdio.h>
#include "../include/escenarios.h"
#include "../include/consola.h"

void escenario_1(){
	for(int i=0;i<COLS;i++)
		printf("%c",220);
	moverCursor(0,ROWS-1);
	for(int i=0;i<COLS;i++)
		printf("%c",223);
	moverCursor(0,1);
	for(int i=0;i<ROWS-2;i++)
		printf("%c\n",219);
	for(int i=0;i<ROWS-2;i++){
		moverCursor(COLS-1,i+1);
		printf("%c\n",219);
	}
}

void escenario_2(){
	escenario_1();
	moverCursor(35,0);
	cambiarColorFuente(0x1);
	for (int i=0;i<10;i++)
		printf("%c",220);
	moverCursor(35,ROWS-1);
	for (int i=0;i<10;i++)
		printf("%c",223);
	moverCursor(0,11);
	for(int i=0;i<8;i++)
		printf("%c\n",219);
	for(int i=0;i<8;i++){
		moverCursor(COLS-1,i+11);
		printf("%c\n",219);
	}
	cambiarColorFuente(0x0F);
}

void escenario_3(){
	escenario_2();
	moverCursor(13,10);
	for(int i=0;i<10;i++){
		moverCursor(13,i+10);
		printf("%c\n",219);
	}
	moverCursor(66,10);
	for(int i=0;i<10;i++){
		moverCursor(66,i+10);
		printf("%c\n",219);
	}
	moverCursor(27,6);
	for(int i=0;i<26;i++)
		printf("%c",219);
	moverCursor(27,23);
	for(int i=0;i<26;i++)
		printf("%c",219);
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
