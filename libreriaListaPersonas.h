#ifndef LIBRERIALISTAPERSONAS_H_INCLUDED
#define LIBRERIALISTAPERSONAS_H_INCLUDED
typedef struct
{
    int dia;
    int mes;
    int anio;
} fecha;

typedef struct {

    char nombreYapellido [30];
    int dni;
    int esEstudiante; // 1 � 0
    char email [30];
    char direccion [30];
    int alquiler; // 0 no puede alquilar � 1 puede alquilar
    fecha fechaAlquiler;

}lector;

typedef struct nodoLector
{
    lector info;
    struct nodoLector * sig;

}nodoLector;

lector cargarLector(char nombrelector[]);
int lectorExiste(char nombreLector[], const char *archivoLectores);
void guardarLector(const lector *lectorAGuardar, const char *archivoLectores);
void cargarArchivoLectores(const char *archivoLectores);
nodoLector* buscarNodoLector(nodoLector* lista, const char* nombre);
nodoLector* iniciarLista();
nodoLector* crearNodoLector(lector nuevo);
nodoLector * borrarNodoLector(nodoLector * lista, int dni) ;
void imprimirListaLectores(nodoLector* lista);
void mostrarArchivolectores (const char * archivoLectores);
nodoLector *cargarLectorDesdeArchivo(FILE *archivo);
nodoLector *cargarLectoresDesdeArchivo(const char *nombreArchivo);
void liberarListaLectores(nodoLector *lista);
void insertarOrdenado(nodoLector **lista, nodoLector *nuevoNodo);
void mostrarLector(lector unLector);
void generarLectorRandom(lector *l);
void generarArchivoLectores(const char *filename);
#endif // LIBRERIALISTAPERSONAS_H_INCLUDED
