# Snake - Juego clásico hecho con C

Juego de consola realizado con lenguaje c **para windows**.

## Caracteristicas

- Control mediante las teclas direccionales.
- Es posible acelerar la serpiente presionando hacia adelante, según la dirección que posea.
- El nivel del juego aumenta a medida que la serpiente crece.
- La velocidad de la serpiente incrementa en cada nivel.
- Se muestra las distintas estadísticas de la partida.
- Cronometro que marca el tiempo de juego.
- Se puede elegir entre tres mapas.
  - Clásico.
  - Portales (Puedes atravesar los portales interconectados entre sí).
  - Obstáculos (Contiene barreras en el mapa que dificultan el movimiento).
- Hay tres tipos de bolas que otorgan distintos puntos y poseen mayor o menor dificultad para comer:
  - Común, 10 puntos * nivel.
  - Temporal, 25 puntos * nivel (Desaparece luego de 4 segundos).
  - Móvil, 50 puntos * nivel (Se mueve por el mapa antes de desaparecer).
- Sonidos personalizados para cada acción realizada dentro del juego.
- Se puede pausar el juego.
- Menús interactivos para cada instancia del programa.

## Instalación

Después de descargar o clonar el repositorio, se debe compilar el código con GCC. 

#### Usando Makefile
Para usar este método, además de GCC, debe estar disponible la herramienta "Make". Todos los comandos necesarios serán ejecutados de forma automática.
```bash
make snake
```
#### Compilar manualmente
Comandos necesarios para compilar manualmente el proyecto:
```bash
mkdir -p ./obj
gcc -I./include -c main.c -o obj/main.o
gcc -I./include -c src/consola.c -o obj/consola.o
gcc -I./include -c src/escenarios.c -o obj/escenarios.o
gcc -I./include -c src/colisiones.c -o obj/colisiones.o
gcc -I./include -c src/panel.c -o obj/panel.o
gcc -I./include -c src/serpiente.c -o obj/serpiente.o
gcc -I./include -c src/cronometro.c -o obj/cronometro.o
windres res/resource.rc -O coff -o obj/resource.o
gcc -o snake ./obj/main.o ./obj/consola.o ./obj/escenarios.o ./obj/colisiones.o ./obj/panel.o ./obj/serpiente.o ./obj/cronometro.o ./obj/resource.o -I./include -lwinmm
```
