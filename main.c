#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include <string.h>



const char * archivoLectores = "archivoLectores.bin";
const char * archivoLibros = "archivoLibros.bin";
const char * archivoAlquileres = "archivoAlquileres.bin";

int main()
{
        //Funcion para cargar archivos

        //cargarArchivoLectores(archivoLectores);
        //cargarLibroEnArchivo(archivoLibros);

        //Funcion para mostrar archivos;
        //mostrarArchivolectores(archivoLectores);
        // mostrarArchivoDeLibros(archivoLibros);

        //Inicializar la lista
        nodoLector * listadoDeLectores = iniciarLista();
        //Funcion para cargar la lista con los datos del archivo
        listadoDeLectores = cargarLectoresDesdeArchivo (archivoLectores);
        puts("\n");
        imprimirListaLectores(listadoDeLectores);

        puts("Buscar lector");
        nodoLector * aBuscar = buscarNodoLector(listadoDeLectores,"federico sosa");
        puts("Nodo a buscar \n");
        mostrarLector(aBuscar->info);

         puts("Libros\n");

         puts("\n");
         listaGeneros * listaPrincipal = inicializarListaGeneros ();
         listaPrincipal = cargarListaDeGenerosDesdeArchivo(archivoLibros,listaPrincipal);
         recorrerListaDeGeneros(listaPrincipal);

         nodoAlquiler * listaAlquileres = inicializarListaAlquiler();

         realizarAlquiler(archivoLectores,archivoLibros,archivoAlquileres,&listaPrincipal,&listadoDeLectores,&listaAlquileres);

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


