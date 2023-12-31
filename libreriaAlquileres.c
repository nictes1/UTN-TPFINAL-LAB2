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
        while(sig != NULL && strcasecmp(sig->alquiler.datosLector.nombreYapellido,nombreLectorAbuscar)!=0)
        {
            sig = sig->siguiente;
        }

        if(sig != NULL)
        {
            mostrarAlquiler(sig->alquiler);
        }else
        {
            printf("No se encontro al lector dentro del registro de alquileres\n");
        }

    }
}

void mostrarAlquileres(nodoAlquiler *listaAlquileres) {
    nodoAlquiler *actual = listaAlquileres;

    if(actual == NULL)
    {
        printf("No hay alquileres realizados\n");
    }

    while (actual != NULL) {
        mostrarAlquiler(actual->alquiler);
        puts("\n");
        actual = actual->siguiente;
    }
}

// Funci�n para validar si un a�o es bisiesto
int esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

// Funci�n para cargar una fecha con validaci�n de d�as, meses y a�o
fecha cargarFecha() {
    fecha nuevaFecha;

     // Validar si el d�a ingresado es v�lido para el mes y a�o dados
    int diasEnMes = 31; // Por defecto, consideramos un mes con 31 d�as

    do {
        // Solicitar al usuario que ingrese el d�a
        printf("Ingrese el dia: ");
        scanf("%d", &nuevaFecha.dia);

        // Solicitar al usuario que ingrese el mes
        printf("Ingrese el mes: ");
        scanf("%d", &nuevaFecha.mes);

        // Solicitar al usuario que ingrese el a�o
        printf("Ingrese el anio (a partir de 2023): ");
        scanf("%d", &nuevaFecha.anio);

        // Validar si el a�o ingresado es valido
        if (nuevaFecha.anio < 2023) {
            printf("�Anio invalido! Debe ser a partir de 2023. Intente nuevamente.\n");
            continue; // Volver a solicitar la entrada al usuario
        }

        // Validar si el mes ingresado es v�lido
        if (nuevaFecha.mes < 1 || nuevaFecha.mes > 12) {
            printf("�Mes invalido! Debe estar entre 1 y 12. Intente nuevamente.\n");
            continue; // Volver a solicitar la entrada al usuario
        }

        if (nuevaFecha.mes == 4 || nuevaFecha.mes == 6 || nuevaFecha.mes == 9 || nuevaFecha.mes == 11) {
            diasEnMes = 30; // Abril, junio, septiembre y noviembre tienen 30 d�as
        } else if (nuevaFecha.mes == 2) {
            diasEnMes = (esBisiesto(nuevaFecha.anio)) ? 29 : 28; // Febrero tiene 28 o 29 d�as
        }

        // Verificar si el d�a ingresado es v�lido
        if (nuevaFecha.dia < 1 || nuevaFecha.dia > diasEnMes) {
            printf("�Dia invalido para el mes y anio dados! Intente nuevamente.\n");
        }
    } while (nuevaFecha.dia < 1 || nuevaFecha.dia > diasEnMes);

    return nuevaFecha;
}


int contarDias(fecha a) {
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int dias = a.dia;

    for (int i = 0; i < a.mes - 1; i++) {
        dias += meses[i];
    }

    // Ajusta los d�as para a�os bisiestos
    if (a.mes > 2 && esBisiesto(a.anio)) {
        dias++;
    }

    return dias;
}

int diferenciaFechas(fecha alquiler, fecha temp) {
    int dias1 = contarDias(alquiler);
    int dias2 = contarDias(temp);

    int diferencia = dias2 - dias1;

    return diferencia;
}


nodoAlquiler *buscarAlquiler(nodoAlquiler *listaAlquileres, const char *nombreLector, const char *tituloBuscado) {
    nodoAlquiler *alquilerActual = listaAlquileres;

    while (alquilerActual != NULL) {
        if (strcmp(alquilerActual->alquiler.datosLector.nombreYapellido, nombreLector) == 0 &&
            strcmp(alquilerActual->alquiler.datoLibroAlquilado.titulo, tituloBuscado) == 0) {
            return alquilerActual; // Se encontr� el alquiler.
        }

        alquilerActual = alquilerActual->siguiente;
    }

    return NULL; // No se encontr� el alquiler.
}


