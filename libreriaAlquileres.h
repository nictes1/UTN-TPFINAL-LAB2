#ifndef LIBRERIAALQUILERES_H_INCLUDED
#define LIBRERIAALQUILERES_H_INCLUDED

typedef struct nodoAlquiler
{
    stlibros datoLibro;
    lector datosLector;
    fecha fechaAlquiler;

    struct nodoAlquiler * siguiente ;
}nodoAlquiler;

typedef struct
{
    stlibros datoLibroAlquilado;
    lector datosLector;
    fecha fechaAlquiler;
}stRegistroAlquiler;

nodoAlquiler * inicializarListaAlquiler ();
void mostrarAlquilerPendienteDeDevolucion(nodoAlquiler *listaAlquileres, char nombreLectorAbuscar[]);
void mostrarDatosAlquiler(nodoAlquiler *listaAlquileres);
void realizarAlquiler(const char *archivoLectores, const char *archivoLibros, const char *archivoAlquileres, listaGeneros **listaLibros, nodoLector **listaLectores, nodoAlquiler **listaAlquileres);
stRegistroAlquiler crearRegistroAlquiler(stlibros libro, lector lectorEncontrado, fecha fechaAlquiler);
nodoAlquiler *crearNodoAlquiler(const stRegistroAlquiler nuevoAlquiler, nodoAlquiler *listaAlquileres);
void mostrarAlquiler (stRegistroAlquiler dato);
nodoAlquiler *cargarAlquileresDesdeArchivo(const char *nombreArchivo);
void mostrarAlquileres(nodoAlquiler *listaAlquileres);
void mostrarArchivoAlquileres(const char * archivoAlquileres);
int esBisiesto(int anio);
fecha cargarFecha();


#endif // LIBRERIAALQUILERES_H_INCLUDED
