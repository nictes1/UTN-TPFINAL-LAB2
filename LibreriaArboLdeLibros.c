#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include "globals.h"
#include <string.h>
#include <unistd.h>
#include "constants.h"

const char *generos[NUM_GENEROS] = {"Fantasia", "Ciencia Ficcion", "Terror", "Aventura", "Romance"};
const char *titulos[NUM_GENEROS][LIBROS_POR_GENERO] = {
    {"El Hobbit", "Harry Potter y la piedra filosofal", "El nombre del viento", "Juego de Tronos", "El senor de los anillos", "La historia interminable", "Las cronicas de Narnia", "American Gods", "Elric de Melnibone", "La rueda del tiempo"},
    {"Dune", "Neuromante", "El juego de Ender", "Fahrenheit 451", "2001: Una odisea del espacio", "El marciano", "Blade Runner", "Hyperion", "Fundacion", "La guerra de los mundos"},
    {"Dracula", "It", "El exorcista", "La llamada de Cthulhu", "El resplandor", "Frankenstein", "La casa de hojas", "Cementerio de animales", "El silencio de los corderos", "Carrie"},
    {"La isla del tesoro", "Las aventuras de Huckleberry Finn", "Robinson Crusoe", "Viaje al centro de la Tierra", "Los tres mosqueteros", "Moby Dick", "El conde de Montecristo", "La vuelta al mundo en 80 dias", "El ultimo mohicano", "La Odisea"},
    {"Orgullo y prejuicio", "Lo que el viento se llevo", "Romeo y Julieta", "El amor en los tiempos del colera", "Cumbres Borrascosas", "Jane Eyre", "La dama de las camelias", "Los puentes de Madison", "Posdata: Te amo", "El tiempo entre costuras"}
};
const char *autores[NUM_GENEROS][LIBROS_POR_GENERO] = {
    {"J.R.R. Tolkien", "J.K. Rowling", "Patrick Rothfuss", "George R.R. Martin", "J.R.R. Tolkien", "Michael Ende", "C.S. Lewis", "Neil Gaiman", "Michael Moorcock", "Robert Jordan"},
    {"Frank Herbert", "William Gibson", "Orson Scott Card", "Ray Bradbury", "Arthur C. Clarke", "Andy Weir", "Philip K. Dick", "Dan Simmons", "Isaac Asimov", "H.G. Wells"},
    {"Bram Stoker", "Stephen King", "William Peter Blatty", "H.P. Lovecraft", "Stephen King", "Mary Shelley", "Mark Z. Danielewski", "Stephen King", "Thomas Harris", "Stephen King"},
    {"Robert Louis Stevenson", "Mark Twain", "Daniel Defoe", "Julio Verne", "Alexandre Dumas", "Herman Melville", "Alexandre Dumas", "Julio Verne", "James Fenimore Cooper", "Homero"},
    {"Jane Austen", "Margaret Mitchell", "William Shakespeare", "Gabriel Garcia Marquez", "Emily Bronte", "Charlotte Bronte", "Alexandre Dumas (hijo)", "Robert James Waller", "Cecelia Ahern", "Maria Duenas"}
};

stlibros crearLibroEspecifico(const char *titulo, const char *autor, const char *genero, int anio, int cantCopias, float precio) {
    stlibros libro;
    strcpy(libro.titulo, titulo);
    strcpy(libro.autor, autor);
    libro.cantPag = 300;
    strcpy(libro.genero, genero);
    libro.anioLanzamiento = anio;
    libro.Copias.cantCopias = cantCopias;
    libro.Copias.precioAlquiler = precio;
    return libro;
}
nodoGenero *crearNodoGenero(const char *genero, nodoArbolLibro *arbol) {
    nodoGenero *nuevoGenero = (nodoGenero *)malloc(sizeof(nodoGenero));
    strcpy(nuevoGenero->genero, genero);
    nuevoGenero->arbolDeLibros = arbol;
    nuevoGenero->siguiente = NULL;
    return nuevoGenero;
}

void agregarGeneroALista(listaGeneros *lista, nodoGenero *nuevoGenero) {
    if (lista->primero == NULL) {
        lista->primero = nuevoGenero;
    } else {
        nodoGenero *actual = lista->primero;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoGenero;
    }
}

