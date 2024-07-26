
#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <windows.h>

#define FRAMERATE			20 //50fps
#define ROWS					20
#define COLS 					60

#define OFFSETX 			26
#define OFFSETMENUX 	2
#define OFFSETY 			0

#define FLECHA_ARRIBA			VK_UP
#define FLECHA_ABAJO			VK_DOWN
#define FLECHA_IZQUIERDA	VK_LEFT
#define FLECHA_DERECHA		VK_RIGHT
#define TECLA_ESPACIO			VK_SPACE
#define PRESIONADA				0x8000

#define BLANCO				0x0F
#define VERDE 				0x0A
#define ROJO 					0x0C
#define ROJO_INTENSO	0x04
#define AMARILLO 			0x0E
#define DORADO 				0x06
#define CELESTE 			0x01
#define CELESTE_INT 	0x09

#define BOLA 254

enum DIRECCIONES{
	ARRIBA, 
	ABAJO, 
	IZQUIERDA, 
	DERECHA
};

enum BOLAS{
	COMUN = 4,
	TEMPORAL,
	MOVIL,
	CUERPO
};

enum ESCENARIOS{
	ESCENARIO1 = 1, 
	ESCENARIO2, 
	ESCENARIO3
};

typedef struct coordenadas{
	int x;
	int y;
}Coordenadas;

typedef struct tiempo{
	int minutos;
	int segundos;
}Tiempo;

typedef struct bloque{
	Coordenadas posicion;
	char valor;
	int color;
	struct bloque *siguiente;
	struct bloque *anterior;
}Bloque;

typedef struct serpiente{
	Bloque *cabeza;
	int largo;
	Bloque *cola;
}Serpiente;

typedef struct bola{
	Coordenadas posicion;
	int tipo;
	int color;
	int puntos;
	BOOL estado;
}Bola;

typedef struct bolamovil{
	Bola bola;
	int velocidad;
	int direccion;
}Bolamovil;

#endif //ESTRUCTURAS_H