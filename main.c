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

void mostrarMenuBibliotecario(listaGeneros ** listaDeGeneros, nodoLector ** listaDeLectores, nodoAlquiler ** listaDeAlquileres);
void mostrarMenuAlquiler(listaGeneros ** listaDeGeneros, nodoLector ** listaDeLectores, nodoAlquiler ** listaDeAlquileres);

int main()
{

        //generarArchivoConGenerosYLibros("libros.bin");
        //mostrarArchivoDeLibros("libros.bin");


        //Funcion para cargar archivos manualmente

        //cargarArchivoLectores(archivoLectores);
        cargarLibroEnArchivo(archivoLibros);

        //Funcion para mostrar archivos;

        //mostrarArchivolectores(archivoLectores);
        // mostrarArchivoDeLibros(archivoLibros);
        //mostrarArchivoAlquileres(archivoAlquileres);

        //Inicializar la lista lectores

        nodoLector * listadoDeLectores = iniciarLista();

        //Funcion para cargar la lista con los datos del archivo
        listadoDeLectores = cargarLectoresDesdeArchivo (archivoLectores);
        puts("\nLista de lectores\n");
        imprimirListaLectores(listadoDeLectores);

        puts("Buscar lector");
        nodoLector * aBuscar = buscarNodoLector(listadoDeLectores,"federico sosa");
        puts("Nodo a buscar \n");
        mostrarLector(aBuscar->info);


        //Funciones de libros


         puts("Libros\n");

         puts("Lista de libros\n");
         listaGeneros * listaPrincipal = inicializarListaGeneros (); //inicializar La lista
         listaPrincipal = cargarListaDeGenerosDesdeArchivo(archivoLibros,listaPrincipal); //Cargar la lista con los datos del archivo
         recorrerListaDeGeneros(listaPrincipal); //mostrar La lista Completa

         puts("Libro a buscar\n");  // Buscar un libro por titulo
         char nombreLibro [30];
         fflush(stdin);
         gets(nombreLibro);


        //Mostrar un libro

         nodoArbolLibro *libroAbuscar = buscarLibroPorTituloEnLista(listaPrincipal, nombreLibro);


         if(libroAbuscar != NULL)
         {
             puts("\nDato del libro\n");

             mostrarLibro(libroAbuscar->dato);
         }else
         {
             puts("Libro inexistente");
         }

         puts("Mostrar por genero\n");

        mostrarLibrosPorGenero(listaPrincipal,"terror");

        puts("Datos de un libro");

        //Funciones de alquiler

        //Inicializar la lista y cargarla con los datos del archivo de alquiler
            nodoAlquiler *listaAlquileres = cargarAlquileresDesdeArchivo(archivoAlquileres);

        //mostrarLa lista de alquileres
            //mostrarAlquileres(listaAlquileres);

         realizarAlquiler(archivoLectores,archivoLibros,archivoAlquileres,&listaPrincipal,&listadoDeLectores,&listaAlquileres);


    /*
         int opcion;

    do {
        // Mostrar men� principal
        printf("\n=== Men� Principal ===\n");
        printf("1. Acciones del Bibliotecario\n");
        printf("2. Acciones de Alquiler\n");
        printf("0. Salir\n");
        printf("Seleccione una opci�n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                mostrarMenuBibliotecario(&listaPrincipal,&listadoDeLectores,&listaAlquileres);
                break;
            case 2:
                mostrarMenuAlquiler(&listaPrincipal,&listadoDeLectores,&listaAlquileres);
                break;
            case 0:
                printf("Saliendo del programa. �Hasta luego!\n");
                break;
            default:
                printf("Opci�n no v�lida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 0);

    // ... Resto de tu c�digo ...
*/
    return 0;
}

void mostrarMenuBibliotecario(listaGeneros ** listaDeGeneros, nodoLector ** listaDeLectores, nodoAlquiler ** listaDeAlquileres) {
    int opcion;

    do {
        // Mostrar men� del Bibliotecario
        printf("\n=== Men� del Bibliotecario ===\n");
        printf("1. Agregar nuevo libro\n");
        printf("2. Mostrar lista de libros por g�nero\n");
        printf("3. Mostrar informaci�n de un libro por t�tulo\n");
        printf("0. Volver al men� principal\n");
        printf("Seleccione una opci�n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarLibroAListaYArchivo(listaDeGeneros, archivoLibros);
                break;
            case 2:
                //
                puts("Mostrar por genero\n");
                mostrarLibrosPorGenero(listaDeGeneros,"Edad Media");
                break;
            case 3:
                //
                puts("Datos de un libro");
                //Mostrar un libro
                 puts("Libro a buscar\n");  // Buscar un libro por titulo
                char nombreLibro [30];
                fflush(stdin);
                gets(nombreLibro);

                nodoArbolLibro *libroAbuscar = buscarLibroPorTituloEnLista(listaDeGeneros, nombreLibro);


                if(libroAbuscar != NULL)
                {
                    puts("\nDato del libro\n");

                    mostrarLibro(libroAbuscar->dato);
                }else
                {
                puts("Libro inexistente");
                }
                break;
            case 0:
                printf("Volviendo al men� principal.\n");
                break;
            default:
                printf("Opci�n no v�lida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 0);
}

void mostrarMenuAlquiler(listaGeneros ** listaDeGeneros, nodoLector ** listaDeLectores, nodoAlquiler ** listaDeAlquileres) {
    int opcion;

    do {
        // Mostrar men� de Alquiler
        printf("\n=== Men� de Alquiler ===\n");
        printf("1. Realizar nuevo alquiler\n");
        printf("2. Mostrar alquileres pendientes de devoluci�n\n");
        printf("3. Mostrar informaci�n de un alquiler\n");
        printf("0. Volver al men� principal\n");
        printf("Seleccione una opci�n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                realizarAlquiler(archivoLectores, archivoLibros, archivoAlquileres, &listaDeGeneros, &listaDeLectores, &listaDeAlquileres);
                break;
            case 2:
                mostrarAlquilerPendienteDeDevolucion(listaDeAlquileres, "nombreLectorAbuscar"); // Es para probar, aca debemos pedir al usuario que ingrese el nombre
                break;
            case 3:
                mostrarDatosAlquiler(listaDeAlquileres);
                break;
            case 0:
                printf("Volviendo al men� principal.\n");
                break;
            default:
                printf("Opci�n no v�lida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 0);
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


