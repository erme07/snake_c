# Nombre del ejecutable
EXECUTABLE=snake

# Directorios
SRC_DIR=./src
INCLUDE_DIR=./include
OBJ_DIR=./obj
RES_DIR=./res

# Archivos de origen
SRC=./main.c $(SRC_DIR)/consola.c $(SRC_DIR)/escenarios.c $(SRC_DIR)/colisiones.c $(SRC_DIR)/menu.c

# Archivos objeto
OBJ=$(OBJ_DIR)/main.o $(OBJ_DIR)/consola.o $(OBJ_DIR)/escenarios.o $(OBJ_DIR)/colisiones.o $(OBJ_DIR)/menu.o

# Compilador
CC=gcc

# Opciones de compilación
CFLAGS=-I$(INCLUDE_DIR) -Wall

# Objetivo por defecto
all: create_dirs $(EXECUTABLE)

# Enlazar ejecutable
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

# Compilar archivos fuente a archivos objeto
$(OBJ_DIR)/main.o: ./main.c $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/escenarios.h $(INCLUDE_DIR)/colisiones.h $(INCLUDE_DIR)/estructuras.h $(INCLUDE_DIR)/menu.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/consola.o: $(SRC_DIR)/consola.c $(INCLUDE_DIR)/consola.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/escenarios.o: $(SRC_DIR)/escenarios.c $(INCLUDE_DIR)/escenarios.h $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/estructuras.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/colisiones.o: $(SRC_DIR)/colisiones.c $(INCLUDE_DIR)/colisiones.h $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/estructuras.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.c $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/consola.h $(INCLUDE_DIR)/estructuras.h $(INCLUDE_DIR)/escenarios.h | create_dirs
	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR)/resource.o: $(RES_DIR)/resource.rc | create_dirs
# 	windres $< -O coff -o $@

# Crear directorios necesarios
create_dirs:
	mkdir -p $(OBJ_DIR)

# Limpiar archivos generados
clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)

.PHONY: all clean create_dirs