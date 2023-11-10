#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include <string.h>
#include <unistd.h>

/*

*/

void realizarAlquiler (const char * archivoLectores, const char * archivoLibros, const char * archivoAlquileres, listaGeneros ** listaLibros, nodoLector ** listaLectores, nodoAlquiler ** listaAlquileres)
{
    FILE* archiLibros = fopen(archivoLibros, "rb+");
    FILE* archiLectores = fopen(archivoLectores, "rb+");
    FILE* archiAlquiler = fopen(archivoAlquileres, "rb+");

    if (archiAlquiler == NULL)
    {
        archiAlquiler = fopen(archivoAlquileres, "wb+");
        if (archiAlquiler == NULL)
        {
            printf("Error al abrir el archivo de alquiler\n");
            return;
        }
    }

    if (archiLibros == NULL || archiLectores == NULL)
    {
        printf("Error al abrir los archivos\n");
        return;
    }

    char tituloBuscado[20];
    char nombreLector[20];


    printf("Ingrese el nombre del lector que va a alquilar: ");
    fflush(stdin);
    gets(nombreLector);

    nodoLector * lectorEncontrado = buscarNodoLector (*lista,nombreLector);

    if(lectorEncontrado == NULL)  //Si no existe le doy opcion a crear desde aca
    {
        char mander = 's';
        puts("Desea crear el usuario ? \n");
        fflush(stdin);
        scanf("%c",&mander);
        if(mander == 's')
        {
            lector nuevo = cargarLector(nombreLector);
            insertarOrdenado(&listaLectores,crearNodoLector(nuevo));

        }else
        {
            fclose(archiLibros);
            fclose(archiLectores);
            fclose(archiAlquiler);
            return;

        }
    }


    nodoArbolLibro *libroEncontrado = buscarLibroPorTitulo(*listaLibros, tituloBuscado);
    printf("Ingrese el título del libro que desea buscar: ");
    fflush(stdin);
    gets(tituloBuscado);


    if (libroEncontrado != NULL && libroEncontrado->dato.Copias.cantCopias >= 1) //el libroexiste y dispone de 1 o mas Copia
    {

        if(lectorEncontrado->info.alquiler == 1)  //Si esta en 1 puede alquilar
        {




            fclose(archiLibros);
            fclose(archiLectores);
            fclose(archiAlquiler);
        }
        else if ( lectorEncontrado != NULL && lectorEncontrado->info.alquiler == 0) //El lector existe pero no puede alquilar
        {

            printf("El lector ya posee un alquiler");
            //Mostrar Registro Alquiler
            //MostrarLista

        }
         fclose(archiLibros);
        fclose(archiLectores);
        fclose(archiAlquiler);
    }else if (libroEncontrado != NULL && libroEncontrado->dato.Copias.cantCopias < 1 )//el libro existe pero no esta disponible
    {
        printf("Libro no disponible");
        //Podriamos agregar una funcion de agregar personas a una FILA ..
        fclose(archiLibros);
        fclose(archiLectores);
        fclose(archiAlquiler);

    }else if(libroExisteEnArchivo == NULL){
        printf("El libro no fue encontrado.\n");
        fclose(archiLibros);
        fclose(archiLectores);
        fclose(archiAlquiler);
    }
}


