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
                *listaDeGeneros = agregarGeneroAListaYArchivo(*listaDeGeneros, archivoLibros);
                break;
            case 2:
                system("cls");
                printf("2. Mostrar lista de libros por genero\n");
                char generoAver [30];
                fflush(stdin);

                ///muestra los generos disponibles.
                mostrarGeneros(*listaDeGeneros);

                puts("Ingrese el genero que desea buscar: \n");
                fgets(generoAver, sizeof(generoAver), stdin);
                generoAver[strcspn(generoAver, "\n")] = 0;

                mostrarLibrosPorGenero(*listaDeGeneros,&generoAver);
                system("pause");
                system("cls");
                break;
            case 3:
                system("cls");
                printf("3. Mostrar informacion de un libro por titulo\n");

                mostrarLibrosDisponibles(*listaDeGeneros);

                puts("\n"); //salto de linea para que se vea mas claro.
                puts("Cual es libro que desa buscar? \n");  // Buscar un libro por titulo
                char nombreLibro [60];
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
                system("pause");
                system("cls");
                break;
            case 4:
                {
                system("cls");
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
                system("pause");
                system("cls");
                }
                break;
            case 5:
                {
                        system("cls");
                        printf("5. Ver un lector\n");
                        int opcion;

                        do{

                        printf("1.Buscar por Dni\n");
                        printf("2.Buscar por Nombre y Apellido\n");
                        printf("0.Volver\n");


                        opcion = leerOpcion();

                        switch(opcion) {
                        case 1:
                            {
                               int dniBuscado;
                                printf("Ingrese el DNI del lector: ");
                                scanf("%d", &dniBuscado); // Leer DNI como entero

                                nodoLector *buscado = buscarLectorPorDNI(*listaDeLectores, dniBuscado);
                                puts("\n");
                                if (buscado != NULL) {
                                    mostrarLector(buscado->info);
                                } else {
                                    printf("Lector con DNI %d no encontrado.\n", dniBuscado);
                                }
                                system("pause");
                                system("cls");
                            }
                            break;
                        case 2:
                            {
                                char nombreLector [30];
                                printf("Ingrese el nombre del lector que va a ingresar: ");
                                fflush(stdin);
                                fgets(nombreLector, sizeof(nombreLector), stdin);
                                nombreLector[strcspn(nombreLector, "\n")] = 0;

                                nodoLector * existe = buscarNodoLector(*listaDeLectores,&nombreLector);
                                puts("\n");
                                if (existe != NULL) {
                                    mostrarLector(existe->info);
                                } else {
                                    printf("Lector no encontrado.\n");
                                }
                                system("pause");
                                system("cls");
                            }
                        case 0:
                            {
                                puts("Volviendo\n");
                            }
                        default:
                                puts("Opcion no valida\n");
                                system("cls");
                            break;
                        }
                    }while(opcion != 0);
                }
                break;
            case 6:
                system("cls");
                printf("6. Ver lista de lectores\n");

                imprimirListaLectores(*listaDeLectores);
                system("pause");
                system("cls");
                break;
            case 7:
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
                {
                    system("cls");
                   realizarAlquiler(archivoAlquileres, listaDeGeneros, listaDeLectores, listaDeAlquileres);
                   escribirArchivoLibros(*listaDeGeneros,archivoLibros);
                   escribirArchivoLectores(*listaDeLectores,archivoLectores);
                   system("pause");
                   system("cls");
                }
                break;
            case 2:
                system("cls");
                mostrarAlquileres(*listaDeAlquileres);
                system("pause");
                system("cls");
                break;
            case 3:
                {
                system("cls");
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
                {
                    system("cls");
                    realizarDevolucion(archivoAlquileres,listaDeGeneros,listaDeLectores,listaDeAlquileres);
                    escribirArchivoLibros(*listaDeGeneros,archivoLibros);
                    escribirArchivoLectores(*listaDeLectores,archivoLectores);
                    system("pause");
                    system("cls");
                }
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


