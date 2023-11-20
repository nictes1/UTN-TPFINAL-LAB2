#include <stdio.h>
#include <stdlib.h>
#include "libreriaListaPersonas.h"
#include "LibreriaArboLdeLibros.h"
#include "libreriaAlquileres.h"
#include <string.h>
#include <unistd.h>

nodoAlquiler * inicializarListaAlquiler ()
{
    return NULL;
}


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

void mostrarAlquileres(nodoAlquiler *listaAlquileres) {
    nodoAlquiler *actual = listaAlquileres;

    if(actual == NULL)
    {
        printf("No hay alquileres realizados\n");
    }

    while (actual != NULL) {
        mostrarDatosAlquiler(actual);
        actual = actual->siguiente;
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
    char nombreLector[60];
    char tituloBuscado[60];


    printf("Ingrese el nombre del lector que va a alquilar: ");
    fflush(stdin);
    fgets(nombreLector, sizeof(nombreLector), stdin);
    nombreLector[strcspn(nombreLector, "\n")] = 0;

    // Buscar el lector
    nodoLector *lectorEncontrado = buscarNodoLector(*listaLectores,&nombreLector);

    if (lectorEncontrado != NULL && lectorEncontrado->info.alquiler == 0) {  //si existe en la lista y tiene el estado de alquiler en 0
        printf("El lector tiene un alquiler pendiente de devolución:\n");
        mostrarAlquilerPendienteDeDevolucion(*listaAlquileres, lectorEncontrado->info.nombreYapellido); //como tiene un alquiler pendiente de devolucion lo buscamos en la lista de alquileres
        return;
    }

    if (lectorEncontrado == NULL) { //si no existe damos la opcion de crearlo
        char mander = 's';
        printf("El lector no está registrado, ¿desea crearlo? (s/n): ");
        fflush(stdin);
        scanf("%c", &mander);

        if (mander == 's') {
            lector nuevo = cargarLector(nombreLector);  //creamos el nodo
            insertarOrdenado(listaLectores, crearNodoLector(nuevo)); //lo insertamos en la lista ordenada de lectores
            lectorEncontrado = buscarNodoLector(*listaLectores, nombreLector); //volvemos a capturar el puntero al lector que creamos
        } else {
            return;
        }
    }else
    {
        printf("El lector existe\n");
    }

    printf("Ingrese el título del libro que desea buscar: ");
    fgets(tituloBuscado, sizeof(tituloBuscado), stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = 0;

    // Buscar el libro en la lista de libros
    nodoArbolLibro *libroEncontrado = buscarLibroPorTituloEnLista(*listaLibros,&tituloBuscado);


    if (libroEncontrado == NULL) {
        printf("Libro no encontrado.\n");
        return;
    }

    if (libroEncontrado->dato.Copias.cantCopias == 0) {
        printf("Libro no disponible.\n");
        return;
    }

    libroEncontrado->dato.Copias.cantCopias--; //modificamos la cantidad de copias del libro
    libroEncontrado->dato.cantidadaDevecesAlquilado++;


    lectorEncontrado->info.alquiler = 0; //ponemos el estado del lector en 0

    printf("Ingrese la fecha de alquiler (DD MM AAAA): ");
    fecha miFecha = cargarFecha();

     // Crear el registro de alquiler usando la función modularizada
    stRegistroAlquiler nuevoAlquiler = crearRegistroAlquiler(libroEncontrado->dato, lectorEncontrado->info, miFecha);


    // Agregar el alquiler a la lista de alquileres con la función modularizada
    *listaAlquileres = crearNodoAlquiler(nuevoAlquiler, *listaAlquileres);

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

    FILE *archivoLib = fopen(archivoLibros, "r+b");
    if (archivoLib != NULL) {
        fseek(archivoLib, (long)(-sizeof(stlibros)), SEEK_CUR);
        fwrite(&(libroEncontrado->dato), sizeof(stlibros), 1, archivoLib);
        fclose(archivoLib);
    } else {
        printf("Error al abrir el archivo de libros para escritura.\n");
    }
}

stRegistroAlquiler crearRegistroAlquiler(stlibros libro, lector lectorEncontrado, fecha fechaAlquiler) {
    stRegistroAlquiler nuevoAlquiler;

    nuevoAlquiler.datoLibroAlquilado = libro;
    nuevoAlquiler.datosLector = lectorEncontrado;
    nuevoAlquiler.fechaAlquiler = fechaAlquiler;

    printf("Nombre : %s \n", nuevoAlquiler.datosLector.nombreYapellido);
    printf("Libro : %s \n",nuevoAlquiler.datoLibroAlquilado.titulo);
    printf("DNI: %i \n", nuevoAlquiler.datosLector.dni);
    printf("Email: %s\n", nuevoAlquiler.datosLector.email);
    printf("Fecha de alquiler: %d/%d/%d\n", nuevoAlquiler.fechaAlquiler.dia, nuevoAlquiler.fechaAlquiler.mes, nuevoAlquiler.fechaAlquiler.anio);

    return nuevoAlquiler;
}

nodoAlquiler* crearNodoAlquiler(stRegistroAlquiler nuevoAlquiler, nodoAlquiler *listaAlquileres) {

    nodoAlquiler *nuevoNodoAlquiler = (nodoAlquiler *)malloc(sizeof(nodoAlquiler));

    nuevoNodoAlquiler->datoLibro = nuevoAlquiler.datoLibroAlquilado;
    nuevoNodoAlquiler->datosLector = nuevoAlquiler.datosLector;
    nuevoNodoAlquiler->fechaAlquiler = nuevoAlquiler.fechaAlquiler;
    nuevoNodoAlquiler->siguiente = listaAlquileres;

    return nuevoNodoAlquiler;
}

void mostrarArchivoAlquileres(const char * archivoAlquileres)
{
    FILE * archi = fopen(archivoAlquileres,"rb");

    if(archivoAlquileres == NULL)
    {
        puts("No hay alquileres registrados todavia\n");
        return;
    }

    stRegistroAlquiler aux;

    while(fread((&aux),sizeof(stRegistroAlquiler),1,archi)==1)
    {
        mostrarAlquiler(aux);
        puts("\n");
    }
}


void mostrarAlquiler (stRegistroAlquiler dato)
{
    printf("Nombre : %s \n", dato.datosLector.nombreYapellido);
    printf("Libro : %s \n",dato.datoLibroAlquilado.titulo);
    printf("DNI: %i \n", dato.datosLector.dni);
    printf("Email: %s\n", dato.datosLector.email);
    printf("Fecha de alquiler: %d/%d/%d\n", dato.fechaAlquiler.dia, dato.fechaAlquiler.mes, dato.fechaAlquiler.anio);
}

nodoAlquiler *cargarAlquileresDesdeArchivo(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
       printf("No hay alquileres pendiente de devolucion\n");
       return NULL;
    }

    nodoAlquiler *listaAlquileres = inicializarListaAlquiler();
    stRegistroAlquiler registroAlquiler; // Cambio: mover la declaración fuera del bucle

    // Lectura continua desde el archivo
    while (fread(&registroAlquiler, sizeof(registroAlquiler), 1, archivo) == 1) {
        nodoAlquiler *nuevoNodoAlquiler = crearNodoAlquiler(registroAlquiler, listaAlquileres);

        // Conectar el nuevo nodo a la lista
        listaAlquileres = nuevoNodoAlquiler;
    }

    fclose(archivo);
    return listaAlquileres;
}

// Función para validar si un año es bisiesto
int esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

// Función para cargar una fecha con validación de días, meses y año
fecha cargarFecha() {
    fecha nuevaFecha;

     // Validar si el día ingresado es válido para el mes y año dados
    int diasEnMes = 31; // Por defecto, consideramos un mes con 31 días

    do {
        // Solicitar al usuario que ingrese el día
        printf("Ingrese el día: ");
        scanf("%d", &nuevaFecha.dia);

        // Solicitar al usuario que ingrese el mes
        printf("Ingrese el mes: ");
        scanf("%d", &nuevaFecha.mes);

        // Solicitar al usuario que ingrese el año
        printf("Ingrese el año (a partir de 2023): ");
        scanf("%d", &nuevaFecha.anio);

        // Validar si el año ingresado es válido
        if (nuevaFecha.anio < 2023) {
            printf("¡Anio invalido! Debe ser a partir de 2023. Intente nuevamente.\n");
            continue; // Volver a solicitar la entrada al usuario
        }

        // Validar si el mes ingresado es válido
        if (nuevaFecha.mes < 1 || nuevaFecha.mes > 12) {
            printf("¡Mes invalido! Debe estar entre 1 y 12. Intente nuevamente.\n");
            continue; // Volver a solicitar la entrada al usuario
        }

        if (nuevaFecha.mes == 4 || nuevaFecha.mes == 6 || nuevaFecha.mes == 9 || nuevaFecha.mes == 11) {
            diasEnMes = 30; // Abril, junio, septiembre y noviembre tienen 30 días
        } else if (nuevaFecha.mes == 2) {
            diasEnMes = (esBisiesto(nuevaFecha.anio)) ? 29 : 28; // Febrero tiene 28 o 29 días
        }

        // Verificar si el día ingresado es válido
        if (nuevaFecha.dia < 1 || nuevaFecha.dia > diasEnMes) {
            printf("¡Dia inválido para el mes y anio dados! Intente nuevamente.\n");
        }
    } while (nuevaFecha.dia < 1 || nuevaFecha.dia > diasEnMes);

    return nuevaFecha;
}

/*
// Función para contar días acumulados hasta el mes anterior
int contarDias(fecha a) {
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dias = a.dia;

    for (int i = 0; i < a.mes - 1; i++) {
        dias += meses[i];
    }

    return dias;
}

int main() {
    fecha miFecha;

    // Llamar a la función para cargar una fecha con validación de días, meses y año
    miFecha = cargarFecha();

    // Imprimir la fecha cargada
    printf("Fecha cargada: %d/%d/%d\n", miFecha.dia, miFecha.mes, miFecha.anio);

    // Llamar a la función para contar días acumulados hasta el mes anterior
    int diasAcumulados = contarDias(miFecha);

    // Imprimir la cantidad de días acumulados hasta el mes anterior
    printf("Días acumulados hasta el mes anterior: %d\n", diasAcumulados);

    return 0;
}
*/
