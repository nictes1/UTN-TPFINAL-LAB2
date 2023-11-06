#ifndef LIBRERIALISTAPERSONAS_H_INCLUDED
#define LIBRERIALISTAPERSONAS_H_INCLUDED
typedef struct
{
    int dia;
    int mes;
    int anio;
} fecha;

typedef struct {

    char nombreYapellido [20];
    int dni;
    int esEstudiante; // 1 ó 0
    char email [20];
    char direccion [20];
    int alquiler; // 1 tiene un libro ó 0 no tiene libro
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
nodoLector* buscarNodoLector(nodoLector* lista, char nombre[]);
nodoLector* iniciarLista();
nodoLector* crearNodoLector(lector nuevo);
nodoLector * borrarNodoLector(nodoLector * lista, int dni) ;
void imprimirListaLectores(nodoLector* lista);
void mostrarArchivo (const char * archivoLectores);
nodoLector *cargarLectorDesdeArchivo(FILE *archivo);
nodoLector *cargarLectoresDesdeArchivo(const char *nombreArchivo);
void liberarListaLectores(nodoLector *lista);
void insertarOrdenado(nodoLector **lista, nodoLector *nuevoNodo);


#endif // LIBRERIALISTAPERSONAS_H_INCLUDED
