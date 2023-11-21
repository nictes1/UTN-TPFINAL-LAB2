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
        //generarArchivoConGenerosYLibros(archivoLibros);
        //generarArchivoLectores(archivoLectores);

        listaGeneros * listaPrincipal = inicializarListaGeneros ();
        listaPrincipal = cargarListaDeGenerosDesdeArchivo(archivoLibros,listaPrincipal);

<<<<<<< HEAD
=======

>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
        nodoLector * listaDeLectores = iniciarLista();
        listaDeLectores = cargarLectoresDesdeArchivo (archivoLectores);



        //Inicializar la lista y cargarla con los datos del archivo de alquiler
        nodoAlquiler *listaAlquileres = inicializarListaAlquiler();
        listaAlquileres = cargarAlquileresDesdeArchivo(archivoAlquileres);

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
                mostrarMenuBibliotecario(&listaPrincipal,&listaDeLectores,&listaAlquileres);
                system("cls");
                break;
            case 2:
                mostrarMenuAlquiler(&listaPrincipal,&listaDeLectores,&listaAlquileres);
                system("cls");
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

    system("cls");

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
        printf("7. Dar de baja/alta un libro\n");
        printf("0. Volver al menu principal\n");

        opcion = leerOpcion();

        switch (opcion) {
            case 1:
                agregarLibroAListaYArchivo(listaDeGeneros, archivoLibros);
                break;
            case 2:
<<<<<<< HEAD
                puts("Mostrar por genero\n");
                char generoAver [30];
                fflush(stdin);
=======
                system("cls");
                printf("2. Mostrar lista de libros por genero\n");
                char generoAver [30];
                fflush(stdin);

                ///muestra los generos disponibles.
                mostrarGeneros(*listaDeGeneros);

                puts("Ingrese el genero que desea buscar: \n");
>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
                fgets(generoAver, sizeof(generoAver), stdin);
                generoAver[strcspn(generoAver, "\n")] = 0;

                mostrarLibrosPorGenero(*listaDeGeneros,&generoAver);
                system("pause");
                system("cls");
                break;
            case 3:
<<<<<<< HEAD
                //
                puts("Datos de un libro");
                //Mostrar un libro
                 puts("Libro a buscar\n");  // Buscar un libro por titulo
=======
                system("cls");
                printf("3. Mostrar informacion de un libro por titulo\n");

                mostrarLibrosDisponibles(*listaDeGeneros);

                puts("\n"); //salto de linea para que se vea mas claro.
                puts("Cual es libro que desa buscar? \n");  // Buscar un libro por titulo
>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
                char nombreLibro [60];
                fflush(stdin);
                fgets(nombreLibro, sizeof(nombreLibro), stdin);
                nombreLibro[strcspn(nombreLibro, "\n")] = 0;

                printf("\nNombre del libro a buscar : %s\n",nombreLibro);
<<<<<<< HEAD

=======
>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
                nodoArbolLibro *libroAbuscar = buscarLibroPorTituloEnLista(*listaDeGeneros,&nombreLibro);


                if(libroAbuscar != NULL)
                {
                    puts("\nDato del libro\n");
<<<<<<< HEAD

                    mostrarLibro(libroAbuscar->dato);
                }else
                {
                puts("Libro inexistente");
                }
                system("pause");
                system("cls");
                break;
            case 4:
                printf("Cargar un lector\n");
                char nombreLector [30];
                printf("Ingrese el nombre del lector que va a ingresar: ");
                fflush(stdin);
                fgets(nombreLector, sizeof(nombreLector), stdin);
                nombreLector[strcspn(nombreLector, "\n")] = 0;

=======
                    mostrarLibro(libroAbuscar->dato);
                }else
                {
                puts("Libro inexistente");
                }
                system("pause");
                system("cls");
                break;
            case 4:
                printf("Cargar un lector\n");
                char nombreLector [30];
                printf("Ingrese el nombre del lector que va a ingresar: ");
                fflush(stdin);
                fgets(nombreLector, sizeof(nombreLector), stdin);
                nombreLector[strcspn(nombreLector, "\n")] = 0;

>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
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
                system("pause");
                system("cls");
                break;
            case 5:
