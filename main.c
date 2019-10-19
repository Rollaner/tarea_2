#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicfunctions.h"
#include "Map.h"
#include "list.h"

long long stringHash(const void * key) {
    long long hash = 5381;

    const char * ptr;

    for (ptr = key; *ptr != '\0'; ptr++) {
        hash = ((hash << 5) + hash) + tolower(*ptr); /* hash * 33 + c */
    }

    return hash;
}

int stringEqual(const void * key1, const void * key2) {
    const char * A = key1;
    const char * B = key2;

    return strcmp(A, B) == 0;
}

int main()
{
    int op = 0;
    printf("Ingrese numero de la operacion deseada: \n");
    printf("1) Importar música desde archivo CSV \n");
    printf("2) Exportar musica desde archivo CSV \n");
    printf("3) Agregar album \n");
    printf("4) Agregar cancion \n");
    printf("5) Eliminar canciones de un artista \n");
    printf("6) Buscar cancion CSV \n");
    printf("7) Buscar canciones de un artista \n");
    printf("8) Buscar album \n");
    printf("9) Salir \n");
    while(op!=9){
        scanf("%d", &op);
        switch(op){
            case 1:printf("Leyendo archivo canciones.csv \n");
                    Map* mapa_canciones = createMap(stringHash,stringEqual);
                    Map* mapa_artistas = createMap(stringHash,stringEqual);
                    import_musicCSV(mapa_canciones,mapa_artistas);              //falta insercion de mapar artistas y albumes.
                    break;
            case 2:printf("Exportando archivo canciones.csv \n");

                    break;
            case 3:printf("Ingrese datos album \n");
                    break;
            case 4:printf("Ingrese datos cancion \n");
                    break;
            case 5:printf("Ingrese nombre artista \n");
                    break;
            case 6:printf("Ingrese nombre cancion \n");
                    char* nombre = calloc(50, sizeof(char));
                    fgets(nombre,50,stdin);             //para eliminar "\n del switch"
                    fgets(nombre,50,stdin);
                    if ((strlen(nombre) > 0) && (nombre[strlen (nombre) - 1] == '\n'))
                        nombre[strlen (nombre) - 1] = '\0';
                    search_by_title(nombre, mapa_canciones);
                    break;
            case 7:printf("Ingrese nombre artista \n");
                    break;
            case 8:printf("Ingrese nombre album \n");
                    break;
            case 9: break;
        }
    }
    return 0;
}
