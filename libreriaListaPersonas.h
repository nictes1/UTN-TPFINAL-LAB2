#ifndef LIBRERIALISTAPERSONAS_H_INCLUDED
#define LIBRERIALISTAPERSONAS_H_INCLUDED
typedef struct
{
    unsigned int dia;
    unsigned int mes;
    unsigned int anio;
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

lector cargarLector(char nombrelector[]); //Carga un lector manualmente
int lectorExiste(char nombreLector[], const char *archivoLectores); //Verifica la existencia de un lector en el archivo
void guardarLector(const lector *lectorAGuardar, const char *archivoLectores); //Guarda un lector en el archivo
void cargarArchivoLectores(const char *archivoLectores); // Carga usuarios lectores manualmente
nodoLector* buscarNodoLector(nodoLector* lista, const char* nombre); //Busqueda de un lector en la lista de lectores x Nombre
nodoLector* buscarLectorPorDNI(nodoLector* lista, int dniBuscado); // Busqueda de un lector en la lista de lectores x DNI
nodoLector* iniciarLista(); // Inicializar lista de lectores
nodoLector* crearNodoLector(lector nuevo); //Crear un nodo lector
nodoLector * borrarNodoLector(nodoLector * lista, int dni) ; //Borrar un lector de la lista
void imprimirListaLectores(nodoLector* lista); //Imprime la lista de lectores ( Ordenados por DNI)
void mostrarArchivolectores (const char * archivoLectores); //Mostrar Archivo de lectores
nodoLector *cargarLectorDesdeArchivo(FILE *archivo); //Carga un lector desde el archivo a un nodo
nodoLector *cargarLectoresDesdeArchivo(const char *nombreArchivo); //Ordena y crea nodos de lectores en la lista simple
void liberarListaLectores(nodoLector *lista); //Libera la memoria de la lista de lectores
void insertarOrdenado(nodoLector **lista, nodoLector *nuevoNodo); //Inserta los lectores ordenadamente en la lista
void mostrarLector(lector unLector); //Muestra la informacion de un lector en la lista
void generarLectorRandom(lector *l); //Genera un lector automaticamente con datos de la base de datos
void generarArchivoLectores(const char *filename); //Genera un archivo de lectores automaticamente
void escribirArchivoLectores(nodoLector *inicio, const char *nombreArchivo); //Escribe los datos de un lector en la lista de lectores
void modificarLector(lector *l); //Modifica los datos de un lector manualmente

#endif // LIBRERIALISTAPERSONAS_H_INCLUDED
