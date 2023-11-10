#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include <string.h>
#include <unistd.h>


void mostrarAlquilerPendienteDeDevolucion (nodoAlquiler * listaAlquileres, char nombreLectorAbuscar[])
{
    if(listaAlquileres == NULL)
    {
        puts("Lista Vacia\n");
    }else
    {
        nodoAlquiler * sig;
        sig = listaAlquileres;
        while(sig != NULL && strcasecmp(sig->datosLector.nombreYapellido,nombreLectorAbuscar)!=0)
        {
            sig = sig->siguiente;
        }
        mostrarDatosAlquiler(sig);
    }
}

void mostrarDatosAlquiler(nodoAlquiler * listaAlquileres)
{
    printf("Nombre : %s \n", listaAlquileres->datosLector.nombreYapellido);
    printf("Libro : %s \n",listaAlquileres->datoLibro.titulo);
    printf("DNI: %i \n", listaAlquileres->datosLector.dni);
    printf("Email: %s\n", listaAlquileres->datosLector.email);
    printf("Fecha de alquiler: %d/%d/%d\n", listaAlquileres->datosLector.fechaAlquiler.dia, listaAlquileres->datosLector.fechaAlquiler.mes, listaAlquileres->datosLector.fechaAlquiler.anio);
    puts("\n---------------------\n");
}

void realizarAlquiler(const char *archivoLectores, const char *archivoLibros, const char *archivoAlquileres, listaGeneros **listaLibros, nodoLector **listaLectores, nodoAlquiler **listaAlquileres) {
    char nombreLector[20];
    char tituloBuscado[20];
    int dia, mes, anio;

    printf("Ingrese el nombre del lector que va a alquilar: ");
    fflush(stdin);
    gets(nombreLector);

    // Buscar el lector
    nodoLector *lectorEncontrado = buscarNodoLector(*listaLectores, nombreLector);

    if (lectorEncontrado != NULL && lectorEncontrado->info.alquiler == 0) {
        printf("El lector tiene un alquiler pendiente de devoluci�n:\n");
        mostrarAlquilerPendienteDeDevolucion(*listaAlquileres, lectorEncontrado->info.nombreYapellido);
        return;
    }

    if (lectorEncontrado == NULL) {
        char mander = 's';
        printf("El lector no est� registrado, �desea crearlo? (s/n): ");
        fflush(stdin);
        scanf("%c", &mander);

        if (mander == 's') {
            lector nuevo = cargarLector(nombreLector);
            insertarOrdenado(listaLectores, crearNodoLector(nuevo));
            lectorEncontrado = buscarNodoLector(*listaLectores, nombreLector);
        } else {
            return;
        }
    }

    printf("Ingrese el t�tulo del libro que desea buscar: ");
    fflush(stdin);
    gets(tituloBuscado);

    // Buscar el libro en la lista de libros
    nodoArbolLibro *libroEncontrado = buscarLibroEnArbol(*listaLibros, tituloBuscado);

    if (libroEncontrado == NULL) {
        printf("Libro no encontrado.\n");
        return;
    }

    if (libroEncontrado->dato.Copias.cantCopias == 0) {
        printf("Libro no disponible.\n");
        return;
    }

    libroEncontrado->dato.Copias.cantCopias--;


    lectorEncontrado->info.alquiler = 0;

    printf("Ingrese la fecha de alquiler (DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &anio);

    stRegistroAlquiler nuevoAlquiler;
    nuevoAlquiler.datoLibroAlquilado = libroEncontrado->dato;
    nuevoAlquiler.datosLector = lectorEncontrado->info;
    nuevoAlquiler.fechaAlquiler.dia = dia;
    nuevoAlquiler.fechaAlquiler.mes = mes;
    nuevoAlquiler.fechaAlquiler.anio = anio;

    // Agregar el alquiler a la lista de alquileres
    nodoAlquiler *nuevoNodoAlquiler = (nodoAlquiler *)malloc(sizeof(nodoAlquiler));
    nuevoNodoAlquiler->datoLibro = nuevoAlquiler.datoLibroAlquilado;
    nuevoNodoAlquiler->datosLector = nuevoAlquiler.datosLector;
    nuevoNodoAlquiler->fechaAlquiler = nuevoAlquiler.fechaAlquiler;
    nuevoNodoAlquiler->siguiente = *listaAlquileres;
    *listaAlquileres = nuevoNodoAlquiler;

    // Guardar el alquiler en el archivo de alquileres
    FILE *archivoAlquiler = fopen(archivoAlquileres, "ab");
    if (archivoAlquiler != NULL) {
        fwrite(&nuevoAlquiler, sizeof(stRegistroAlquiler), 1, archivoAlquiler);
        fclose(archivoAlquiler);
    } else {
        printf("Error al abrir el archivo de alquileres para escritura.\n");
    }

    // Actualizar el estado del lector en el archivo de lectores
    FILE *archivoLect = fopen(archivoLectores, "r+b");
    if (archivoLect != NULL) {
        fseek(archivoLect, (long)(-sizeof(lector)), SEEK_CUR);
        fwrite(&(lectorEncontrado->info), sizeof(lector), 1, archivoLect);
        fclose(archivoLect);
    } else {
        printf("Error al abrir el archivo de lectores para escritura.\n");
    }
}

