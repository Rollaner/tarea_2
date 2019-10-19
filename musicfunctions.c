#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicfunctions.h"
#include "list.h"
#include "Map.h"

typedef struct song{
 char* name;
 char* artist;
 int length;
 list* albumList;
}song;

typedef struct album{
    char* name;
    char* date;
    Map* album_songs;
}album;

typedef struct artist{
    char* name;
    list* songlist;
}artist;

char * _strdup (const char *s) {
	size_t len = strlen (s) + 1;
    void *new = malloc (len);

	if (new == NULL)
	    return NULL;

	return (char *) memcpy (new, s, len);
}

const char *get_csv_field (char * tmp, int i) {
    //se crea una copia del string tmp
    char * line = _strdup (tmp);
    const char * tok;
    for (tok = strtok (line, ","); tok && *tok; tok = strtok (NULL, ",\n")) {
        if (!--i) {
            return tok;
        }
    }
    return NULL;
}

Map* import_musicCSV(){                     //lee datos de un archivo csv y los inserta al mapa songs
    FIlE* fp = fopen("mdata\\canciones.csv", r);
    fclose(fp);
};

void export_musicCSV(Map* songs);      //toma datos de mapa canciones y los ingresa a un archivo en formato csv

void search_by_title(char* title, Map* songMap);

void search_by_album(char* album, Map* albumMap);

void add_song(char* title, char* artist, int length); // añade una cancion, se tiene que usar en conjunto a insert para añadirlo a los mapas

void add_album(char* title, char* date, Map* albumMap); // crea un nuevo album

void search_by_artist(char* name, Map* artistMap);

void delete_artist(char* name, Map* artistMap);