<<<<<<< HEAD
                printf("Ver datos de un lector.\n");
                char nombreLectorAbuscar [30];
                printf("Ingrese el nombre del lector que va a buscar: ");
                fflush(stdin);
                fgets(nombreLectorAbuscar, sizeof(nombreLectorAbuscar), stdin);
                nombreLectorAbuscar[strcspn(nombreLectorAbuscar, "\n")] = 0;

                nodoLector * buscado = buscarNodoLector(*listaDeLectores,&nombreLectorAbuscar);
                puts("\n");
                if(buscado != NULL){
                    mostrarLector(buscado->info);
                }else
                {
                    printf("Lector inexistente\n");
=======
                system("cls");
                printf("5. Ver un lector\n");
                int dniBuscado;
                printf("Ingrese el DNI del lector: ");
                scanf("%d", &dniBuscado); // Leer DNI como entero

                nodoLector *buscado = buscarLectorPorDNI(*listaDeLectores, dniBuscado);
                puts("\n");
                if (buscado != NULL) {
                    mostrarLector(buscado->info);
                } else {
                    printf("Lector con DNI %d no encontrado.\n", dniBuscado);
>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
                }
                system("pause");
                system("cls");
                break;
            case 6:
<<<<<<< HEAD
                printf("Ver listado de lectores en el sistema.\n");
=======
                system("cls");
                printf("6. Ver lista de lectores\n");

>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
                imprimirListaLectores(*listaDeLectores);
                system("pause");
                system("cls");
                break;
            case 7:
<<<<<<< HEAD
                {
                    char nombreLibro [60];
                    int nuevoEstado;
                    printf("Ingrese el nombre del libro: ");
                    fflush(stdin);
                    fgets(nombreLibro, sizeof(nombreLibro), stdin);
                    nombreLibro[strcspn(nombreLibro, "\n")] = 0;

                    printf("Ingrese el nuevo estado (1 para disponible, 0 para no disponible): ");
                    scanf("%d", &nuevoEstado);

                    modificarEstadoLibro(*listaDeGeneros,&nombreLibro, nuevoEstado, archivoLibros);
                }
=======
                system("cls");
                printf("7. Dar de baja/alta un libro\n");
                puts("Libros disponibles: \n");
                mostrarLibrosDisponibles(*listaDeGeneros);
                char libro [60];
                int nuevoEstado;
                printf("\n Ingrese el nombre del libro: ");
                fflush(stdin);
                fgets(libro, sizeof(libro), stdin);
                libro[strcspn(libro, "\n")] = 0;


                puts("Libro encontrado: \n");
                mostrarLibrosPorNombre(*listaDeGeneros,&libro);

                printf("Ingrese el nuevo estado (1 para disponible, 0 para no disponible): ");
                scanf("%d", &nuevoEstado);

                modificarEstadoLibro(*listaDeGeneros,&libro, nuevoEstado, archivoLibros);
                buscarLibroPorTituloEnLista(*listaDeGeneros,&libro);
>>>>>>> 5e3e51a4e9637a1a9f65a44acad5c9cda1614f79
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

    system("cls");

    int opcion;

    do {
        // Mostrar menu de Alquiler
        printf("\n=== Menu de Alquiler ===\n");
        printf("1. Realizar nuevo alquiler\n");
        printf("2. Mostrar alquileres pendientes de devolucion\n");
        printf("3. Mostrar informacion de un alquiler\n");
        printf("4. Realizar Devolucion\n");
        printf("0. Volver al menu principal\n");

        opcion = leerOpcion();

        switch (opcion) {
            case 1:

                realizarAlquiler(archivoLectores, archivoLibros, archivoAlquileres, listaDeGeneros, listaDeLectores, listaDeAlquileres);
                system("pause");
                system("cls");
                break;
            case 2:
                mostrarAlquileres(*listaDeAlquileres);
                system("pause");
                system("cls");
                break;
            case 3:
                {
                char lectorDeudor [30];
                printf("Ingrese el nombre del lector que va a buscar en la lista de alquileres: ");
                fflush(stdin);
                fgets(lectorDeudor, sizeof(lectorDeudor), stdin);
                lectorDeudor[strcspn(lectorDeudor, "\n")] = 0;
                mostrarAlquilerPendienteDeDevolucion(*listaDeAlquileres, lectorDeudor);
                }
                system("pause");
                system("cls");
                break;
            case 4:
                realizarDevolucion(archivoLectores,archivoLibros,archivoAlquileres,listaDeGeneros,listaDeLectores,listaDeAlquileres);
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


