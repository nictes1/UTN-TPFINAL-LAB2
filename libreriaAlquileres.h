#ifndef LIBRERIAALQUILERES_H_INCLUDED
#define LIBRERIAALQUILERES_H_INCLUDED

typedef struct nodoAlquiler
{
    stlibros datoLibro;
    lector datosLector;

    struct nodoAlquiler * siguiente ;
}nodoAlquiler;

typedef struct
{
    stlibros datoLibroAlquilado;
    lector datosLector;
}stRegistroAlquiler;


#endif // LIBRERIAALQUILERES_H_INCLUDED
