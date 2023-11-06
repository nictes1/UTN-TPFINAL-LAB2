#ifndef LIBRERIAARCHIVO_H_INCLUDED
#define LIBRERIAARCHIVO_H_INCLUDED

typedef struct
{
    lector datoLector;

}stRegistroLectores;

typedef struct
{
    stlibros datoLibro;

}stRegistroLibro;

typedef struct
{
    lector _ALector;
    stlibros _ALibro;

}registroArchivoAlquiler;

#endif // LIBRERIAARCHIVO_H_INCLUDED
