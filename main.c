#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"

//comentario agregado de practica - nico
//nuevo comentario
//Constantes para los archivos
const char * archivoLectores = "archivoLectores.bin";
const char * archivoLibros = "archivoLibros.bin";

int main()
{
        //Funcion para cargar archivo
        cargarArchivoLectores(archivoLectores);
        cargarLibroEnArchivo(archivoLibros);
        /*
        //Inicializar la lista
        nodoLector * listadoDeLectores = iniciarLista();
        //Funcion para cargar la lista con los datos del archivo
        listadoDeLectores = cargarLectoresDesdeArchivo (archivoLectores);
        puts("\n");
        imprimirListaLectores(listadoDeLectores);
        //Funcion para añadir un lector a la lista y tambien guardarlo en el archivo
         agregarLectorAListaYArchivo(&listadoDeLectores, archivoLectores);

         //cargarLibroEnArchivo(archivoLibros);*/
         puts("Libros\n");
         mostrarArchivoDeLibros(archivoLibros);
         /*   puts("\n");
         listaGeneros * listaPrincipal = inicializarListaGeneros ();
         listaPrincipal = cargarListaDeGenerosDesdeArchivo(archivoLibros,listaPrincipal);
         recorrerListaDeGeneros(listaPrincipal);*/
         puts("Lectores\n");
         mostrarArchivo(archivoLectores);

    return 0;
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


