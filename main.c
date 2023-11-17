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
int leerOpcion();
int main()
{
        //Inicializar la lista lectores

        nodoLector * listadoDeLectores = iniciarLista();

        //Funcion para cargar la lista con los datos del archivo
        listadoDeLectores = cargarLectoresDesdeArchivo (archivoLectores);

        //Inicializar la lista de generos
         listaGeneros * listaPrincipal = inicializarListaGeneros (); //inicializar La lista
         listaPrincipal = cargarListaDeGenerosDesdeArchivo(archivoLibros,listaPrincipal); //Cargar la lista con los datos del archivo

        //Inicializar la lista y cargarla con los datos del archivo de alquiler
            nodoAlquiler *listaAlquileres = cargarAlquileresDesdeArchivo(archivoAlquileres);

         int opcion;

    do {
        // Mostrar menu principal
        printf("\n=== Menu Principal ===\n");
        printf("1. Acciones del Bibliotecario\n");
        printf("2. Acciones de Alquiler\n");
        printf("0. Salir\n");

        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                mostrarMenuBibliotecario(&listaPrincipal,&listadoDeLectores,&listaAlquileres);
                break;
            case 2:
                mostrarMenuAlquiler(&listaPrincipal,&listadoDeLectores,&listaAlquileres);
                break;
            case 0:
                printf("Saliendo del programa. Hasta luego!\n");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}

void mostrarMenuBibliotecario(listaGeneros ** listaDeGeneros, nodoLector ** listaDeLectores, nodoAlquiler ** listaDeAlquileres) {
    int opcion;

    do {
        // Mostrar menu del Bibliotecario
        printf("\n=== Menu del Bibliotecario ===\n");
        printf("1. Agregar nuevo libro\n");
        printf("2. Mostrar lista de libros por genero\n");
        printf("3. Mostrar informacion de un libro por titulo\n");
        printf("4. Cargar un lector\n");
        printf("5. Ver un lector\n");
        printf("6. Ver lista de lectores\n");
        printf("0. Volver al menu principal\n");

        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                agregarLibroAListaYArchivo(listaDeGeneros, archivoLibros);
                break;
            case 2:
                puts("Mostrar por genero\n");
                char generoAver [30];
                fflush(stdin);
                fgets(generoAver, sizeof(generoAver), stdin);
                generoAver[strcspn(generoAver, "\n")] = 0;

                mostrarLibrosPorGenero(*listaDeGeneros,&generoAver);
                break;
            case 3:
                //
                puts("Datos de un libro");
                //Mostrar un libro
                 puts("Libro a buscar\n");  // Buscar un libro por titulo
                char nombreLibro [30];
                fflush(stdin);
                fgets(nombreLibro, sizeof(nombreLibro), stdin);
                nombreLibro[strcspn(nombreLibro, "\n")] = 0;

                printf("\nNombre del libro a buscar : %s\n",nombreLibro);

                nodoArbolLibro *libroAbuscar = buscarLibroPorTituloEnLista(*listaDeGeneros,&nombreLibro);


                if(libroAbuscar != NULL)
                {
                    puts("\nDato del libro\n");

                    mostrarLibro(libroAbuscar->dato);
                }else
                {
                puts("Libro inexistente");
                }
                break;
            case 4:
                printf("Cargar un lector\n");
                char nombreLector [30];
                printf("Ingrese el nombre del lector que va a ingresar: ");
                fflush(stdin);
                fgets(nombreLector, sizeof(nombreLector), stdin);
                nombreLector[strcspn(nombreLector, "\n")] = 0;

                nodoLector * existe = buscarNodoLector(*listaDeLectores,&nombreLector);
                lector nuevo;

                if(existe == NULL) //Si no esta en la lista lo podemos agregar
                {
                    nuevo = cargarLector(nombreLector);
                    agregarLectorAListaYArchivo(listaDeLectores,archivoLectores,nuevo);
                }else
                {
                    printf("\nEl lector ya se encuentra en la lista\n");
                }

                break;
            case 5:
                printf("Ver datos de un lector.\n");
                char nombreLectorAbuscar [30];
                printf("Ingrese el nombre del lector que va a buscar: ");
                fflush(stdin);
                fgets(nombreLectorAbuscar, sizeof(nombreLectorAbuscar), stdin);
                nombreLectorAbuscar[strcspn(nombreLectorAbuscar, "\n")] = 0;

                nodoLector * buscado = buscarNodoLector(*listaDeLectores,&nombreLectorAbuscar);
                puts("\n");
                mostrarLector(buscado->info);
                system("pause");
                system("cls");
                break;
            case 6:
                printf("Ver listado de lectores en el sistema.\n");
                imprimirListaLectores(*listaDeLectores);
                system("pause");
                system("cls");
                break;
            case 0:
                printf("Volviendo al menu principal.\n");
                sleep(1);
                system("cls");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 0);
}

void mostrarMenuAlquiler(listaGeneros ** listaDeGeneros, nodoLector ** listaDeLectores, nodoAlquiler ** listaDeAlquileres) {
    int opcion;

    do {
        // Mostrar menu de Alquiler
        printf("\n=== Menu de Alquiler ===\n");
        printf("1. Realizar nuevo alquiler\n");
        printf("2. Mostrar alquileres pendientes de devolucion\n");
        printf("3. Mostrar informacion de un alquiler\n");
        printf("0. Volver al menu principal\n");

        opcion = leerOpcion();

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
                sleep(1);
                system("cls");
                break;
            default:
                printf("Opcion no valida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 0);
}
int leerOpcion() {
    int opcion;
    while (1) {
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            printf("Opcion no valida. Intente nuevamente.\n");
        } else {
            break;
        }
    }
    return opcion;
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


