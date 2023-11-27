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



nodoAlquiler * inicializarListaAlquiler (); //Fn para inicializar la lista de alquileres
void mostrarAlquilerPendienteDeDevolucion(nodoAlquiler *listaAlquileres, char nombreLectorAbuscar[]); //Fn para buscar un alquiler en especifico y verificar sus datos
void mostrarDatosAlquiler(nodoAlquiler *listaAlquileres); //Fn para recorrer la lista de alquileres pendientes de devolucion en su totalidad
void realizarAlquiler(const char *archivoAlquileres, listaGeneros **listaLibros, nodoLector **listaLectores, nodoAlquiler **listaAlquileres); //Fn para realizar un alquiler
stRegistroAlquiler crearRegistroAlquiler(stlibros libro, lector lectorEncontrado, fecha fechaAlquiler); //Fn para serializar los datos de un alquiler
nodoAlquiler *crearNodoAlquiler(const stRegistroAlquiler nuevoAlquiler, nodoAlquiler *listaAlquileres); //Fn para cargar los campos del nodo lector con la estructura alquiler cargada
void mostrarAlquiler (stRegistroAlquiler dato); //Fn para mostrar los datos de un alquiler
nodoAlquiler *cargarAlquileresDesdeArchivo(const char *nombreArchivo); //Fn para pasar los alquileres del archivo a la lista de alquileres
void mostrarAlquileres(nodoAlquiler *listaAlquileres); //Fn para mostrar la lista de alquileres
void mostrarArchivoAlquileres(const char * archivoAlquileres); //Fn para mostrar el archivo de alquileres
int esBisiesto(int anio); //Fn para saber si un año es biciesto , esto servira para agregar un dia mas al alquiler o no
fecha cargarFecha(); //fn para cargar la fecha de alquiler
void realizarDevolucion(const char *archivoAlquileres, listaGeneros **listaLibros, nodoLector **listaLectores, nodoAlquiler **listaAlquileres); //Fn para realizar la devolucion de un libro alquilado
int diferenciaFechas(fecha alquiler, fecha temp); //fn para calcular los dias de alquiler de un libro
int contarDias(fecha a); //Fn para calcular los dias transcurridos hasta una fecha determinada
nodoAlquiler *buscarAlquiler(nodoAlquiler *listaAlquileres, const char *nombreLector, const char *tituloBuscado); //Fn para buscar un alquiler en especifico
void borrarNodoAlquiler(nodoAlquiler **lista, int dni); //fn para borrar el alquiler realizado de la lista luego de su corresponiente devolucion

#endif // LIBRERIAALQUILERES_H_INCLUDED
