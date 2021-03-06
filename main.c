#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicfunctions.h"
#include "Map.h"
#include "list.h"
#include "ctype.h"

/*long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); // hash * 33 + c
    }
    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}*/


int main()
{
    int op = 0;
    printf("Ingrese numero de la operacion deseada: \n");
    printf("1) Importar musica desde archivo CSV \n");
    printf("2) Exportar musica a archivo CSV \n");
    printf("3) Agregar album \n");
    printf("4) Agregar cancion \n");
    printf("5) Eliminar canciones de un artista \n");
    printf("6) Buscar cancion \n");
    printf("7) Buscar canciones de un artista \n");
    printf("8) Buscar album \n");
    printf("9) Salir \n");
    char* nombre = calloc(50, sizeof(char));
    Map* mapa_canciones = createMap(stringHash,stringEqual);
    Map* mapa_artistas = createMap(stringHash,stringEqual);
    Map* mapa_albumes = createMap(stringHash,stringEqual);
    while(op!=9){
        scanf("%d", &op);
        switch(op){
            case 1:printf("Leyendo archivo canciones.csv \n");
                    import_musicCSV(mapa_canciones,mapa_artistas,mapa_albumes);
                    printf("Operacion Terminada \n");              //falta insercion de mapar artistas y albumes.
                    break;
            case 2:printf("Exportando  a archivo cancionesOUTPUT.csv \n");
                    export_musicCSV(mapa_canciones);
                    printf("Operacion Completada \n");
                    break;
            case 3:printf("Ingrese datos album \n");
                    nombre = calloc(50, sizeof(char));
                    fgets(nombre,10,stdin);             //para eliminar "\n del switch"
                    fgets(nombre,50,stdin);
                    //char* fecha = calloc(26,sizeof(char));
                    //fgets(fecha,50,stdin);
                    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
                        nombre[strlen (nombre) - 1] = '\0';
                    //if ((strlen(fecha) > 0) && (fecha[strlen (fecha) - 1] == '\n'))
                      //  fecha[strlen (fecha) - 1] = '\0';
                    add_album(nombre,mapa_albumes,mapa_canciones);
                    break;
            case 4:printf("Ingrese datos cancion \n");
                    fgets(nombre,10,stdin);             //para eliminar "\n del switch"
                    fgets(nombre,50,stdin);
                    char* artista = calloc(50,sizeof(char));
                    char* duracion = calloc(6,sizeof(char));
                    fgets(artista,50,stdin);
                    fgets(duracion,6,stdin);
                    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
                        nombre[strlen (nombre) - 1] = '\0';
                    if ((strlen(artista) > 0) && (artista[strlen (artista) - 1] == '\n'))
                        artista[strlen (artista) - 1] = '\0';
                    if ((strlen(duracion) > 0) && (duracion[strlen (duracion) - 1] == '\n'))
                        duracion[strlen (duracion) - 1] = '\0';
                    add_song(nombre,artista,duracion,"-",mapa_canciones, mapa_artistas, mapa_albumes);
                    printf("Cancion ingresada a memoria \n");
                    break;
            case 5:printf("Ingrese nombre artista \n");
                    fgets(nombre,10,stdin);             //para eliminar "\n del switch"
                    fgets(nombre,50,stdin);
                    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
                        nombre[strlen (nombre) - 1] = '\0';
                    delete_artist(nombre,mapa_artistas,mapa_canciones,mapa_albumes);
                    printf("Artista ""%s"" eliminado \n", nombre);
                    break;
            case 6:printf("Ingrese nombre cancion \n");
                    fgets(nombre,10,stdin);             //para eliminar "\n del switch"
                    fgets(nombre,50,stdin);
                    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
                        nombre[strlen (nombre) - 1] = '\0';
                    search_by_title(nombre, mapa_canciones);
                    break;
            case 7:printf("Ingrese nombre artista \n");
                    fgets(nombre,10,stdin);             //para eliminar "\n del switch"
                    fgets(nombre,50,stdin);
                    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
                        nombre[strlen (nombre) - 1] = '\0';
                    search_by_artist(nombre,mapa_artistas);
                    break;
            case 8:printf("Ingrese nombre album \n");
                    fgets(nombre,10,stdin);             //para eliminar "\n del switch"
                    fgets(nombre,50,stdin);
                    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
                        nombre[strlen (nombre) - 1] = '\0';
                    search_by_album(nombre,mapa_albumes);
                    break;
            case 9: printf("Para guardar sus cambios recuerde exportar a CSV \n");
                    break;

            default: printf("Opcion no valida, intente nuevamentente \n");
                     continue;
        }
    }
    return 0;
}
