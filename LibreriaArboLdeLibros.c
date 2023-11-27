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

stlibros crearLibroEspecifico(const char *titulo, const char *autor, const char *genero, int anio, int cantCopias, float precio, int estado) {
    stlibros libro;
    strcpy(libro.titulo, titulo);
    strcpy(libro.autor, autor);
    libro.cantPag = 300;
    strcpy(libro.genero, genero);
    libro.anioLanzamiento = anio;
    libro.Copias.cantCopias = cantCopias;
    libro.Copias.precioAlquiler = precio;
    libro.estado = estado;
    return libro;
}
nodoGenero *crearNodoGenero(const char *genero, nodoArbolLibro *arbol) {
    nodoGenero *nuevoGenero = (nodoGenero *)malloc(sizeof(nodoGenero));
    strcpy(nuevoGenero->genero, genero);
    nuevoGenero->arbolDeLibros = arbol;
    nuevoGenero->siguiente = NULL;
    return nuevoGenero;
}

listaGeneros* agregarGeneroALista(listaGeneros *lista, const char genero[]) {
    nodoGenero *nuevoGenero = (nodoGenero *)malloc(sizeof(nodoGenero));
    strcpy(nuevoGenero->genero, genero);
    nuevoGenero->arbolDeLibros = inicializarArbol();
    nuevoGenero->siguiente = lista->primero;

    lista->primero = nuevoGenero;
    return lista;
}


void mostrarGeneros(listaGeneros *lista) {
    nodoGenero *actual = lista->primero;
    printf("Lista de Generos:\n");
    while (actual != NULL) {
        printf("%s\n", actual->genero);
        actual = actual->siguiente;
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
            libro = crearLibroEspecifico(titulos[i][j], autores[i][j], generos[i], 2000 + j, 5, 50.0, 1);
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

    printf("Ingrese la cantidad de paginas: ");
    scanf("%d", &libro.cantPag);

    printf("Ingrese el genero del libro : ");
    fflush(stdin);
    fgets(libro.genero, sizeof(libro.genero), stdin);
    libro.genero[strcspn(libro.genero, "\n")] = 0;

    printf("Ingrese el año de lanzamiento: ");
    scanf("%d", &libro.anioLanzamiento);

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
        printf("Error al asignar memoria para la lista de generos.\n");
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
        return NULL; // El arbol esta vacio, no se encontro el libro
    }

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

    while (tempGenero != NULL) {
        nodoArbolLibro *libroEncontrado = buscarLibroEnArbol(tempGenero->arbolDeLibros, libroBuscado);
        if (libroEncontrado != NULL) {
            return libroEncontrado;
        }
        tempGenero = tempGenero->siguiente;
    }

    return NULL;
}


nodoArbolLibro *insertarPorNombre(nodoArbolLibro *arbol, nodoArbolLibro *nuevo) {
    if (arbol == NULL) {
        arbol = nuevo;
    } else {
        if (strcasecmp(nuevo->dato.titulo, arbol->dato.titulo) > 0) {
            arbol->der = insertarPorNombre(arbol->der, nuevo);
        } else {
            arbol->izq = insertarPorNombre(arbol->izq, nuevo);
        }
    }
    return arbol;
}


// Funcion para mostrar los libros en orden
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
            // Si el genero no existe en la lista, agregalo
            agregarGenero(listaGeneros, libro.genero);
            genero = listaGeneros->primero;
        }

        // Crea el nodo del �rbol de libros para el libro y agr�galo al g�nero correspondiente
        genero->arbolDeLibros = insertarPorNombre(genero->arbolDeLibros, crearNodoArbolLibro(libro));
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
    printf("Cantidad de copias: %d\n", libro.Copias.cantCopias);
    printf("Precio de alquiler por copia: %.2f\n", libro.Copias.precioAlquiler);
    printf("Estado del libro: %s\n", libro.estado ? "Disponible" : "No disponible");
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

