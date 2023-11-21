#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include <string.h>
#include <unistd.h>


const char *nombres[] = {
    "Juan", "Ana", "Pedro", "Maria", "Carlos", "Lucia",
    "Jose", "Sofia", "Fernando", "Carmen", "Miguel", "Elena",
    "Francisco", "Isabel", "Diego", "Laura"
};

const char *apellidos[] = {
    "Perez", "Gonzalez", "Lopez", "Martinez", "Rodriguez", "Garcia",
    "Fernandez", "Gomez", "Sanchez", "Diaz", "Vazquez", "Romero",
    "Torres", "Dominguez", "Jimenez", "Ruiz"
};

void generarLectorRandom(lector *l) {
    const char *nombres[] = {"Juan", "Ana", "Pedro", "Maria", /* ... otros nombres ... */};
    const char *apellidos[] = {"Perez", "Gonzalez", "Lopez", "Martinez", /* ... otros apellidos ... */};

    int nombreIdx = rand() % (sizeof(nombres) / sizeof(nombres[0]));
    int apellidoIdx = rand() % (sizeof(apellidos) / sizeof(apellidos[0]));

    sprintf(l->nombreYapellido, "%s %s", nombres[nombreIdx], apellidos[apellidoIdx]);
    l->dni = rand() % 50000000 + 10000000;
    l->esEstudiante = rand() % 2;
    l->alquiler = 1;
    sprintf(l->email, "%s%s@gmail.com", nombres[nombreIdx], apellidos[apellidoIdx]);
    sprintf(l->direccion, "Calle %d", rand() % 100 + 1);
}

void generarArchivoLectores(const char *filename) {
    FILE *buffer = fopen(filename, "ab");
    if (!buffer) {
        printf("Error al abrir el archivo %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < 100; i++) {
        lector l;
        generarLectorRandom(&l);
        fwrite(&l, sizeof(lector), 1, buffer);
    }

    fclose(buffer);
}



// Funcion para cargar un lector desde la entrada estandar
lector cargarLector(char nombrelector[])
{
    lector nuevoLector;

    strcpy(nuevoLector.nombreYapellido, nombrelector);

    printf("Ingrese el DNI: ");
    scanf("%d", &nuevoLector.dni);

    printf("Es estudiante (1 para si, 0 para no): ");
    scanf("%d", &nuevoLector.esEstudiante);

    printf("Ingrese el email: ");
    scanf("%s", nuevoLector.email);

    printf("Ingrese la direccion: ");
    scanf("%s", nuevoLector.direccion);

    nuevoLector.alquiler = 1;

    return nuevoLector;
}

// Funcion para verificar si un lector con el mismo nombre ya existe en un archivo binario
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
        if (strcasecmp(lectorActual.nombreYapellido, nombreLector) == 0)
        {
            fclose(archivo);
            return 1; // El lector ya existe en el archivo
        }
    }

    fclose(archivo);
    return 0; // El lector no existe en el archivo
}

// Funcion para guardar un lector en un archivo binario
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

//funcion para agregar lectores al archivo - CARGA MANUAL DE LECTORES
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
        fgets(nombre, sizeof(nombre), stdin);
        nombre[strcspn(nombre, "\n")] = 0;
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


nodoLector* buscarNodoLector(nodoLector* lista, const char* nombre) {
    if (lista == NULL) {
        printf("La lista está vacía.\n");
        return NULL;
    }

    if (nombre == NULL) {
        printf("El nombre proporcionado es NULL.\n");
        return NULL;
    }

    nodoLector* seg;
    seg = lista;
    printf("Lector a buscar %s\n",nombre);
    while (seg != NULL) {
        if (strcasecmp(seg->info.nombreYapellido, nombre) == 0) {
            return seg;
        }
        seg = seg->sig;
    }

    printf("No se encontro el lector con nombre %s.\n", nombre);
    return NULL;
}

//Inicializa la lista del lector
nodoLector* iniciarLista() {
    return NULL;
}

//crea un nodo de tipo "lector"
nodoLector* crearNodoLector(lector nuevo) {
    nodoLector* auxiliar = (nodoLector*)malloc(sizeof(nodoLector));
    auxiliar->info = nuevo;
    auxiliar->sig = NULL;

    return auxiliar;
}


//Muestra informacion de un lector
void mostrarLector(lector unLector) {
    printf("Nombre: %s\n", unLector.nombreYapellido);
    printf("DNI: %d\n", unLector.dni);
    printf("Es estudiante: %s\n", unLector.esEstudiante ? "Si" : "No");
    printf("Email: %s\n", unLector.email);
    printf("Direccion: %s\n", unLector.direccion);
    printf("Estado de alquiler: %s\n", unLector.alquiler ? "Disponible" : "En alquiler");
}


//Imprime lista completa de lectores
void imprimirListaLectores(nodoLector* lista) {
    nodoLector* actual = lista;
    puts("Lectores: \n");
    while (actual != NULL) {
        mostrarLector(actual->info);
        puts("\n---------\n");
        actual = actual->sig;
    }
}


//Muesta el archivo de lectores
void mostrarArchivolectores (const char * archivoLectores)
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
            mostrarLector(auxiliar);
            puts("\n------------\n");
        }
    }
}


//Carga la lista de lectores x Archivo
nodoLector *cargarLectoresDesdeArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        // El archivo no existe, crea uno vac�o
        archivo = fopen(nombreArchivo, "wb");
        if (archivo == NULL) {
            printf("No se pudo crear el archivo de lectores.\n");
            return NULL;
        }
        fclose(archivo);

        // Vuelve a abrir el archivo en modo lectura binaria
        archivo = fopen(nombreArchivo, "rb");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo de lectores.\n");
            return NULL;
        }
    }

    nodoLector *lista = iniciarLista();
    lector nuevoLector;  // Cambio: mover la declaraci�n fuera del bucle

    // Lectura continua desde el archivo
    while (fread(&nuevoLector, sizeof(nuevoLector), 1, archivo) == 1) {
        nodoLector *nuevoNodo = crearNodoLector(nuevoLector);
        insertarOrdenado(&lista, nuevoNodo);
    }

    fclose(archivo);
    return lista;
}



// Funcion para liberar la memoria de la lista de lectores
void liberarListaLectores(nodoLector *lista)
{
    while (lista != NULL)
    {
        nodoLector *temp = lista;
        lista = lista->sig;
        free(temp);
    }
}

// Funcion para insertar un lector en la lista ordenadamente por DNI
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

//Funcion para agregar un nuevo lector ordenado en la lista y en el archivo de lectores
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



//Borra un nodo de lector buscando por su DNI
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
            ante = seg;          // Adelantar una posici�n la variable 'ante'.
            seg = seg->sig;      // Avanzar al siguiente nodo.
        }
        // En este punto, 'ante' contiene la direcci�n del nodo anterior al buscado, y 'seg'
        // contiene la direcci�n del nodo que quieres borrar.
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

nodoLector *buscarLectorPorDNI(nodoLector *lista, int dniBuscado) {
    nodoLector *actual = lista;
    while (actual != NULL) {
        if (actual->info.dni == dniBuscado) {
            return actual; // Lector encontrado
        }
        actual = actual->sig;
    }
    return NULL; // Lector no encontrado
}

