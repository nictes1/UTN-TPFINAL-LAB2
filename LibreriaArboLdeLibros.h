#ifndef LIBRERIAARBOLDELIBROS_H_INCLUDED
#define LIBRERIAARBOLDELIBROS_H_INCLUDED

//copias de libros
typedef struct
{
    int cantCopias;
    float precioAlquiler;
} stcopias;


//libros
typedef struct
{
    char titulo[60];
    char autor[30];
    int cantPag;
    char genero[30];
    int anioLanzamiento;
    int cantidadaDevecesAlquilado;
    stcopias Copias;
    int estado; // 1 disponible 2 no disponible

} stlibros;

//Arbol de libros
typedef struct nodoArbolLibro
{
    stlibros dato;
    struct nodoArbolLibro * izq;
    struct nodoArbolLibro * der;
} nodoArbolLibro;

//lista de arboles --> lista de generos - arbol de libros
typedef struct nodoGenero {
    char genero[30];
    nodoArbolLibro *arbolDeLibros;
    struct nodoGenero *siguiente;
} nodoGenero;

//Lista de generos
typedef struct listaGeneros {
    nodoGenero *primero;
} listaGeneros;

void mostrarGeneros(listaGeneros *lista); //Funcion para mostrar generos disponibles
void mostrarLibrosDisponiblesEnArbol(nodoArbolLibro *arbol); //Funcion para mostrar libros disponibles dentro de un genero( no dados de baja )
void mostrarLibrosDisponibles(listaGeneros *lista); //Funcion para mostrar todos libros disponibles
void buscarYMostrarLibroEnArbol(nodoArbolLibro *arbol, const char *nombreBuscado); //Fn para buscar y mostrar datos de un libro
void mostrarLibrosPorNombre(listaGeneros *lista, const char *nombreBuscado); ///

nodoArbolLibro *buscarLibroEnArbol(nodoArbolLibro *arbol, const char * titulo); //Funcion para buscar un libro especifico y retornarlo
stlibros crearLibro(char nombreLibro[]); //Funcion para crear un libro manualmente
int libroExisteEnArchivo(const char *nombreLibro, const char *archivo); //Fn para verificar la existencia de un libro en el archivo
void cargarLibroEnArchivo(const char *archivo); //Funcion para cargar un libro al archivo
nodoArbolLibro *inicializarArbol(); //Fn para inicializar un arbol
listaGeneros *inicializarListaGeneros(); //Fn para inicializar una lista de generos
nodoArbolLibro *crearNodoArbolLibro(stlibros libro); //Fn para crear un nodo de libro
void agregarGenero(listaGeneros *lista, const char genero[]); //Fn para crear un genero nuevo
nodoArbolLibro* buscarLibroPorTituloEnLista(listaGeneros *listaLibros, char const * libroBuscado); //Fn para buscar un libro dentro de la lista general
nodoArbolLibro *insertarPorCopias(nodoArbolLibro *arbol, nodoArbolLibro *nuevo); //fn para insetar un libro dentro del arbol ordenadamente
void inorder(nodoArbolLibro *arbol); //Fn para mostrar los libros ordenadamente por cantidad de copias
nodoGenero *buscarGenero(listaGeneros *lista, const char genero[]); //Fn para buscar un genero especifico
listaGeneros *cargarListaDeGenerosDesdeArchivo(const char *nombreArchivo, listaGeneros *listaGeneros); //Fn para cargar los generos desde un archivo
void mostrarArchivoDeLibros(const char *archivo); //Fn para mostrar el archivo de libros
void recorrerListaDeGeneros(listaGeneros *lista); //Fn para recorrer los generos de la lista
listaGeneros* agregarGeneroAListaYArchivo(listaGeneros *lista, const char *archivoLibros); //Fn para crear un libro, un genero o ambos manualmente
void mostrarLibro(stlibros libro); //Fn para mostrar los datos de un libro
void mostrarLibrosPorGenero(listaGeneros *lista, const char *genero); //Fn para mostrar los libros de cada genero
void modificarLibro(nodoGenero *genero, char const *titulo); //Fn para modificar los datos de un libro manualmente
nodoArbolLibro* buscarLibroPorTituloEnGenero(nodoGenero *genero, char const * libroBuscado); //Fn para buscar un libro por titulo en un genero

//Generacion de archivo .bin
void generarArchivoConGenerosYLibros(const char* nombreArchivo); //Fn para generar un archivo  automaticamente con datos de la base de datos
void serializarYGuardarListaGeneros(FILE *archivo, listaGeneros *lista); //Fn para serializar los datos del archivo
listaGeneros* agregarGeneroALista(listaGeneros *lista, const char genero[]); //Fn para agregar generos en la lista
nodoGenero *crearNodoGenero(const char *genero, nodoArbolLibro *arbol); //Fn para crear un nodo genero
stlibros crearLibroEspecifico(const char *titulo, const char *autor, const char *genero, int anio, int cantCopias, float precio, int estado); //Fn para crear un libro con los datos de la base
void modificarEstadoLibro(listaGeneros *lista, const char *nombreLibro, int nuevoEstado, const char *nombreArchivo);//Fn para dar de alta o baja logica a un libro
void escribirArchivoLibros(listaGeneros *lista, const char *nombreArchivo); //Fn para escribir los datos de la lista en un archivo luego de moficicarla

#endif // LIBRERIAARBOLDELIBROS_H_INCLUDED
