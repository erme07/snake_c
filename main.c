#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define SUP_IZQ 201
#define SUP_DER 187
#define INF_IZQ 200
#define INF_DER 188
#define VERTICAL 186
#define HORIZONTAL 205

#define ROWS 20
#define COLS 60

typedef struct bloque{
	int x;
	int y;
	struct bloque *siguiente;
}Bloque;

typedef struct serpiente{
	Bloque *cabeza;
	int largo;
	Bloque *cola;
}Serpiente;

void printBorder(void);
void moverCursor(int, int);

int main(){
	
	printBorder();
	//moverCursor(1,1);
	getch();
	return 0;
}

void printBorder(){
	int i,j;
	for(i=0;i<ROWS;i++){
		if(i==0){
			for(j=0;j<COLS;j++){
				//if(j>=25 && j<35) printf(" ");
				//else 
					printf("%c",220);
			}
		}else if(i==ROWS-1){
			for(j=0;j<COLS;j++){
				//if(j>=25 && j<35) printf(" ");	
				//else 
					printf("%c",223);
			}
		}else{
			for(j=0;j<COLS;j++){
				//if(j==0 && (i>=7 && i<13)) printf(" ");
				//else if(j==COLS-1 && (i>=7 && i<13)) printf(" ");
				//else 
					if(j==0 || j==COLS-1) printf("%c",219);
				else printf(" ");
			}
		}
		printf("\n");
	}
}

void moverCursor(int row, int col){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = col;
    pos.Y = row;
    SetConsoleCursorPosition(hConsole, pos);
    printf("%c%c",254,254);
}

void imprimirBola(){
	srand(time(NULL));
	int random_number = rand() % 100 + 1; // Numero aleatorio entre 1 y 100
    printf("%d\n", random_number);
}