listaGeneros* agregarGeneroAListaYArchivo(listaGeneros *lista, const char *archivoLibros) {
    char nombreLibro[20];
    char genero[20];

    printf("Ingrese el titulo del libro: ");
    fflush(stdin);
    fgets(nombreLibro, sizeof(nombreLibro), stdin);
    nombreLibro[strcspn(nombreLibro, "\n")] = 0;

    int existe = libroExisteEnArchivo(&nombreLibro, archivoLibros);

    if (existe == 0) {  // Si el libro no se encontraba en el archivo

        stlibros libroAGuardar = crearLibro(nombreLibro);
        nodoArbolLibro *nuevoNodo = crearNodoArbolLibro(libroAGuardar);

        strcpy(genero, nuevoNodo->dato.genero);
        printf("Genero a buscar : %s", genero);

        // Buscar el genero en la lista
        nodoGenero *generoEncontrado = buscarGenero(lista, genero);

        if (generoEncontrado == NULL) {
            puts("Genero no encontrado\n");
            generoEncontrado = crearNodoGenero(genero, nuevoNodo);
            lista = agregarGeneroALista(lista, generoEncontrado);
            generoEncontrado = buscarGenero(lista, genero);
            generoEncontrado->arbolDeLibros = insertarPorNombre(generoEncontrado->arbolDeLibros,nuevoNodo);
        } else {
            // Insertar el libro en el árbol correspondiente al género
            generoEncontrado->arbolDeLibros = insertarPorNombre(generoEncontrado->arbolDeLibros, nuevoNodo);
        }

        FILE *archivo = fopen(archivoLibros, "ab");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo para escritura.\n");
            free(nuevoNodo); // Liberar memoria si no se pudo abrir el archivo
            return lista;
        }

        fwrite(&libroAGuardar, sizeof(libroAGuardar), 1, archivo); // Guardar en el archivo
        fclose(archivo);

        printf("Libro guardado en la lista y en el archivo.\n");

    } else {
        printf("El libro ya existe en la lista.\n");
    }

    return lista;
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

// Función para modificar el estado de un libro por su título
void modificarEstadoLibro(listaGeneros *lista, const char *nombreLibro, int nuevoEstado, const char *nombreArchivo) {
    // Buscar el libro en la lista
    nodoArbolLibro *libroEncontrado = buscarLibroPorTituloEnLista(lista, nombreLibro);

    if (libroEncontrado != NULL) {
        // Modificar el estado del libro
        libroEncontrado->dato.estado = nuevoEstado;

        // Actualizar el archivo con la nueva información
        FILE *archivo = fopen(nombreArchivo, "rb+");

        if (archivo == NULL) {
            printf("No se pudo abrir el archivo para modificar el estado del libro.\n");
            return;
        }

        // Buscar la posición del libro en el archivo
        fseek(archivo, -sizeof(stlibros), SEEK_CUR);
        fwrite(&(libroEncontrado->dato), sizeof(stlibros), 1, archivo);

        fclose(archivo);

        printf("Estado del libro \"%s\" modificado correctamente.\n", nombreLibro);
    } else {
        printf("El libro \"%s\" no se encuentra en la lista.\n", nombreLibro);
    }
}

void mostrarLibrosDisponibles(listaGeneros *lista) {
    nodoGenero *generoActual = lista->primero;
    while (generoActual != NULL) {
        puts("\n");
        printf("Genero: %s\n", generoActual->genero);
        mostrarLibrosDisponiblesEnArbol(generoActual->arbolDeLibros);
        generoActual = generoActual->siguiente;
    }
}

void mostrarLibrosDisponiblesEnArbol(nodoArbolLibro *arbol) {
    if (arbol != NULL) {
        mostrarLibrosDisponiblesEnArbol(arbol->izq);
        if (arbol->dato.estado == 1) {
            printf("Titulo: %s\n", arbol->dato.titulo);
        }
        mostrarLibrosDisponiblesEnArbol(arbol->der);
    }
}