void realizarAlquiler(const char *archivoAlquileres, listaGeneros **listaLibros, nodoLector **listaLectores, nodoAlquiler **listaAlquileres) {
    char nombreLector[60];
    char tituloBuscado[60];


    printf("Ingrese el nombre del lector que va a alquilar: ");
    fflush(stdin);
    fgets(nombreLector, sizeof(nombreLector), stdin);
    nombreLector[strcspn(nombreLector, "\n")] = 0;

    // Buscar el lector
    nodoLector *lectorEncontrado = buscarNodoLector(*listaLectores,&nombreLector);

    if (lectorEncontrado != NULL && lectorEncontrado->info.alquiler == 0) {  //si existe en la lista y tiene el estado de alquiler en 0
        printf("El lector tiene un alquiler pendiente de devolucion:\n");
        mostrarAlquilerPendienteDeDevolucion(*listaAlquileres, lectorEncontrado->info.nombreYapellido); //como tiene un alquiler pendiente de devolucion lo buscamos en la lista de alquileres
        return;
    }

    if (lectorEncontrado == NULL) { //si no existe damos la opcion de crearlo
        char mander = 's';
        printf("El lector no est� registrado, � desea crearlo ? (s/n): ");
        fflush(stdin);
        scanf("%c", &mander);

        if (mander == 's') {
            lector nuevo = cargarLector(nombreLector);  //creamos el nodo
            insertarOrdenado(listaLectores, crearNodoLector(nuevo)); //lo insertamos en la lista ordenada de lectores
            lectorEncontrado = buscarNodoLector(*listaLectores, nombreLector); //volvemos a capturar el puntero al lector que creamos
        } else {
            printf("Volviendo al menu principal\n");
            sleep(1);
            return;
        }
    }

    fflush(stdin);
    printf("Ingrese el titulo del libro que desea buscar: ");
    fgets(tituloBuscado, sizeof(tituloBuscado), stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = 0;

    // Buscar el libro en la lista de libros
    nodoArbolLibro *libroEncontrado = buscarLibroPorTituloEnLista(*listaLibros,&tituloBuscado);


    if (libroEncontrado == NULL) {
        printf("Libro no encontrado.\n");
        return;
    }

    if (libroEncontrado->dato.Copias.cantCopias == 0 || libroEncontrado->dato.estado == 0) {
        printf("Libro no disponible por falta de copias o disponibilidad.\n");
        return;
    }

    libroEncontrado->dato.Copias.cantCopias--; //modificamos la cantidad de copias del libro
    libroEncontrado->dato.cantidadaDevecesAlquilado++;


    lectorEncontrado->info.alquiler = 0; //ponemos el estado del lector en 0

    printf("Ingrese la fecha de alquiler (DD MM AAAA)\n");
    fecha miFecha = cargarFecha();

    int contar = contarDias(miFecha);

     // Crear el registro de alquiler usando la funci�n modularizada
    stRegistroAlquiler nuevoAlquiler = crearRegistroAlquiler(libroEncontrado->dato, lectorEncontrado->info, miFecha);


    // Agregar el alquiler a la lista de alquileres con la funci�n modularizada
    *listaAlquileres = crearNodoAlquiler(nuevoAlquiler, *listaAlquileres);

    // Guardar el alquiler en el archivo de alquileres
    FILE *archivoAlquiler = fopen(archivoAlquileres, "ab");
    if (archivoAlquiler != NULL) {
        fwrite(&nuevoAlquiler, sizeof(stRegistroAlquiler), 1, archivoAlquiler);
        fclose(archivoAlquiler);
    } else {
        printf("Error al abrir el archivo de alquileres para escritura.\n");
    }
}

stRegistroAlquiler crearRegistroAlquiler(stlibros libro, lector lectorEncontrado, fecha fechaAlquiler) {
    stRegistroAlquiler nuevoAlquiler;

    nuevoAlquiler.datoLibroAlquilado = libro;
    nuevoAlquiler.datosLector = lectorEncontrado;
    nuevoAlquiler.fechaAlquiler = fechaAlquiler;

    return nuevoAlquiler;
}

nodoAlquiler* crearNodoAlquiler(stRegistroAlquiler nuevoAlquiler, nodoAlquiler *listaAlquileres) {

    nodoAlquiler *nuevoNodoAlquiler = (nodoAlquiler *)malloc(sizeof(nodoAlquiler));
    nuevoNodoAlquiler->alquiler = nuevoAlquiler;
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
       //printf("No hay alquileres pendiente de devolucion\n");
       return NULL;
    }

    nodoAlquiler *listaAlquileres = inicializarListaAlquiler();
    stRegistroAlquiler registroAlquiler; // Cambio: mover la declaraci�n fuera del bucle

    // Lectura continua desde el archivo
    while (fread(&registroAlquiler, sizeof(registroAlquiler), 1, archivo) == 1) {
        nodoAlquiler *nuevoNodoAlquiler = crearNodoAlquiler(registroAlquiler, listaAlquileres);

        // Conectar el nuevo nodo a la lista
        listaAlquileres = nuevoNodoAlquiler;
    }

    fclose(archivo);
    return listaAlquileres;
}


