#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicfunctions.h"
#include "Map.h"
#include "list.h"

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
