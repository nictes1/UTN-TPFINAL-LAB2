#ifndef LIBRERIAARBOLDELIBROS_H_INCLUDED
#define LIBRERIAARBOLDELIBROS_H_INCLUDED

typedef struct
{
    int cantCopias;
    float precioAlquiler;
} stcopias;

typedef struct
{
    char titulo[20];
    char autor[20];
    int cantPag;
    char genero[20];
    int anioLanzamiento;
    int  idInterno;
    stcopias Copias;

} stlibros;

typedef struct nodoArbolLibro
{
    stlibros dato;
    struct nodoArbolLibro * izq;
    struct nodoArbolLibro * der;
} nodoArbolLibro;

typedef struct nodoGenero {
    char genero[20];
    nodoArbolLibro *arbolDeLibros;
    struct nodoGenero *siguiente;
} nodoGenero;

typedef struct listaGeneros {
    nodoGenero *primero;
} listaGeneros;


stlibros crearLibro(char nombreLibro[]);
int libroExisteEnArchivo(const char *nombreLibro, const char *archivo);
void cargarLibroEnArchivo(const char *archivo);
nodoArbolLibro *inicializarArbol();
listaGeneros *inicializarListaGeneros();
nodoArbolLibro *crearNodoArbolLibro(stlibros libro);
void agregarGenero(listaGeneros *lista, const char genero[]);
nodoArbolLibro *buscar(nodoArbolLibro *arbol, int idInterno);
nodoArbolLibro *insertarPorCopias(nodoArbolLibro *arbol, nodoArbolLibro *nuevo);
void inorder(nodoArbolLibro *arbol);
nodoGenero *buscarGenero(listaGeneros *lista, const char genero[]);
listaGeneros *cargarListaDeGenerosDesdeArchivo(const char *nombreArchivo, listaGeneros *listaGeneros);
void mostrarArchivoDeLibros(const char *archivo);
void recorrerListaDeGeneros(listaGeneros *lista);
void agregarLibroAListaYArchivo(listaGeneros *lista, const char *nombreArchivo);

#endif // LIBRERIAARBOLDELIBROS_H_INCLUDED
