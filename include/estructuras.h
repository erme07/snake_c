#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define OFFSETX 			0//26
#define OFFSETMENUX 	28//2
#define OFFSETY 			0
#define ROWS					20
#define COLS 					60

enum DIRECCIONES{
	ARRIBA, 
	ABAJO, 
	IZQUIERDA, 
	DERECHA
};
enum BLOQUES{
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

enum COLISIONES{
	COLISION_BOLA = 1,
	COLISION_BOLATEMP,
	COLISION_BOLAMOVIL,
	COLISION_ESCENARIO,
	COLISION_SERPIENTE,
	COLISION_PORTALV,
	COLISION_PORTALH,
	COLISION_COLAV,
	COLISION_COLAH
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

#endif //ESTRUCTURAS_H