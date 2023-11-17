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

void generarLectorRandom(lector *l);
void generarArchivoLectores(const char *filename);
// Funcion para cargar un lector desde la entrada estandar
lector cargarLector(char nombrelector[]);
// Funcion para verificar si un lector con el mismo nombre ya existe en un archivo binario
int lectorExiste(char nombreLector[], const char *archivoLectores);
// Funcion para guardar un lector en un archivo binario
void guardarLector(const lector *lectorAGuardar, const char *archivoLectores);
//funcion para agregar lectores al archivo - CARGA MANUAL DE LECTORES
void cargarArchivoLectores(const char *archivoLectores);
nodoLector* buscarNodoLector(nodoLector* lista, const char* nombre); 
//Inicializa la lista del lector
nodoLector* iniciarLista(); 
//crea un nodo de tipo "lector"
nodoLector* crearNodoLector(lector nuevo); 
//Muestra informacion de un lector
void mostrarLector(lector unLector);
//Imprime lista completa de lectores
void imprimirListaLectores(nodoLector* lista);
//Muesta el archivo de lectores
void mostrarArchivolectores (const char * archivoLectores);
//Carga la lista de lectores x Archivo
nodoLector *cargarLectoresDesdeArchivo(const char *nombreArchivo); 
// Funcion para liberar la memoria de la lista de lectores
void liberarListaLectores(nodoLector *lista);
// Funcion para insertar un lector en la lista ordenadamente por DNI
void insertarOrdenado(nodoLector **lista, nodoLector *nuevoNodo);
//Funcion para agregar un nuevo lector ordenado en la lista y en el archivo de lectores
void agregarLectorAListaYArchivo(nodoLector **lista, const char *archivoLectores, lector aGuardar);
//Borra un nodo de lector buscando por su DNI
nodoLector * borrarNodoLector(nodoLector * lista, int dni); 
#endif // LIBRERIALISTAPERSONAS_H_INCLUDED
