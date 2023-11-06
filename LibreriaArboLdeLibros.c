#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include <string.h>
#include <unistd.h>


stlibros crearLibro()
{
    stlibros libro;

    printf("Ingrese el título del libro : ");
    fflush(stdin);
    gets(libro.titulo);

    printf("Ingrese el autor del libro : ");
    fflush(stdin);
    gets(libro.autor);

    printf("Ingrese la cantidad de páginas: ");
    scanf("%d", &libro.cantPag);

    printf("Ingrese el género del libro : ");
    fflush(stdin);
    gets(libro.genero);

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

nodoArbolLibro *inicializarArbol()
{
    return NULL;
}

nodoArbolLibro *crearNodoArbolLibro(stlibros libro)
{
    nodoArbolLibro *aux = (nodoArbolLibro *)malloc(sizeof(nodoArbolLibro));

    aux->dato = libro;
    aux->izq = NULL;
    aux->der = NULL;

    return aux;
}

// Función para buscar un libro por su identificador interno
nodoArbolLibro *buscar(nodoArbolLibro *arbol, int idInterno)
{
    nodoArbolLibro *rta = NULL;

    if (arbol != NULL)
    {
        if (idInterno == arbol->dato.idInterno)
        {
            rta = arbol;
        }
        else if (idInterno > arbol->dato.idInterno)
        {
            rta = buscar(arbol->der, idInterno);
        }
        else
        {
            rta = buscar(arbol->izq, idInterno);
        }
    }

    return rta;
}

// Función para insertar un libro en el árbol teniendo como criterio la cantidad de copias
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



// Función para mostrar los libros en orden (por identificador interno)
void inorder(nodoArbolLibro *arbol)
{
    if (arbol != NULL)
    {
        inorder(arbol->izq);
        printf("ID: %d - Título: %s - Autor: %s\n", arbol->dato.idInterno, arbol->dato.titulo, arbol->dato.autor);
        inorder(arbol->der);
    }
}


int ingresarLibro(celdaGeneros ADA[], int validos, nodoArbolLibro *nuevo)
{
    int pos = buscarPosicionGenero(ADA, validos, nuevo->dato.genero);

    if (pos == -1)
    {
        // El género no existe, así que agregamos uno nuevo
        validos = agregarGenero(ADA, validos, nuevo->dato.genero);
        pos = validos - 1; // La posición es la última, que es la que acabamos de agregar
    }

    // Buscar si el libro ya existe en el árbol del género
    nodoArbolLibro *libroExistente = buscar(nuevo->dato.idInterno, ADA[pos].arbolDeLibros);

    if (libroExistente != NULL)
    {
        // El libro ya existe, preguntar al usuario si quiere agregar más copias
        char respuesta;
        printf("Has ingresado un libro existente, ¿desea cargar más copias? (S/N): ");
        fflush(stdin);
        scanf(" %c", &respuesta);

        if (respuesta == 'S' || respuesta == 's')
        {
            int copiasAgregadas;
            printf("¿Cuántas copias desea agregar?: ");
            scanf("%d", &copiasAgregadas);

            // Aumentar la cantidad de copias del libro existente
            libroExistente->dato.Copias.cantCopias += copiasAgregadas;
        }
    }
    else
    {
        // Insertar el libro en el árbol correspondiente
        ADA[pos].arbolDeLibros = insertarPorCopias(ADA[pos].arbolDeLibros, nuevo);
    }

    return validos;
}


int buscarPosicionGenero (celdaGeneros ADA [],int validos,char genero[])
{
    int rta = -1;
    int i=0;
    while(i< validos && rta == -1)
    {
        if(strcasecmp(ADA[i].genero,genero)==0)
        {
            rta = i;   //si encuentra coincidencia nos devuelve la posicion de la materia en el arreglo
        }              //sino devuelve -1
        i++;
    }

    return rta;
}

int agregarGenero(celdaGeneros ADA[], const char genero[], int validos)
{
    strcpy(ADA[validos].genero, genero);
    ADA[validos].arbolDeLibros = inicializarArbol();
    validos++;

    return validos;
}

int libroExisteEnArchivo(const char *nombreLibro, FILE *archivo) {
    if (archivo == NULL) {
        return 0; // El archivo no está disponible
    }

    stlibros libro;

    while (fread(&libro, sizeof(stlibros), 1, archivo) == 1) {
        // Comparar el nombre del libro en el archivo con el nombre proporcionado
        if (strcmp(libro.titulo, nombreLibro) == 0) {
            return 1; // El libro existe en el archivo
        }
    }

    return 0; // No se encontró el libro en el archivo
}

int cargarArregloDeLibros(celdaGeneros ADA[], int dim, const char* archivo) {
    char mander = 's';
    int validos = 0;
    stlibros aux;
    nodoArbolLibro *nuevo;

    FILE* archivoLibros = fopen(archivo, "wb");

    if (archivoLibros == NULL) {
        printf("Error al abrir el archivo de libros.\n");
        return validos;
    }

    while (mander == 's' && validos < dim) {
        aux = crearLibro();

        // Primero, verifica si el libro ya existe en el archivo
        if (libroExisteEnArchivo(aux.titulo, archivoLibros)) {
            printf("El libro con ID %d ya existe en el archivo. No se puede cargar nuevamente.\n", aux.idInterno);
        } else {
            // Luego, verifica si el libro ya existe en el arreglo en memoria
            if (!libroExisteEnArreglo(aux, ADA, validos)) {
                nuevo = crearNodoArbolLibro(aux);
                validos = ingresarLibro(ADA, validos, nuevo);
            } else {
                printf("El libro con ID %d ya existe en el arreglo en memoria. No se puede cargar nuevamente.\n", aux.idInterno);
            }
        }

        printf("Desea cargar más libros ?\n");
        fflush(stdin);
        scanf(" %c", &mander);
    }

    fclose(archivoLibros);
    return validos;
}


int libroExisteEnArreglo(stlibros libro, celdaGeneros ADA[], int validos) {
    for (int i = 0; i < validos; i++) {
        nodoArbolLibro *arbol = ADA[i].arbolDeLibros;
        if (buscar(arbol, libro.idInterno) != NULL) {
            // El libro ya existe en el arreglo en memoria
            return 1;
        }
    }
    return 0;  // El libro no existe en el arreglo en memoria
}