void serializarYGuardarListaGeneros(FILE *archivo, listaGeneros *lista) {
    nodoGenero *generoActual = lista->primero;
    while (generoActual != NULL) {
        nodoArbolLibro *libroActual = generoActual->arbolDeLibros;
        while (libroActual != NULL) {
            fwrite(&(libroActual->dato), sizeof(stlibros), 1, archivo);
            libroActual = libroActual->der;
        }
        generoActual = generoActual->siguiente;
    }
}

void generarArchivoConGenerosYLibros(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    stlibros libro;

     for (int i = 0; i < NUM_GENEROS; i++) {
        for (int j = 0; j < LIBROS_POR_GENERO; j++) {
            libro = crearLibroEspecifico(titulos[i][j], autores[i][j], generos[i], 2000 + j, 5, 50.0);
            fwrite(&libro, sizeof(libro), 1, archivo);
        }
    }


    fclose(archivo);
}



//Crea un libro - carga de datos de forma manual por el usuario
stlibros crearLibro(char nombreLibro[])
{
    stlibros libro;

    strcpy(libro.titulo,nombreLibro);

    printf("Ingrese el autor del libro : ");
    fflush(stdin);
    fgets(libro.autor, sizeof(libro.autor), stdin);
    libro.autor[strcspn(libro.autor, "\n")] = 0;

    printf("Ingrese la cantidad de p�ginas: ");
    scanf("%d", &libro.cantPag);

    printf("Ingrese el g�nero del libro : ");
    fflush(stdin);
    fgets(libro.genero, sizeof(libro.genero), stdin);
    libro.genero[strcspn(libro.genero, "\n")] = 0;

    printf("Ingrese el año de lanzamiento: ");
    scanf("%d", &libro.anioLanzamiento);

    printf("Ingrese el ID interno del libro: ");
    scanf("%d", &libro.idInterno);

    printf("Ingrese la cantidad de copias: ");
    scanf("%d", &libro.Copias.cantCopias);

    printf("Ingrese el precio de alquiler por copia: ");
    scanf("%f", &libro.Copias.precioAlquiler);

    return libro;
}

// Funcion para verificar si un libro ya existe en el archivo
int libroExisteEnArchivo(const char *nombreLibro, const char *archivo) {
    FILE *file = fopen(archivo, "rb");
    if (file == NULL) {
        return 0; // El archivo no est� disponible
    }

    stlibros libro;

    while (fread(&libro, sizeof(stlibros), 1, file) == 1) {
        // Comparar el nombre del libro en el archivo con el nombre proporcionado
        if (strcasecmp(libro.titulo, nombreLibro) == 0) {
            fclose(file);
            return 1; // El libro existe en el archivo
        }
    }

    fclose(file);
    return 0; // No se encontr� el libro en el archivo
}

// Funcion para cargar un libro en el archivo - carga de datos de forma manual por el usuario
void cargarLibroEnArchivo(const char *archivo) {
    char continuar = 's';

    while (continuar == 's' || continuar == 'S') {
        stlibros libro;
        FILE *file = fopen(archivo, "ab");

        if (file == NULL) {
            printf("Error al abrir el archivo de libros.\n");
            return;
        }

        printf("Ingrese el titulo del libro: ");
        fflush(stdin);
        fgets(libro.titulo, sizeof(libro.titulo), stdin);
        libro.titulo[strcspn(libro.titulo, "\n")] = 0;

        if (libroExisteEnArchivo(libro.titulo, archivo)) {
            printf("El libro ya existe en el archivo. No se puede cargar nuevamente.\n");
            fclose(file);
        } else {
            libro = crearLibro(libro.titulo);

            fwrite(&libro, sizeof(stlibros), 1, file);
            fclose(file);
        }

        printf("Desea cargar otro libro? (S/N): ");
        fflush(stdin);
        scanf(" %c", &continuar);
    }
}

//Inicializa la lilsta de libros
nodoArbolLibro *inicializarArbol()
{
    return NULL;
}

//iniciar lista de generos
listaGeneros *inicializarListaGeneros() {
    listaGeneros *nuevaLista = (listaGeneros *)malloc(sizeof(listaGeneros));
    if (nuevaLista != NULL) {
        nuevaLista->primero = NULL; // Inicializa el puntero primero a NULL
    } else {
        printf("Error al asignar memoria para la lista de g�neros.\n");
        // Manejo de errores si no se pudo asignar memoria
    }
    return nuevaLista;
}