void realizarDevolucion(const char *archivoAlquileres, listaGeneros **listaLibros, nodoLector **listaLectores, nodoAlquiler **listaAlquileres) {
    char nombreLector[60];
    char tituloBuscado[60];

    printf("Ingrese el nombre del lector que va a devolver el libro: ");
    fflush(stdin);
    fgets(nombreLector, sizeof(nombreLector), stdin);
    nombreLector[strcspn(nombreLector, "\n")] = 0;

    // Buscar el lector
    nodoLector *lectorEncontrado = buscarNodoLector(*listaLectores, &nombreLector);

    if (lectorEncontrado == NULL) {
        printf("El lector no est� registrado.\n");
        return;
    }

    printf("Ingrese el t�tulo del libro que desea devolver: ");
    fgets(tituloBuscado, sizeof(tituloBuscado), stdin);
    tituloBuscado[strcspn(tituloBuscado, "\n")] = 0;

    // Buscar el libro en la lista de libros
    nodoArbolLibro *libroEncontrado = buscarLibroPorTituloEnLista(*listaLibros, &tituloBuscado);

    if (libroEncontrado == NULL) {
        printf("Libro no encontrado.\n");
        return;
    }

    nodoAlquiler *alquilerActual = buscarAlquiler(*listaAlquileres, nombreLector, tituloBuscado);
    nodoAlquiler *alquilerAux = alquilerActual;  //declaro un nodo temporal que me va a servir para borrar en el archivo luego

    if (alquilerActual == NULL) {
        printf("El lector no tiene ese libro alquilado.\n");
        return;
    }

    mostrarAlquiler(alquilerActual->alquiler);

    // Solicitar al usuario la fecha de devoluci�n
    printf("Ingrese la fecha de devolucion (DD MM AAAA):\n");
    fecha fechaDevolucion = cargarFecha();


    // Calcular la diferencia de d�as entre la fecha de alquiler y la fecha de devoluci�n
    int diferenciaDias = diferenciaFechas(alquilerActual->alquiler.fechaAlquiler, fechaDevolucion);

    puts("\n");

    // Verificar si la diferencia de d�as es negativa (en caso de que la devoluci�n sea antes de la fecha de alquiler)
    if (diferenciaDias < 0) {
        printf("Error: La fecha de devolucion no puede ser anterior a la fecha de alquiler.\n");
        return;
    }

    mostrarLibro(libroEncontrado->dato);
    puts("\n");

    // Calcular el costo total del alquiler
    float costoParcial = (float) (diferenciaDias * libroEncontrado->dato.Copias.precioAlquiler);
    puts("\n");
    float costoDescuento = (costoParcial * 30)/100;
    float costoAlquilerTotal ;
    mostrarLector(lectorEncontrado->info);
    puts("\n");

    if(lectorEncontrado->info.esEstudiante)
    {
        printf("El lector es un estudiante por lo que se le aplica un descuento del 30%\n");

        costoAlquilerTotal = costoParcial - costoDescuento;
    }

    printf("Costo del alquiler del libro por dia : %f\n",libroEncontrado->dato.Copias.precioAlquiler);
    printf("Costo total del alquiler : %f",costoAlquilerTotal);
    puts("\n");

    // Restaurar la cantidad de copias del libro y el estado del lector
    libroEncontrado->dato.Copias.cantCopias++;
    lectorEncontrado->info.alquiler = 1; // El lector puede volver a alquilar

    //Borrar el Nodo de la lista de alquileres
    borrarNodoAlquiler(listaAlquileres,alquilerActual->alquiler.datosLector.dni);


    // Actualizar el archivo de alquileres
    FILE *archivoAlq = fopen(archivoAlquileres, "rb+");
    if (archivoAlq == NULL) {
        printf("Error al abrir el archivo de alquileres.\n");
        return;
    }

    stRegistroAlquiler registro;

    // Eliminar el registro de alquiler
    FILE *archiAlquilerTemp = fopen("alquiler_temp.dat", "wb");  // Creo un archivo temporal
    if (archiAlquilerTemp == NULL) {
        printf("Error al abrir el archivo temporal de alquileres.\n");
        fclose(archivoAlq);
        return;
    }

    fseek(archivoAlq, 0, SEEK_SET);

    while (fread(&registro, sizeof(stRegistroAlquiler), 1, archivoAlq) == 1) {
        if (registro.datosLector.dni != alquilerAux->alquiler.datosLector.dni) {
            fwrite(&registro, sizeof(stRegistroAlquiler), 1, archiAlquilerTemp);
        }
    }

    fclose(archivoAlq);
    fclose(archiAlquilerTemp);  // Cierro los archivos

    remove(archivoAlquileres);   // Borro mi archivo de alquileres original
    rename("alquiler_temp.dat", archivoAlquileres); // Y renombro el archivo temporal con el nombre del archivo original
}


void borrarNodoAlquiler(nodoAlquiler **lista, int dni) {
    nodoAlquiler *actual = *lista;
    nodoAlquiler *anterior = NULL;

    while (actual != NULL && actual->alquiler.datosLector.dni != dni) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != NULL) {
        if (anterior != NULL) {
            anterior->siguiente = actual->siguiente;
        } else {
            *lista = actual->siguiente;
        }
        free(actual);
    }
}
