# Nombre del ejecutable final
TARGET = tpfinal

# Compilador a usar
CC = gcc

# Opciones de compilación, por ejemplo, -Wall para mostrar advertencias
CFLAGS = -Wall

# Lista de archivos fuente
SRC = main.c LibreriaArboLdeLibros.c libreriaListaPersonas.c libreriaAlquileres.c

OBJ = $(SRC:.c=.o)

# Regla por defecto
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
