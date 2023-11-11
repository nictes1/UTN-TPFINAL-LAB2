#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include <string.h>
#include <unistd.h>

// Función para cargar un lector desde la entrada estándar
lector cargarLector(char nombrelector[])
{
    lector nuevoLector;

    strcpy(nuevoLector.nombreYapellido, nombrelector);

    printf("Ingrese el DNI: ");
    scanf("%d", &nuevoLector.dni);

    printf("Es estudiante (1 para sí, 0 para no): ");
    scanf("%d", &nuevoLector.esEstudiante);

    printf("Ingrese el email: ");
    scanf("%s", nuevoLector.email);

    printf("Ingrese la dirección: ");
    scanf("%s", nuevoLector.direccion);

    nuevoLector.alquiler = 1;

    return nuevoLector;
}

// Función para verificar si un lector con el mismo nombre ya existe en un archivo binario
int lectorExiste(char nombreLector[], const char *archivoLectores)
{
    FILE *archivo = fopen(archivoLectores, "rb");
    if (archivo == NULL)
    {
        return 0; // El archivo no existe
    }

    lector lectorActual;
    while (fread(&lectorActual, sizeof(lectorActual), 1, archivo))
    {
        if (strcmp(lectorActual.nombreYapellido, nombreLector) == 0)
        {
            fclose(archivo);
            return 1; // El lector ya existe en el archivo
        }
    }

    fclose(archivo);
    return 0; // El lector no existe en el archivo
}

// Función para guardar un lector en un archivo binario
void guardarLector(const lector *lectorAGuardar, const char *archivoLectores)
{
    FILE *archivo = fopen(archivoLectores, "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    fwrite(lectorAGuardar, sizeof(*lectorAGuardar), 1, archivo);
    fclose(archivo);
}



void cargarArchivoLectores(const char *archivoLectores)
{
    FILE *archivo = fopen(archivoLectores, "ab");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    char mander = 's';
    int existeLector = 0;
    lector lectorAGuardar;

    while (mander == 's')
    {
        char nombre[20];
        printf("Ingrese el nombre del Lector: ");
        fflush(stdin);
        gets(nombre);
        existeLector = lectorExiste(nombre, archivoLectores);

        if (existeLector != 1)
        {
            lectorAGuardar = cargarLector(nombre);
            // Verificar nuevamente antes de guardar
            if (lectorExiste(nombre, archivoLectores) != 1)
            {
                guardarLector(&lectorAGuardar, archivoLectores);
                printf("Lector guardado en el archivo.\n");
            }
        }
        else
        {
            printf("El lector ya existe en el archivo.\n");
        }

        printf("Presione S para cargar otro lector: ");
        fflush(stdin);
        scanf(" %c", &mander);
    }

    fclose(archivo);
}


nodoLector* buscarNodoLector(nodoLector* lista, char nombre[])
{
    nodoLector* seg = lista;

    while ((seg != NULL) && strcasecmp(seg->info.nombreYapellido,nombre)!=0) {
        seg = seg->sig;
    }

    return seg;
}



nodoLector* iniciarLista() {
    return NULL;
}

nodoLector* crearNodoLector(lector nuevo) {
    nodoLector* auxiliar = (nodoLector*)malloc(sizeof(nodoLector));
    auxiliar->info = nuevo;
    auxiliar->sig = NULL;

    return auxiliar;
}



nodoLector * borrarNodoLector(nodoLector * lista, int dni) {
    nodoLector * seg;
    nodoLector * ante = NULL; // Apunta al nodo anterior a 'seg'.

    if (lista != NULL && lista->info.dni == dni) {
        nodoLector * aux = lista;
        lista = lista->sig; // Saltear el primer nodo.
        free(aux);         // Eliminar el primer nodo.
    } else {
        seg = lista;
        while (seg != NULL && seg->info.dni != dni) {
            ante = seg;          // Adelantar una posición la variable 'ante'.
            seg = seg->sig;      // Avanzar al siguiente nodo.
        }
        // En este punto, 'ante' contiene la dirección del nodo anterior al buscado, y 'seg'
        // contiene la dirección del nodo que quieres borrar.
        if (seg != NULL) {
            if (ante != NULL) {
                ante->sig = seg->sig; // Saltear el nodo que quieres eliminar.
            } else {
                lista = seg->sig; // El nodo a eliminar es el primero de la lista.
            }
            free(seg); // Eliminar el nodo.
        }
    }
    return lista;
}

void imprimirListaLectores(nodoLector* lista) {
    nodoLector* actual = lista;
    while (actual != NULL) {
        printf("Nombre: %s, DNI: %d\n", actual->info.nombreYapellido, actual->info.dni);
        actual = actual->sig;
    }
    printf("\n");
}



void mostrarArchivo (const char * archivoLectores)
{
    FILE * archi = fopen(archivoLectores,"rb");
    lector auxiliar;

    if(archi == NULL)
    {
        printf("Error\n");
    }else
    {
        while(fread(&auxiliar,sizeof(lector),1,archi)==1)
        {
            printf("Nombre: %s, DNI: %d\n", auxiliar.nombreYapellido, auxiliar.dni);
        }
    }
}

nodoLector *cargarLectorDesdeArchivo(FILE *archivo)
{
    lector nuevoLector;
    if (fread(&nuevoLector, sizeof(nuevoLector), 1, archivo) != 1)
    {
        printf("No se pudo abrir el archivo de lectores. (No hay lectores en el registro todavía)\n");
        return NULL; // Fin del archivo
    }

    // Crear un nodo para el lector
    nodoLector *nuevoNodo = crearNodoLector(nuevoLector);
    return nuevoNodo;
}

nodoLector *cargarLectoresDesdeArchivo(const char *nombreArchivo)
{
    FILE *archivo;
    archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        // El archivo no existe, crea uno vacío
        archivo = fopen(nombreArchivo, "wb");
        if (archivo == NULL)
        {
            printf("No se pudo crear el archivo de lectores.\n");
            return NULL;
        }
        fclose(archivo);

        // Vuelve a abrir el archivo en modo lectura binaria
        archivo = fopen(nombreArchivo, "rb");
        if (archivo == NULL)
        {
            printf("No se pudo abrir el archivo de lectores.\n");
            return NULL;
        }
    }

    nodoLector *lista = iniciarLista();
    nodoLector *nuevoNodo;

    while ((nuevoNodo = cargarLectorDesdeArchivo(archivo)) != NULL)
    {

        insertarOrdenado(&lista, nuevoNodo);
    }

    fclose(archivo);
    return lista;
}