void mostrarLibrosPorNombre(listaGeneros *lista, const char *nombreBuscado) {
    nodoGenero *generoActual = lista->primero;
    while (generoActual != NULL) {
        buscarYMostrarLibroEnArbol(generoActual->arbolDeLibros, nombreBuscado);
        generoActual = generoActual->siguiente;
    }
}

void buscarYMostrarLibroEnArbol(nodoArbolLibro *arbol, const char *nombreBuscado) {
    if (arbol != NULL) {
        buscarYMostrarLibroEnArbol(arbol->izq, nombreBuscado);
        if (strcasecmp(arbol->dato.titulo, nombreBuscado) == 0) {
            mostrarLibro(arbol->dato);
        }
        buscarYMostrarLibroEnArbol(arbol->der, nombreBuscado);
    }
}

void escribirArchivoLibros(listaGeneros *lista, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "wb"); // Abre el archivo en modo escritura binaria

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    nodoGenero *actualGenero = lista->primero;

    while (actualGenero != NULL) {
        nodoArbolLibro *actualLibro = actualGenero->arbolDeLibros;

        while (actualLibro != NULL) {
            // Escribe el libro en el archivo
            fwrite(&(actualLibro->dato), sizeof(stlibros), 1, archivo);

            actualLibro = actualLibro->der;
        }

        actualGenero = actualGenero->siguiente;
    }

    fclose(archivo); // Cierra el archivo
}

nodoArbolLibro* buscarLibroPorTituloEnGenero(nodoGenero *genero, char const * libroBuscado) {
    if (genero == NULL) {
        return NULL;
    }

    return buscarLibroEnArbol(genero->arbolDeLibros, libroBuscado);
}

// Función para modificar un campo específico del libro
void modificarLibro(nodoGenero *genero, char const *titulo) {
    printf("Libro a modificar : %s\n",titulo);
    nodoArbolLibro *libro = buscarLibroPorTituloEnGenero(genero, titulo);
    mostrarLibro(libro->dato);
     if (libro != NULL) {
        int opcion;
        printf("¿Que campo deseas modificar?\n");
        printf("1. Titulo\n");
        printf("2. Autor\n");
        printf("3. Cantidad de paginas\n");
        printf("4. Genero\n");
        printf("5. Anio de lanzamiento\n");
        printf("6. Cantidad de veces alquilado\n");
        printf("7. Cantidad de copias\n");
        printf("8. Precio de alquiler\n");
        printf("9. Volver\n");

        printf("Ingresa el número de la opción: ");
        opcion = leerOpcion();

        char buffer[100];

        switch (opcion) {
            case 1:
                printf("Ingresa el nuevo título: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0; // Eliminar el carácter de nueva línea
                strncpy(libro->dato.titulo, buffer, sizeof(libro->dato.titulo));
                break;
            case 2:
                printf("Ingresa el nuevo autor: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                strncpy(libro->dato.autor, buffer, sizeof(libro->dato.autor));
                break;
            case 3:
                printf("Ingresa la nueva cantidad de páginas: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                libro->dato.cantPag = atoi(buffer);
                break;
            case 4:
                printf("Ingresa el nuevo género: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                strncpy(libro->dato.genero, buffer, sizeof(libro->dato.genero));
                break;
            case 5:
                printf("Ingresa el nuevo año de lanzamiento: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                libro->dato.anioLanzamiento = atoi(buffer);
                break;
            case 6:
                printf("Ingresa la nueva cantidad de veces alquilado: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                libro->dato.cantidadaDevecesAlquilado = atoi(buffer);
                break;
            case 7:
                printf("Ingresa la nueva cantidad de copias: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                libro->dato.Copias.cantCopias = atoi(buffer);
                break;
            case 8:
                printf("Ingresa el nuevo precio de alquiler: ");
                fflush(stdin);
                fgets(buffer, sizeof(buffer), stdin);
                libro->dato.Copias.precioAlquiler = atof(buffer);
                break;
            case 9:
                printf("Volviendo\n");
                sleep(1);
                break;
            default:
                printf("Opción no válida.\n");
        }
    } else {
        printf("Libro no encontrado.\n");
    }
}