//crear nodo de libro - nodo de tipo "stLibros"
nodoArbolLibro *crearNodoArbolLibro(stlibros libro)
{
    nodoArbolLibro *aux = (nodoArbolLibro *)malloc(sizeof(nodoArbolLibro));

    aux->dato = libro;
    aux->izq = NULL;
    aux->der = NULL;

    return aux;
}

//agrega un genero de libro a la lista de generos - lista (generos) de arboles (libros)
void agregarGenero(listaGeneros *lista, const char genero[]) {
    nodoGenero *nuevoGenero = (nodoGenero *)malloc(sizeof(nodoGenero));
    strcpy(nuevoGenero->genero, genero);
    nuevoGenero->arbolDeLibros = inicializarArbol();
    nuevoGenero->siguiente = lista->primero;
    lista->primero = nuevoGenero;
}

//Busca un libro en el arbol de libros por su titulo.
nodoArbolLibro *buscarLibroEnArbol(nodoArbolLibro *arbol, const char * titulo) {
    if (arbol == NULL) {
        return NULL; // El �rbol est� vac�o, no se encontr� el libro
    }

     printf("\nNombre del libro a buscar  dentro del arbol: %s\n",titulo);
     puts("Libro a comprar :\n");
     mostrarLibro(arbol->dato);
     puts("\n");
    int comparacion = strcasecmp(titulo, arbol->dato.titulo);

    if (comparacion == 0) {
        return arbol; // El libro fue encontrado en este nodo
    } else if (comparacion < 0) {
        return buscarLibroEnArbol(arbol->izq, titulo); // Buscar en el sub�rbol izquierdo
    } else {
        return buscarLibroEnArbol(arbol->der, titulo); // Buscar en el sub�rbol derecho
    }
}

nodoArbolLibro* buscarLibroPorTituloEnLista(listaGeneros *listaLibros, char const * libroBuscado) {
    nodoGenero *tempGenero = listaLibros->primero;

    printf("Nombre del libro a buscar dentro de la lista : %s",libroBuscado);

    while (tempGenero != NULL) {
        nodoArbolLibro *libroEncontrado = buscarLibroEnArbol(tempGenero->arbolDeLibros, libroBuscado);
        if (libroEncontrado != NULL) {
            return libroEncontrado;
        }
        tempGenero = tempGenero->siguiente;
    }

    return NULL;
}


// Inserta un nodo ordenado por su cantidad de copias.
nodoArbolLibro *insertarPorCopias(nodoArbolLibro *arbol, nodoArbolLibro *nuevo)
{
    if (arbol == NULL)
    {
        arbol = nuevo;
    }
    else
    {
        if (nuevo->dato.Copias.cantCopias > arbol->dato.Copias.cantCopias)
        {
            arbol->der = insertarPorCopias(arbol->der, nuevo);
        }
        else
        {
            arbol->izq = insertarPorCopias(arbol->izq, nuevo);
        }
    }
    return arbol;
}



// Funcion para mostrar los libros en orden (por identificador interno)
void inorder(nodoArbolLibro *arbol)
{
    if (arbol != NULL)
    {
        inorder(arbol->izq);
        puts("\n");
        mostrarLibro(arbol->dato);
        inorder(arbol->der);
    }
}

//busca un genero de la lista por su nombre - Ideal para mostrar todos los libros de un genero
nodoGenero *buscarGenero(listaGeneros *lista, const char genero[]) {
    nodoGenero *actual = lista->primero;
    while (actual != NULL) {
        if (strcasecmp(actual->genero, genero) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // Genero no encontrado
}

//carga la lista de generos desde archivo .bin con datos de los generos.
listaGeneros *cargarListaDeGenerosDesdeArchivo(const char *nombreArchivo, listaGeneros *listaGeneros) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo de libros.\n");
        return listaGeneros; // Devolver la lista original
    }

    stlibros libro;

    while (fread(&libro, sizeof(stlibros), 1, archivo) == 1) {
        nodoGenero *genero = buscarGenero(listaGeneros, libro.genero);
        if (genero == NULL) {
            // Si el g�nero no existe en la lista, agr�galo
            agregarGenero(listaGeneros, libro.genero);
            genero = listaGeneros->primero;
        }

        // Crea el nodo del �rbol de libros para el libro y agr�galo al g�nero correspondiente
        genero->arbolDeLibros = insertarPorCopias(genero->arbolDeLibros, crearNodoArbolLibro(libro));
    }

    fclose(archivo);

    return listaGeneros; // Devolver la lista modificada
}

