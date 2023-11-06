#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"

//nuevo comentario
//Constantes para los archivos
const char * archivoLectores = "archivoLectores.bin";
const char * archivoLibros = "archivoLibros.bin";

int main()
{
        //Funcion para cargar archivo
        cargarArchivoLectores(archivoLectores);
        //Inicializar la lista
        nodoLector * listadoDeLectores = iniciarLista();
        //Funcion para cargar la lista con los datos del archivo
        listadoDeLectores = cargarLectoresDesdeArchivo (archivoLectores);
        puts("\n");
        imprimirListaLectores(listadoDeLectores);
        //Funcion para añadir un lector a la lista y tambien guardarlo en el archivo
         agregarLectorAListaYArchivo(&listadoDeLectores, archivoLectores);

    return 0;
}



//Funciones Archivo
void guardarListaEnArchivo(const char* nombreArchivo, nodoLector* lista) {
    FILE* archivo = fopen(nombreArchivo, "ab"); // Abrir el archivo en modo de escritura binaria

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escritura.\n");
        return;
    }

    lector aux;

    nodoLector* actual = lista;

    while (actual != NULL) {


        fwrite(&actual->info, sizeof(lector), 1, archivo);  //No guarda el nodo sino que guarda los datos de ese nodo.
        actual = actual->sig;
    }

    fclose(archivo); // Cerrar el archivo
}



void guardarArregloDeArboles(celdaGeneros ADA[], int dim)
{
    FILE *archivo = fopen(archivoLibros, "wb"); // Abre el archivo para escritura binaria
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para escritura.\n");
        return;
    }

    for (int i = 0; i < dim; i++)
    {
        guardarArbolLibrosRecursivo(ADA[i].arbolDeLibros, archivo);
    }

    fclose(archivo);
}


void guardarArbolLibrosRecursivo(nodoArbolLibro *arbol, FILE *archivo)
{
    if (arbol != NULL)
    {
        fwrite(&arbol->dato , sizeof(stlibros), 1, archivo); // Guarda el libro en el archivo
        guardarArbolLibrosRecursivo(arbol->izq, archivo); // Recorre el subárbol izquierdo
        guardarArbolLibrosRecursivo(arbol->der, archivo); // Recorre el subárbol derecho
    }
}

///Funcion Dias
int contarDias(lector a)
{
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dias = a.fechaAlquiler.dia;

    for (int i = 0; i < a.fechaAlquiler.mes - 1; i++)
    {
        dias += meses[i];
    }

    return dias;
}

int diferenciaFechas(lector a, lector temp)
{
    int dias1 = contarDias(a);
    int dias2 = contarDias(temp);

    int diferencia = dias2 - dias1;

    return diferencia;
}