// Función para liberar la memoria de la lista de lectores
void liberarListaLectores(nodoLector *lista)
{
    while (lista != NULL)
    {
        nodoLector *temp = lista;
        lista = lista->sig;
        free(temp);
    }
}

// Función para insertar un lector en la lista ordenadamente por DNI
void insertarOrdenado(nodoLector **lista, nodoLector *nuevoNodo)
{
    if (*lista == NULL || nuevoNodo->info.dni < (*lista)->info.dni)
    {
        nuevoNodo->sig = *lista;
        *lista = nuevoNodo;
    }
    else
    {
        nodoLector *actual = *lista;
        while (actual->sig != NULL && actual->info.dni < nuevoNodo->info.dni)
        {
            actual = actual->sig;
        }

        nuevoNodo->sig = actual->sig;
        actual->sig = nuevoNodo;
    }
}

void agregarLectorAListaYArchivo(nodoLector **lista, const char *archivoLectores, lector aGuardar) {


    nodoLector *nuevoNodo = crearNodoLector(aGuardar);

    insertarOrdenado(lista, nuevoNodo); // Agregar a la lista

    FILE *archivo = fopen(archivoLectores, "ab");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escritura.\n");
        free(nuevoNodo); // Liberar memoria si no se pudo abrir el archivo
        return;
    }

    fwrite(&aGuardar, sizeof(aGuardar), 1, archivo); // Guardar en el archivo
    fclose(archivo);

    printf("Lector guardado en la lista y en el archivo.\n");
}