//muestra la informacion del archivo de libros.
void mostrarArchivoDeLibros(const char *archivo) {
    FILE *file = fopen(archivo, "rb");

    if (file == NULL) {
        printf("No se pudo abrir el archivo de libros.\n");
        return;
    }

    stlibros libro;

    printf("Libros en el archivo:\n");

    while (fread(&libro, sizeof(stlibros), 1, file) == 1) {

        mostrarLibro(libro);
        puts("\n");
    }

    fclose(file);
}

void mostrarLibro(stlibros libro)
{
    printf("Titulo: %s\n", libro.titulo);
    printf("Autor: %s\n", libro.autor);
    printf("Cantidad de paginas: %d\n", libro.cantPag);
    printf("Genero: %s\n", libro.genero);
    printf("Anio de lanzamiento: %d\n", libro.anioLanzamiento);
    printf("ID interno: %d\n", libro.idInterno);
    printf("Cantidad de copias: %d\n", libro.Copias.cantCopias);
    printf("Precio de alquiler por copia: %.2f\n", libro.Copias.precioAlquiler);
}

//Recorre la lista de generos y muesta los libros ordenados por id. (utiliza funcion inorder(nodoArbolLibro *arbol);)
void recorrerListaDeGeneros(listaGeneros *lista) {
    nodoGenero *actual = lista->primero;

    while (actual != NULL) {
        printf("Genero: %s\n", actual->genero);
        printf("Libros en este genero (ordenados por Cantidad de copias):\n");

        inorder(actual->arbolDeLibros);

        printf("\n");

        actual = actual->siguiente;
    }
}

//agrega un libro a la lista y tambien al archivo con los datos correspondientes a los generos.
void agregarLibroAListaYArchivo(listaGeneros *lista, const char *nombreArchivo) {
    char nombreLibro[20];
    char genero[20];

    printf("Ingrese el titulo del libro: ");
    fflush(stdin);
    fgets(nombreLibro, sizeof(nombreLibro), stdin);
    nombreLibro[strcspn(nombreLibro, "\n")] = 0;

    int existe = libroExisteEnArchivo(lista,nombreLibro);

    if (existe == 1) {
        printf("El libro ya existe en la lista.\n");
        return;
    }

    printf("Ingrese el gwnero del libro: ");
    fflush(stdin);
    fgets(genero, sizeof(genero), stdin);
    genero[strcspn(genero, "\n")] = 0;

    stlibros libroAGuardar = crearLibro(nombreLibro);
    nodoArbolLibro *nuevoNodo = crearNodoArbolLibro(libroAGuardar);

    // Buscar el g�nero en la lista
    nodoGenero *generoEncontrado = buscarGenero(lista, genero);

    if (generoEncontrado == NULL) {
        // Si el g�nero no existe en la lista, agr�galo
        agregarGenero(lista, genero);
        generoEncontrado = lista->primero;
    }

    // Insertar el libro en el �rbol correspondiente al g�nero
    generoEncontrado->arbolDeLibros = insertarPorCopias(generoEncontrado->arbolDeLibros, nuevoNodo);

    FILE *archivo = fopen(nombreArchivo, "ab");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escritura.\n");
        free(nuevoNodo); // Liberar memoria si no se pudo abrir el archivo
        return;
    }

    fwrite(&libroAGuardar, sizeof(libroAGuardar), 1, archivo); // Guardar en el archivo
    fclose(archivo);

    printf("Libro guardado en la lista y en el archivo.\n");
}

// Función para mostrar el árbol completo de libros de un determinado género
void mostrarLibrosPorGenero(listaGeneros *lista, const char *genero) {
    // Buscar el género en la lista
    nodoGenero *generoEncontrado = buscarGenero(lista, genero);

    if (generoEncontrado != NULL) {
        printf("Libros del genero %s:\n", genero);
        inorder(generoEncontrado->arbolDeLibros);
    } else {
        printf("El genero %s no se encuentra en la lista.\n", genero);
    }
}



