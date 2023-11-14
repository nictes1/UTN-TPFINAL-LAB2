#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include <string.h>
#include <unistd.h>

//Crea un libro - carga de datos de forma manual por el usuario
stlibros crearLibro(char nombreLibro[])
{
    stlibros libro;

    strcpy(libro.titulo,nombreLibro);

    printf("Ingrese el autor del libro : ");
    fflush(stdin);
    gets(libro.autor);

    printf("Ingrese la cantidad de p�ginas: ");
    scanf("%d", &libro.cantPag);

    printf("Ingrese el g�nero del libro : ");
    fflush(stdin);
    gets(libro.genero);

    printf("Ingrese el a�o de lanzamiento: ");
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
        if (strcmp(libro.titulo, nombreLibro) == 0) {
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

        printf("Ingrese el t�tulo del libro: ");
        fflush(stdin);
        gets(libro.titulo);

        if (libroExisteEnArchivo(libro.titulo, archivo)) {
            printf("El libro ya existe en el archivo. No se puede cargar nuevamente.\n");
            fclose(file);
        } else {
            libro = crearLibro(libro.titulo);

            fwrite(&libro, sizeof(stlibros), 1, file);
            fclose(file);

            printf("�Desea cargar otro libro? (S/N): ");
            fflush(stdin);
            scanf(" %c", &continuar);
        }
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

    int comparacion = strcmp(titulo, arbol->dato.titulo);

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
        printf("ID: %d - T�tulo: %s - Autor: %s\n", arbol->dato.idInterno, arbol->dato.titulo, arbol->dato.autor);
        inorder(arbol->der);
    }
}

//busca un genero de la lista por su nombre.
nodoGenero *buscarGenero(listaGeneros *lista, const char genero[]) {
    nodoGenero *actual = lista->primero;
    while (actual != NULL) {
        if (strcmp(actual->genero, genero) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // G�nero no encontrado
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
        printf("T�tulo: %s\n", libro.titulo);
        printf("Autor: %s\n", libro.autor);
        printf("Cantidad de p�ginas: %d\n", libro.cantPag);
        printf("G�nero: %s\n", libro.genero);
        printf("A�o de lanzamiento: %d\n", libro.anioLanzamiento);
        printf("ID interno: %d\n", libro.idInterno);
        printf("Cantidad de copias: %d\n", libro.Copias.cantCopias);
        printf("Precio de alquiler por copia: %.2f\n", libro.Copias.precioAlquiler);
        printf("\n");
    }

    fclose(file);
}

//Recorre la lista de generos y muesta los libros ordenados por id. (utiliza funcion inorder(nodoArbolLibro *arbol);)
void recorrerListaDeGeneros(listaGeneros *lista) {
    nodoGenero *actual = lista->primero;

    while (actual != NULL) {
        printf("G�nero: %s\n", actual->genero);
        printf("Libros en este g�nero (ordenados por Cantidad de copias):\n");

        inorder(actual->arbolDeLibros);

        printf("\n");

        actual = actual->siguiente;
    }
}

//agrega un libro a la lista y tambien al archivo con los datos correspondientes a los generos.
void agregarLibroAListaYArchivo(listaGeneros *lista, const char *nombreArchivo) {
    char nombreLibro[20];
    char genero[20];

    printf("Ingrese el t�tulo del libro: ");
    fflush(stdin);
    gets(nombreLibro);

    int existe = libroExisteEnArchivo(lista,nombreLibro);

    if (existe == 1) {
        printf("El libro ya existe en la lista.\n");
        return;
    }

    printf("Ingrese el g�nero del libro: ");
    fflush(stdin);
    gets(genero);

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


