#ifndef LIBRERIAALQUILERES_H_INCLUDED
#define LIBRERIAALQUILERES_H_INCLUDED

typedef struct
{
    stlibros datoLibroAlquilado;
    lector datosLector;
    fecha fechaAlquiler;
}stRegistroAlquiler;

typedef struct nodoAlquiler
{
    stRegistroAlquiler alquiler;
    struct nodoAlquiler * siguiente ;
}nodoAlquiler;



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
void realizarDevolucion(const char *archivoLectores, const char *archivoLibros, const char *archivoAlquileres, listaGeneros **listaLibros, nodoLector **listaLectores, nodoAlquiler **listaAlquileres);
int diferenciaFechas(fecha alquiler, fecha temp);
int contarDias(fecha a);
nodoAlquiler *buscarAlquiler(nodoAlquiler *listaAlquileres, const char *nombreLector, const char *tituloBuscado);
void borrarNodoAlquiler(nodoAlquiler **lista, int dni);

#endif // LIBRERIAALQUILERES_H_INCLUDED
