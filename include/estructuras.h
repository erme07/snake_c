#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define ROWS 30
#define COLS 80

enum DIRECCIONES{
	ARRIBA, 
	ABAJO, 
	IZQUIERDA, 
	DERECHA
};

enum ESCENARIOS{
	ESCENARIO1, 
	ESCENARIO2, 
	ESCENARIO3
};

typedef struct coordenadas{
	int x;
	int y;
}Coordenadas;

typedef struct bloque{
	int x;
	int y;
	char valor;
	struct bloque *siguiente;
	struct bloque *anterior;
}Bloque;

typedef struct serpiente{
	Bloque *cabeza;
	int largo;
	Bloque *cola;
}Serpiente;

#endif //ESTRUCTURAS_H