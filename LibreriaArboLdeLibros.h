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

typedef struct
{
   char genero [20];
 	 // "terror", "Ciencia Ficcion"
     // "Comedia", "Romance", etc.
   nodoArbolLibro * arbolDeLibros;
} celdaGeneros;

#endif // LIBRERIAARBOLDELIBROS_H_INCLUDED
